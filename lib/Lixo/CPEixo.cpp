#include "..\Inc\CPEixo.h"

CPEixo::CPEixo() {
	Canal = 0;
}

CPEixo::~CPEixo() {
	PMenuList.clear();
	PHWNDList.clear();
}

void CPEixo::Load() {
	PMenuList.clear();
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
	char szPath[260];
	fpos_t Pos;

	MOpc.Load(File);
	MErros.Load(File);
	printf("Saiu\n");
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
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
			}
			break;
			//Verifica comando
			case 1:{
				//printf("Etapa:%d\n",etapas);
				if (!(strcmp(Leitura,"BEGINMENU")==0)){
					etapas = 0;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]",Leitura);
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
					etapas++;
					CLog::Log.Add("Begin\n",etapas);
				}
			}
			break;
			//LeLinha
			case 2:{
				//printf("Etapa:%d ",etapas);
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
					reading = false;
				}
				else {
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
					etapas++;
				}
			}
			break;
			//Verifica fim dos comandos
			case 3:{
				if ((strcmp(Leitura,"ENDMENU")==0)){
					etapas = 5;
					CLog::Log.Add("End\n");
				}
				else etapas++;
			}
			break;
			//Le comando
			case 4:{
				CPMenu tmpMenu;
				fsetpos(FileHandle,&Pos);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpMenu.Nome);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpMenu.Menu);
				fscanf(FileHandle,"%d%*[\t]",&tmpMenu.x);
				fscanf(FileHandle,"%d%*[\t]",&tmpMenu.y);
				fscanf(FileHandle,"%d%*[\t]",&tmpMenu.w);
				fscanf(FileHandle,"%d%*[^\n^\t]",&tmpMenu.h);
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
				CLog::Log.Add("%s // %s // %d // %d // %d //%d \n",
				tmpMenu.Nome,
				tmpMenu.Menu,
				tmpMenu.x,
				tmpMenu.y,
				tmpMenu.w,
				tmpMenu.h);
				tmpMenu.Load(File);
				PMenuList.push_back(tmpMenu);
				etapas = 2;
			}
			break;	
			//Finaliza
			case 5:{
				CLog::Log.Add("Menu Ok,Size:%d\n",PMenuList.size());
				fclose(FileHandle);
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

bool CPEixo::Is_at_type(char *AxisType){
	if (strcmp(AxisType,Tipo)==0){
		return true;
	}
	return false;
}


void CPEixo::LoadMPar(){
	MParList.clear();
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
	char szPath[260];
	fpos_t Pos;

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
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
			}
			break;
			//Verifica comando
			case 1:{
				//printf("Etapa:%d\n",etapas);
				if (!(strcmp(Leitura,"BEGINMPAR")==0)){
					etapas = 0;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]",Leitura);
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
					etapas++;
					CLog::Log.Add("Begin\n",etapas);
				}
			}
			break;
			//LeLinha
			case 2:{
				//printf("Etapa:%d ",etapas);
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
					reading = false;
				}
				else {
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
					etapas++;
				}
			}
			break;
			//Verifica fim dos comandos
			case 3:{				 	
				if ((strcmp(Leitura,"ENDMPAR")==0)){
					etapas = 5;
					CLog::Log.Add("End\n");
				}
				else etapas++;
			}
			break;
			//Le comando
			case 4:{
				CPMPar tmpMPar;
				fsetpos(FileHandle,&Pos);
				
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpMPar.Tipo);
				fscanf(FileHandle,"%[^\n^\t]",tmpMPar.Valor);
				fscanf(FileHandle,"%*[\n]");		   //Avança para linha de baixo				

				printf("%s // %s \n",
				tmpMPar.Tipo,
				tmpMPar.Valor);
				tmpMPar.Load(File);
				MParList.push_back(tmpMPar);
				etapas = 2;
			}
			break;	
			//Finaliza
			case 5:{
				printf("Menu Ok,Size:%d\n",MParList.size());
				fclose(FileHandle);
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

CPMPar* CPEixo::getMPar(const char* Valor){
	for (int i=0;i<MParList.size();i++){
		if(strcmp(MParList[i].Valor,Valor)==0){
			return &MParList[i];
		}
	}
	return NULL;
}

char* CPEixo::GetCanal(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"DefCanal")==0){
				return PMenuList[a].ParList[b].Valor;
			}
		}
	}
	return NULL;
}

int CPEixo::GetEnd(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"VarTmp1")==0){
				return atoi(PMenuList[a].ParList[b].Valor);
			}
		}
	}
	return 0;
}

int CPEixo::GetLei(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"VarTmp2")==0){
				return atoi(PMenuList[a].ParList[b].Valor);
			}
		}
	}
	return 0;
}


char* CPEixo::GetFator(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"MENFAT")==0){
				return PMenuList[a].ParList[b].Valor;
			}
		}
	}
	return NULL;
}

char* CPEixo::GetPulsoVolta(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"PGiro")==0){
				return PMenuList[a].ParList[b].Valor;
			}
		}
	}
	return NULL;	
}

char* CPEixo::GetPorta(){
	for (int a=0;a<PMenuList.size();a++){
		for (int b=0;b<PMenuList[a].ParList.size();b++){
			if ( strcmp(PMenuList[a].ParList[b].Opcoes,"GetComOp")==0){
				return PMenuList[a].ParList[b].Valor;
			}
		}
	}
	return NULL;
}

HWND CPEixo::GetHWND(int ID){
	for (int i=0;i<PHWNDList.size();i++){
		if ( (int)GetMenu(PHWNDList[i])==ID){
			return PHWNDList[i];
		}
	}
	return NULL;
}