#include    "..\Inc\CPMOpc.h"

CPMOpc::CPMOpc(){
}
CPMOpc::~CPMOpc(){
	MOpcList.clear();
}

void CPMOpc::Load(char* File){
	MOpcList.clear();
	fpos_t Pos;
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
	char szPath[260];
	
	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\";
	Path+=File;
	FILE* FileHandle = fopen(Path.c_str(),"r");
	if (FileHandle == NULL) CLog::Log.Add("Nao foi possivel abrir %s \n",File); 
	while (reading){
		switch (etapas){
			//LeLinha
			case 0:{
				//printf("Etapa:%d ",etapas);
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				//printf("Leitura:%s\n",Leitura);
			}
			break;
			//Verifica comando
			case 1:{
				//printf("Etapa:%d\n",etapas);
				if (!(strcmp(Leitura,"BEGINOPCOES")==0)){
					etapas = 0;
				}
				else {
					etapas++;
				}
			}
			break;
			//LeLinha
			case 2:{
				//printf("Etapa:%d ",etapas);
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura) == EOF){
					reading = false;
				}
				else etapas++;
			}
			break;
			//Verifica fim dos menus de comandos 
			case 3:{
				if ((strcmp(Leitura,"ENDOPCOES")==0)){
					etapas = 5;
				}
				else {
					etapas++;
				}
			}
			break;
			//Le opção
			case 4:{
				int tmp;
				CPLOpc tmpCPLOpc;
				strcpy(tmpCPLOpc.Opcoes,Leitura);
				Leitura[0] = 0;
				fscanf(FileHandle,"%*[\n]",tmpCPLOpc.Opcoes);
				tmpCPLOpc.Load(FileHandle);
				MOpcList.push_back(tmpCPLOpc);
				etapas = 2;
			}
			break;	
			//Finaliza
			case 5:{
				fclose (FileHandle);
				reading = false;
				readOk  = true;
			}
			break;	
			default:
				reading = false;
			break;
		}
	}	
}

CPLOpc::CPLOpc(){
}

CPLOpc::~CPLOpc(){
	OpcList.clear();
}

CPLOpc* CPMOpc::getOpcList(char* Opcoes){
	for (int i=0;i<MOpcList.size();i++){
		if ((strcmp(MOpcList[i].Opcoes,Opcoes)==0)){
			return &MOpcList[i];
		}
	}
//Não encontrou opção do programa,então é opção de interface ou não tem a opção;
	if ((strcmp("GetComOp",Opcoes)==0)){
		return getComPort();
		}
	return NULL;	
}

void CPLOpc::Load(FILE* FileHandle){
	OpcList.clear();
	int etapas = 0;
	fpos_t Pos,_Pos;
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	
	while (reading){
		switch (etapas){
			//Le Opção
			case 0:{
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				fscanf(FileHandle,"%[^\n^\t]%*[\t]",Leitura);
				etapas++;
			}
			break;
			//Verifica fim das opções
			case 1:{
				fgetpos(FileHandle,&_Pos);
				if ( Pos == _Pos){
					//Fim das opções
					Leitura[0] = 0;
					fscanf(FileHandle,"%*[\n]",Leitura);
					etapas=3;
				}
				else{
					etapas++;
				}
			}
			break;
			//Le Opção
			case 2:{
				SOpc tmpOpc;
				strcpy(tmpOpc.Opc,Leitura);
				OpcList.push_back(tmpOpc);
				etapas=0;
			}
			break;
			//Finaliza
			case 3:{
				reading = false;
				readOk  = true;
			}
			break;	
			default:
				reading = false;
			break;
		}
	}	
}

CPLOpc* CPMOpc::getComPort(){
	HKEY hKey;
	#define MAX_KEY_LENGTH 255
	#define MAX_VALUE_NAME 16383
	CPLOpc* LOpc = new CPLOpc;
	
	char    achKey[MAX_KEY_LENGTH];   			// buffer for subkey name
    DWORD   cbName;                   			// size of name string 
    char	achClass[MAX_PATH] = TEXT("");  	// buffer for class name 
    DWORD	cchClassName = MAX_PATH;  			// size of class string 
    DWORD	cSubKeys=0;               			// number of subkeys 
    DWORD	cbMaxSubKey;              			// longest subkey size 
    DWORD	cchMaxClass;              			// longest class string 
    DWORD	cValues;              				// number of values for key 
    DWORD	cchMaxValue;          				// longest value name 
    DWORD	cbMaxValueData;       				// longest value data 
    DWORD	cbSecurityDescriptor; 				// size of security descriptor 
    FILETIME ftLastWriteTime;      				// last write time 

	DWORD i, retCode;
	TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
	char chPorta[MAX_VALUE_NAME];
	
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,"HARDWARE\\DEVICEMAP\\SERIALCOMM",NULL,KEY_READ,&hKey);
	
	RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 

	if (cSubKeys){
        for (i=0; i<cSubKeys; i++){ 
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
						achKey, 
						&cbName, 
						NULL, 
						NULL, 
						NULL, 
						&ftLastWriteTime
						); 
            if (retCode == ERROR_SUCCESS){
				//_tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 		
	SOpc tmpOpc;
	strcpy(tmpOpc.Opc,"COM:NC");
	LOpc->OpcList.push_back(tmpOpc);
	//printf( "\nNumber of values: %d\n", cValues);
	for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++){ 
		cchValue = MAX_VALUE_NAME; 
		achValue[0] = '\0'; 
		retCode = RegEnumValue(
					hKey, i, 
					achValue, 
					&cchValue, 
					NULL, 
					NULL,
					NULL,
					NULL
					);
		if (retCode == ERROR_SUCCESS ){ 
			//_tprintf(TEXT("(%d) %s\n"), i+1, achValue);
			SOpc tmpOpc;
			DWORD cbData = 25;	
			RegQueryValueEx( hKey,
							achValue,
							NULL,
							NULL,
							(LPBYTE)tmpOpc.Opc,
							&cbData 
							);
			LOpc->OpcList.push_back(tmpOpc);
			//printf( "\nNumber of values: %s\n", tmpOpc.Opc);
		}
       }
	return LOpc;
}

int CPMOpc::getOpcID(char* Opcoes,char *opcao){
	CPLOpc* LOpc;
	LOpc = getOpcList(Opcoes);
	if (LOpc == NULL) {
		return 0;
	}
	for (int i=0;i<LOpc->OpcList.size();i++){
		if ((strcmp(LOpc->OpcList[i].Opc,opcao)==0)){
			return i;
		}
	}
	return 0;
}

char* CPMOpc::getOpcStr(char* Opcoes,int ID){
	CPLOpc* LOpc;
	//printf("%s\n",Opcoes);
	LOpc = getOpcList(Opcoes);
	if (LOpc == NULL) {
		return NULL;
	}
	if (ID<=LOpc->OpcList.size()){
		return LOpc->OpcList[ID].Opc;
	}	
	return NULL;
}

int CPMOpc::getMaskReset(char* Opcoes){
	CPLOpc* tmpOpcoes = getOpcList(Opcoes);
	uint16_t size = (tmpOpcoes->OpcList.size())-1;
	uint16_t Cbit = 0;
	uint16_t Mask = 1;
	bool bit = 0;
	for (int i=0;i<16;i++){
		bit = size & 0x8000;
		size <<= 1;
		if ( bit == 1){
			Cbit = 16-i;
			break;
		}
	}
	for (int j=0;j<Cbit;j++){
		Mask*=2;
	}
	Mask-=1;
	return Mask;
}