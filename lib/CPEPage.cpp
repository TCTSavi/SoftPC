#include "..\Inc\CPEpage.h"

CPEPage::CPEPage() {
}

CPEPage::~CPEPage() {
	PMenuList.clear();
	PHWNDList.clear();
}

void CPEPage::Load() {
	PMenuList.clear();
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
	char szPath[260];
	fpos_t Pos;

	MOpc.Load(File);
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

bool CPEPage::Is_at_type(char *AxisType){
	if (strcmp(AxisType,Tipo)==0){
		return true;
	}
	return false;
}


void CPEPage::LoadMPar(){
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

CPMPar* CPEPage::getMPar(const char* Valor){
	for (int i=0;i<MParList.size();i++){
		if(strcmp(MParList[i].Valor,Valor)==0){
			return &MParList[i];
		}
	}
	return NULL;
}

void CPEPage::MakeRPar(){
	for (int c = 0;c<PMenuList.size();c++){
		for (int d = 0;d<PMenuList[c].ParList.size();d++){
			if(RParList.empty()){
				std::string NomePar;
				CRPar tmpRPar;
				tmpRPar.ParList.push_back(&PMenuList[c].ParList[d]);
				NomePar = "Grupo de endereco";
				tmpRPar.Par = PMenuList[c].ParList[d];
				strcpy(tmpRPar.Par.Nome,NomePar.c_str());
				RParList.push_back(tmpRPar);
			}
			else{
				bool found = false;
				for (int i=0;i<RParList.size();i++){
					if ( RParList[i].ParList[0]->End == PMenuList[c].ParList[d].End ){
						RParList[i].ParList.push_back(&PMenuList[c].ParList[d]);
						found = true;
						break;
					}
				}
				if (!found){
					std::string NomePar;
					CRPar tmpRPar;
					tmpRPar.ParList.push_back(&PMenuList[c].ParList[d]);
					NomePar = "Grupo de endereco";
					tmpRPar.Par = PMenuList[c].ParList[d];
					strcpy(tmpRPar.Par.Nome,NomePar.c_str());
					RParList.push_back(tmpRPar);
				}
			}
		}
	}
	for (int d = 0;d<TesteVerList.size();d++){
		if(RParList.empty()){
			std::string NomePar;
			CRPar tmpRPar;
			tmpRPar.ParList.push_back(&TesteVerList[d]);
			NomePar = "Grupo de endereco";
			tmpRPar.Par = TesteVerList[d];
			strcpy(tmpRPar.Par.Nome,NomePar.c_str());
			RParList.push_back(tmpRPar);
		}
		else{
			bool found = false;
			for (int i=0;i<RParList.size();i++){
				if ( RParList[i].ParList[0]->End == TesteVerList[d].End ){
					RParList[i].ParList.push_back(&TesteVerList[d]);
					found = true;
					break;
				}
			}
			if (!found){
				std::string NomePar;
				CRPar tmpRPar;
				tmpRPar.ParList.push_back(&TesteVerList[d]);
				NomePar = "Grupo de endereco";
				tmpRPar.Par = TesteVerList[d];
				strcpy(tmpRPar.Par.Nome,NomePar.c_str());
				RParList.push_back(tmpRPar);
			}
		}
	}
	//for (int i=0;i<RParList.size();i++){
	//	printf("Parametros de mesmo endereco:%s \n",RParList[i].Par.Nome);
	//	for (int j=0;j<RParList[i].ParList.size();j++){
	//		printf(" End:%d %s\n",RParList[i].ParList[j]->End,RParList[i].ParList[j]->Nome);
	//	}
	//	printf("\n");
	//}
	for (int i = 0;i<RParList.size();i++){
		for ( int j =0;j<RParList[i].ParList.size();j++){
			bool Find = false;
			switch (RParList[i].ParList[j]->getTipo()){
				case PCIERROR:
				case PCITABCONTROL:
				case PCICOMBUFSENDBAR:
				case PCIERRORBIT:
				case PCIBUTOP:
				case PCISTATUSBIT:
				case PCIBUTTON:
				case PCILEDIT:
				case PCILEDITL:
				case PCILEDITH:
				case PCITESTEVERIFICACAO:
				case PCIATVBYTE:
				case PCIATVBIT:
				case PCILCOMBOBOX:{
				}
				break;
				case PCITVBIT:
				case PCITVBYTE:{
					ReadRParList.push_back(RParList[i]);
					Find = true;
				}
				break;
				case PCILABEL:{
					ReadRParList.push_back(RParList[i]);
					Find = true;
				}
				break;
				default:{
					printf("Nao definida leitura para pagina de %s\n",RParList[i].ParList[j]->Nome);
				}
				break;
			}
			if (Find) break;
		}
	}
}

bool CPEPage::HasTesteVer(int IDbit){
	bool find = false;
	for (int c = 0;c<PMenuList.size();c++){
		for (int d = 0;d<PMenuList[c].ParList.size();d++){
			switch (PMenuList[c].ParList[d].getTipo()){
				case PCITESTEVERIFICACAO:{
					uint8_t	EndByte = 0;
					ConvVtoD(PMenuList[c].ParList[d].Valor,"%x",&EndByte);
					EndByte = 0xf0 & EndByte;
					char ByteValor[10];
					char BitValor[10];					
					itoa(EndByte,ByteValor,16);
					itoa(EndByte+IDbit,BitValor,16);
					CPPar tmpPar;
					strcpy( tmpPar.Tipo,"ATVBYTE");
					tmpPar.End = EndByte;
					strcpy( tmpPar.Valor,ByteValor);
					TesteVerList.push_back(tmpPar);
					for (int i = 0;i<16;i++){
						CPPar tmpPar;
						tmpPar.End = EndByte+i;
						strcpy( tmpPar.Tipo,"TVBYTE");
						strcpy( tmpPar.Valor,"FFFF");
						strcpy( tmpPar.Fator,"HEXFAT");
						tmpPar.Color = WARNCOLOR;
						TesteVerList.push_back(tmpPar);
					}
					strcpy( tmpPar.Tipo,"ATVBIT");
					strcpy( tmpPar.Valor,BitValor);
					TesteVerList.push_back(tmpPar);
					for (int i = 0;i<16;i++){
						CPPar tmpPar;
						tmpPar.End = EndByte+IDbit;
						tmpPar.Bit = i;
						strcpy( tmpPar.Tipo,"TVBIT");
						strcpy( tmpPar.Valor,"0");
						strcpy( tmpPar.Fator,"BITFAT");
						tmpPar.Color = WARNCOLOR;
						TesteVerList.push_back(tmpPar);
					}
					AdressBit = &TesteVerList[16];
					find = true;
				}
				break;
				default:{
				}
				break;
			}
		}
	}
	return find;
}

void CPEPage::ChangeTesteVer(int IDBit){
	while (!RParList.empty()){RParList.pop_back();}		
	while (!ReadRParList.empty()){ReadRParList.pop_back();}
	std::vector<CPPar> SavePar;
	for(int i = 0;i<TesteVerList.size();i++){
		SavePar.push_back(TesteVerList[i]);
		//printf("ID1:%d\n",TesteVerList[i].ID);
	}
	while (!TesteVerList.empty()){TesteVerList.pop_back();}
	if (HasTesteVer(IDBit)){
		for(int i = 0;i<TesteVerList.size();i++){
			TesteVerList[i].ID = SavePar[i].ID;
			//printf("ID2:%d\n",TesteVerList[i].ID);
		}
	}
	MakeRPar();
}

void CPEPage::SetBitTstVer(CPPar* Par){
	for(int i = 0;i<TesteVerList.size();i++){
		if (Par == &TesteVerList[i]){
			printf("Indice:%x\n",i-1);
			ChangeTesteVer(i-1);
		}
	}
}

void CPEPage::ConvVtoD ( const char * str, const char * format, ... ){
	va_list args;
	va_start (args, format);
	vsscanf (str, format, args);
	va_end (args);
}