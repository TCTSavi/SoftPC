#include    "..\Inc\CPMPar.h"

CPMPar::CPMPar(){
}

CPMPar::~CPMPar(){
}

CPCPar::CPCPar(){
}

CPCPar::~CPCPar(){
}

void CPMPar::Load(char* File){
	CParList.clear();
	fpos_t Pos;
	char szPath[260];

	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\";
	Path+=File;
	FILE* FileHandle = fopen(Path.c_str(),"r");

	
	if (FileHandle == NULL) printf("Nao foi possivel abrir Menu:%s \n",File);
    
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
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
				if (!(strcmp(Leitura,Valor)==0)){
					etapas = 0;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura);
					etapas++;
					printf("Begin\n",etapas);
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
			//Verifica fim dos comandos
			case 3:{
				if ((strcmp(Leitura,"END")==0)){
					etapas = 5;
					printf("End\n");
				}
				else etapas++;
			}
			break;
			//Le comando
			case 4:{
				CPCPar tmpCPar;
				fsetpos(FileHandle,&Pos);
				fscanf(FileHandle,"%d%*[\t]",&tmpCPar.NPage);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpCPar.Menu);
				fscanf(FileHandle,"%[^\n^\t]",tmpCPar.Par);
				fscanf(FileHandle,"%*[\n]");		   //Avança para linha de baixo
				printf("%d // %s // %s\n",
				tmpCPar.NPage,
				tmpCPar.Menu,
				tmpCPar.Par);
				CParList.push_back(tmpCPar);
				etapas = 2;
			}
			break;	
			//Finaliza
			case 5:{
				printf("Parametros Ok,Size:%d\n",CParList.size());
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