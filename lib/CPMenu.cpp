#include    "..\Inc\CPMenu.h"

CPMenu::CPMenu(){
}

CPMenu::~CPMenu(){
	ParList.clear();
}

void CPMenu::Load(char* File){
	ParList.clear();
	fpos_t Pos;
	char szPath[260];

	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\";
	Path+=File;
	FILE* FileHandle = fopen(Path.c_str(),"r");

	
	if (FileHandle == NULL) CLog::Log.Add("Nao foi possivel abrir Menu:%s \n",File);
    
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
				if (!(strcmp(Leitura,Menu)==0)){
					etapas = 0;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura);
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
				if(fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura) == EOF){
					reading = false;
				}
				else etapas++;
			}
			break;
			//Verifica fim dos comandos
			case 3:{
				if ((strcmp(Leitura,"ENDPAR")==0)){
					etapas = 5;
					CLog::Log.Add("End\n");
				}
				else etapas++;
			}
			break;
			//Le comando
			case 4:{
				CPPar tmpPar;
				fsetpos(FileHandle,&Pos);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpPar.Nome);
				fscanf(FileHandle,"%hhx%*[\t]",&tmpPar.End);
				fscanf(FileHandle,"%hd%*[\t]",&tmpPar.Bit);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpPar.Opcoes);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpPar.Tipo);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpPar.Fator);
				fscanf(FileHandle,"%[^\t]%*[\t]",tmpPar.getValor());
				fscanf(FileHandle,"%d%*[\t]",&tmpPar.x);
				fscanf(FileHandle,"%d%*[\t]",&tmpPar.y);
				fscanf(FileHandle,"%d%*[\t]",&tmpPar.w1);
				fscanf(FileHandle,"%d%*[\t]",&tmpPar.h1);
				fscanf(FileHandle,"%d%*[\t]",&tmpPar.w2);
				fscanf(FileHandle,"%d%*[\n]",&tmpPar.h2);
				CLog::Log.Add("%s // %x // %d // %s // %s // %s // %s // %d // %d // %d // %d // %d // %d \n",
				tmpPar.Nome,
				tmpPar.End,
				tmpPar.Bit,
				tmpPar.Opcoes,
				tmpPar.Tipo,
				tmpPar.Fator,
				tmpPar.getValor(),
				tmpPar.x,
				tmpPar.y,
				tmpPar.w1,
				tmpPar.h1,
				tmpPar.w2,
				tmpPar.h2);
				ParList.push_back(tmpPar);
				etapas = 2;
			}
			break;	
			//Finaliza
			case 5:{
				CLog::Log.Add("Parametros Ok,Size:%d\n",ParList.size());
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
