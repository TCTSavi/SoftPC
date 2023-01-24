#include "..\Inc\CPCtrl.h"

CPCtrl::CPCtrl() {
	reading = true;
	readOk = false;
	readOk = 0;
	etapas = 0;
	Status = LOG_OK;
	StatusOld = LOG_ERROR;
	StatusError = LOG_ERROR;
}

CPCtrl::~CPCtrl() {
	PEixoList.clear();
	PMainList.clear();
}

void CPCtrl::PrtEtp(){
	printf("etapa:%d\n",etapas);
}

void CPCtrl::LoadEixos(char* File){
	ID = 9999;
	PEixoList.clear();

	char szPath[260];
	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\";
	Path+=File;
	
	FileHandle = fopen(Path.c_str(),"r");
	if (FileHandle == NULL) CLog::Log.Add("Nao foi possivel abrir :%s \n",Path.c_str());
	
	while (reading){
		switch (etapas){
			case 	0:{PrtEtp();LeLinha();}						break;
			case 	1:{PrtEtp();VerComando("BEGINEIXOS",0);}	break;//Se BEGINEIXOS segue , se não pula
			case 	2:{PrtEtp();LeLinha();}						break;
			case 	3:{PrtEtp();VerComando("ENDEIXOS",5);}		break;//Se ENDEIXOS segue , se não pula
			case 	4:{PrtEtp();VerFim();}						break;
			case 	5:{PrtEtp();VerDado();}						break;
			default	 :{reading = false;}						break;
		}
	}
}

void CPCtrl::LeLinha(){
	fgetpos(FileHandle,&Pos);
	Leitura[0] = 0;
	if(fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura) == EOF){
	reading = false;
	}
	else etapas++;
}
void CPCtrl::VerComando(char *Comando,int etapa){
	if (!(strcmp(Leitura,Comando)==0)){
		etapas = etapa;
	}
	else {
		fscanf(FileHandle,"%s%*[^\n]%*[\n]",Leitura);
		etapas++;
		CLog::Log.Add("Begin\n",etapas);
	}	
}

void CPCtrl::VerDado(){
	int  NEixo;
	char Nome[50];
	char File[50];
	char Tipo[50];
	fsetpos(FileHandle,&Pos);
	fscanf(FileHandle,"%d%*[\t]",&NEixo);
	fscanf(FileHandle,"%[^\t]%*[\t]",Nome);
	fscanf(FileHandle,"%[^\t]%*[\t]",File);
	fscanf(FileHandle,"%[^\t^\n]%*[\n]",Tipo);
	CLog::Log.Add("N:%d %s %s %s\n",
	NEixo,
	Nome,
	File,
	Tipo);
	CPEixo *Eixo =GetAxis(NEixo);
	if (Eixo == NULL){
		CPEixo _Eixo;
		PEixoList.push_back(_Eixo);
		Eixo = &PEixoList.back();
		Eixo->Number = NEixo;
	}
	CPEPage Page;
	Page.NEixo = NEixo;
	strcpy(Page.Nome,Nome);
	strcpy(Page.File,File);
	strcpy(Page.Tipo,Tipo);
	Page.Load();
	Eixo->PageList.push_back(Page);
	PageOrder PO;
	PO.NEixo = GetEixoIndex(Eixo);
	PO.NPage= Eixo->PageList.size()-1;
	APage.push_back(PO);
	if ( Page.Is_at_type("User") ){
		APageUser.push_back(PO);
	}
	else{
		APageConfig.push_back(PO);
	}
	//
	etapas = 2;	
}

void CPCtrl::VerFim(){
	for (int i =0;i<PEixoList.size();i++ ){
		setID(&PEixoList[i].PageList);
		for (int j = 0;j<PEixoList[i].PageList.size();j++){
			if (PEixoList[i].PageList[j].HasTesteVer(0)){
				for (int w=0;w<PEixoList[i].PageList[j].TesteVerList.size();w++){
					PEixoList[i].PageList[j].TesteVerList[w].ID = giveID();
				}
			}
		}
	}
	CLog::Log.Add("Eixo Ok,Size:%d\n",PEixoList.size());
	fclose(FileHandle);
	reading = false;
	readOk  = true;	
}


void CPCtrl::LoadMain(HWND _hwnd,char* File){
	PMainList.clear();
	char Leitura[100];
	bool reading = true;
	bool readOk = false;
	int etapas = 0;
	hwnd = _hwnd;

	char szPath[260];
	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\";
	Path+=File;
	
	FILE* FileHandle = fopen(Path.c_str(),"r");
	fpos_t Pos;
	if (FileHandle == NULL) CLog::Log.Add("Nao foi possivel abrir %s \n",File);
	CPEPage tmpPage;
	
	strcpy(tmpPage.Nome,"Controle Principal");
	strcpy(tmpPage.File,File);
	tmpPage.Load();
	tmpPage.LoadMPar();

	CPPar 	ParTabControl;
	CPMenu 	MenuTabControl;
	strcpy(ParTabControl.Nome,"Par Tab Control");
	strcpy(ParTabControl.Tipo,"TABCONTROL");
	strcpy(MenuTabControl.Nome,"Menu Tab Control");
	strcpy(MenuTabControl.Menu,"MTABCONTROL");
	MenuTabControl.x = 0;
	MenuTabControl.y = 0;
	MenuTabControl.w = 0;
	MenuTabControl.h = 0;
	MenuTabControl.ParList.push_back(ParTabControl);
	tmpPage.PMenuList.push_back(MenuTabControl);
	PMainList.push_back(tmpPage);
	setID(&PMainList);
	fclose(FileHandle);
	for (int i = 0;i<PEixoList.size();i++){
		PEixoList[i].Load(hwnd);
	}
}

void CPCtrl::setID(std::vector<CPEPage>* _PageList){
	for (int a = 0;a<(*_PageList).size();a++){
		for (int b = 0;b<(*_PageList)[a].PMenuList.size();b++){
			for (int c = 0;c<(*_PageList)[a].PMenuList[b].ParList.size();c++){
				(*_PageList)[a].PMenuList[b].ParList[c].ID = giveID();
			}
		}
	}
}

CPPar* CPCtrl::getPar(int ID){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					if ( PEixoList[a].PageList[b].PMenuList[c].ParList[d].ID == ID){
						return &PEixoList[a].PageList[b].PMenuList[c].ParList[d];
					}
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				if ( PEixoList[a].PageList[b].TesteVerList[c].ID == ID){
					return &PEixoList[a].PageList[b].TesteVerList[c];
				}
			}
		}
	}
	for (int a = 0;a<PMainList.size();a++){
		for (int b = 0;b<PMainList[a].PMenuList.size();b++){
			for (int c = 0;c<PMainList[a].PMenuList[b].ParList.size();c++){
				if ( PMainList[a].PMenuList[b].ParList[c].ID == ID){
					return &PMainList[a].PMenuList[b].ParList[c];
				}
			}
		}
	}
	return NULL;
}

void CPCtrl::ClearCommPage(){
	for (int a = 0;a<PEixoList.size();a++){
		PEixoList[a].Comm.ClearPage();
	}
}

void CPCtrl::SetCommPage(CPEPage* Page){
	CPEixo* Eixo = GetAxis(Page);
	Eixo->PParComAllReadPage(Page);
}

CPEixo* CPCtrl::GetAxis(CPEPage* Page){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			if ( &PEixoList[a].PageList[b] == Page){
				return &PEixoList[a];
			}
		}
	}
	return NULL;
}


CPPar* CPCtrl::getPar(int NEixo,const char* PagName,const char* MenuName,const char* ParName){
	for (int a = 0;a<PEixoList.size();a++){
		if (PEixoList[a].Number == NEixo){
			for (int b = 0;b<PEixoList[a].PageList.size();b++){
				if (strcmp(PEixoList[a].PageList[b].Nome,PagName)==0){
					for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
						if (strcmp(PEixoList[a].PageList[b].PMenuList[c].Nome,MenuName)==0){
							for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
								if (strcmp(PEixoList[a].PageList[b].PMenuList[c].ParList[d].Nome,ParName)==0){
									return &PEixoList[a].PageList[b].PMenuList[c].ParList[d];
								}
							}
						}
					}
				}
			}
		}
	}
	for (int b = 0;b<PMainList[0].PMenuList.size();b++){
		if (strcmp(PMainList[0].PMenuList[b].Menu,MenuName)==0){
			for (int c = 0;c<PMainList[0].PMenuList[b].ParList.size();c++){
				if (strcmp(PMainList[0].PMenuList[b].ParList[c].Nome,ParName)==0){
					return &PMainList[0].PMenuList[b].ParList[c];
				}
			}
		}
	}
	return NULL;
}


int CPCtrl::giveID(){
	ID++;
	return ID;
}

bool CPCtrl::Load_AxisFile(char* File,char* AxisType){
	bool reading = true;
	bool readOk = false;
	char Leitura[100];
	int etapas = 0;
	int nPage=0;
	fpos_t Pos;
	CPEixo tmpEixo;
	
	
	FILE* FileHandle = fopen(File,"r");
	if (FileHandle == NULL) {
		CLog::Log.Add("\nNao foi possivel abrir %s \n",File);
		return readOk;
	}
	CLog::Log.Add("Abrir:\r\n%s\r\n",File);
	while (reading){
		switch (etapas){
			//LeLinha
			case 0:{
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
			}
			break;
			//Verifica o comando
			case 1:{
				if (!(strcmp(Leitura,"BEGINPEIXO")==0)){
					etapas = 0;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]",Leitura);//Avança até o fim da linha
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo				
					etapas++;
				}
			}
			break;
			//LeLinha
			case 2:{
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo

			}
			//Verifica fim dos comandos
			case 3:{
				if ((strcmp(Leitura,"ENDPEIXO")==0)){
					etapas = 5;
				}
				else etapas++;
			}
			break;
			//Le comando
			case 4:{
				int  NEixo;
				char Nome[50];
				char File[50];
				fsetpos(FileHandle,&Pos);
				fscanf(FileHandle,"%d%*[\t]",&NEixo);
				fscanf(FileHandle,"%[^\t]%*[\t]",Nome);
				fscanf(FileHandle,"%[^\t^\n]%*[\n]",File);
				CLog::Log.Add("%d // %s // %s \r\n",
				NEixo,
				Nome,
				File);
				CPEPage Page;
				Page.NEixo = NEixo;
				strcpy(Page.Nome,Nome);
				strcpy(Page.File,File);
				tmpEixo.PageList.push_back(Page);
				etapas = 2;
			}
			break;
			//Verifica coerencia do arquivo
			case 5:{
				if ( sizeat(AxisType) != tmpEixo.PageList.size() ){
					CLog::Log.Add("Numero incoerente de eixos\r\n");
					CLog::Log.Add("Nao foi possivel carregar o programa\r\n");
					reading = false;
				}
				for (int i=0;i<sizeat(AxisType);i++){
					CPEPage* PageS = GivePage(AxisType,i);
					if (PageS == NULL){printf("Deu Ruim\n");}
					if (!(strcmp(PageS->File,tmpEixo.PageList[i].File)==0)){
					CLog::Log.Add("Combinacao incoerente de tipos\r\n");
					CLog::Log.Add("Nao foi possivel carregar o programa\r\n");
					reading = false;
					}
				}
				for (int i=0;i<sizeat(AxisType);i++){
					CPEPage* PageS = GivePage(AxisType,i);
					if (PageS == NULL){printf("Deu Ruim\n");}
					if (!(strcmp(PageS->Nome,tmpEixo.PageList[i].Nome)==0)){
					CLog::Log.Add("Combinacao incoerente de eixos\r\n");
					CLog::Log.Add("Nao foi possivel carregar o programa\r\n");
					reading = false;
					}
				}
			//Até aqui ok!
				etapas++;
			}
			break;
			//LeLinha
			case 6:{
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo

			}
			//LeComando
			case 7:{
				if (!(strcmp(Leitura,"BEGINPCF")==0)){
					etapas = 6;
				}
				else {
					fscanf(FileHandle,"%s%*[^\n]%",Leitura);//Avança até o fim da linha
					fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
					etapas++;
				}
			}
			break;
			//LeLinha
			case 8:{
				fgetpos(FileHandle,&Pos);
				Leitura[0] = 0;
				if(fscanf(FileHandle,"%s%*[^\n]",Leitura) == EOF){
				reading = false;
				}
				else etapas++;
				fscanf(FileHandle,"%*[\n]");//Avança para linha de baixo
			}			
			case 9:{
				if ((strcmp(Leitura,"ENDPCF")==0)){
					nPage++;
					if (nPage < tmpEixo.PageList.size()){
						etapas = 6;
					}
					else{
						etapas =12;
						//Fim da carga dos programas
					}
					
				}
				else etapas++;
			}
			break;
			case 10:{
				if ((strncmp(Leitura,"//",2)==0)){
					etapas = 8;
				}
				else etapas++;
			}
			break;
			case 11:{
				CPPar* Par;
				Leitura[0] = 0;
				fsetpos(FileHandle,&Pos);
				fscanf(FileHandle,"%[^\t]%*[\t]",Leitura);
				//printf("%s ,%d,%s\n",AxisType,nPage,Leitura);
				Par = getPar(AxisType,nPage,Leitura);
				if (Par == NULL){
					CLog::Log.Add("Parametro %s nao existe\r\n",Leitura);
				}
				else{
					fscanf(FileHandle,"%[^\t^\n]",Leitura);
					Par->setValor(Leitura);
				}
				fscanf(FileHandle,"%*[^\n]");
				fscanf(FileHandle,"%*[\n]");
				etapas=8;
			}
			break;	
			case 12:{
				reading = false;
				readOk  = true;
				fclose(FileHandle);
				CLog::Log.Add("Fim da leitura\r\n\r\n");
			}
			break;
			default:{
				fsetpos(FileHandle,&Pos);
				reading = false;
				fclose(FileHandle);
			}
			break;
		}
	}
	//system("pause");
	return readOk;
}

CPPar* CPCtrl::getPar(int NPage,char* MenuName,char* ParNome){
	CPEPage* PageS = GivePage(NPage);
	if (PageS == NULL){printf ("Deu Ruim\n");}
	for (int b = 0;b<PageS->PMenuList.size();b++){
		if (strcmp(PageS->PMenuList[b].Menu,MenuName)==0){
			for (int c = 0;PageS->PMenuList[b].ParList.size();c++){
				if ((strcmp(PageS->PMenuList[b].ParList[c].Nome,ParNome)==0)){
					return &PageS->PMenuList[b].ParList[c];
				}
			}
		}
	}
	
	return	NULL;
}

CPPar* CPCtrl::getPar(char *AxisType,int NPag,char* ParNome){
	CPEPage* PageS = GivePage(AxisType,NPag);
	if (PageS == NULL){printf ("Deu Ruim\n");}
	for (int a = 0;a<PageS->PMenuList.size();a++){
		for (int b = 0;b<PageS->PMenuList[a].ParList.size();b++){
			if ((strcmp(PageS->PMenuList[a].ParList[b].Nome,ParNome)==0)){
				return &PageS->PMenuList[a].ParList[b];
			}
		}
	}
}

HWND CPCtrl::getHWND(int ID){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PHWNDList.size();c++){
				if ( GetMenu(PEixoList[a].PageList[b].PHWNDList[c]) == (HMENU)ID){
					return PEixoList[a].PageList[b].PHWNDList[c];
				}
			}
		}
	}
	for (int a = 0;a<PMainList.size();a++){
		for (int b = 0;b<PMainList[a].PHWNDList.size();b++){
			if ( GetMenu(PMainList[a].PHWNDList[b]) == (HMENU)ID){
				return PMainList[a].PHWNDList[b];
			}
		}
	}
	return NULL;
}

void CPCtrl::SetAParToHWND(){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					SetParToHWND(&PEixoList[a].PageList[b].PMenuList[c].ParList[d]);
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				SetParToHWND(&PEixoList[a].PageList[b].TesteVerList[c]);
			}			
		}
	}		
}

void CPCtrl::SetAHWNDToPar(){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					SetHWNDToPar(&PEixoList[a].PageList[b].PMenuList[c].ParList[d]);
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				SetHWNDToPar( &PEixoList[a].PageList[b].TesteVerList[c] );
			}			
		}
	}	
}

void CPCtrl::SetParToHWND(CPPar* Par){
	HWND hwnd;
	hwnd = getHWND(Par->ID);
	if (hwnd == NULL) return; 
	CPMOpc* MOpc = GetMOpc(Par);
	if (MOpc == NULL) return;
	char OldValor[25];
	switch(Par->getTipo()){
		case PCIBUTTON:{
		}
		break;
		case PCILEDIT:
		case PCILEDITL:
		case PCILEDITH:{
			SetWindowText(hwnd,Par->getValor());
			Par->Color = OKCOLOR;
		}
		break;
		case PCILABELC:{
			//std::string str;
			//str += Par->Nome;
			//str += Par->getValor();
			//SetWindowText(hwnd,str.c_str());
			CPMPar* MPar = PMainList[0].getMPar(Par->getValor());
			std::string str;
			str += Par->Nome;
			HWND Label = getHWND(Par->ID);
			for (int i=0;i<MPar->CParList.size();i++){
				CPPar *ParN	= getPar(MPar->CParList[i].NPage,MPar->CParList[i].Menu,MPar->CParList[i].Par);
				//printf("%s %s %s\n",MPar->CParList[i].Eixo,MPar->CParList[i].Menu,MPar->CParList[i].Par);
				if ( ParN == NULL){
					CLog::Log.Add("Menu: %s invalido,Linha:%d de:%d\r\n",MPar->Valor,i,MPar->CParList.size());
				}
				else{
					str += ParN->getValor();
					str += " ";
				}
				
			}
			GetWindowText(Label,OldValor,sizeof(OldValor));
			if ( strcmp(str.c_str(),OldValor) != 0){
				SetWindowText(Label,str.c_str());
			}
		}
		break;
		case PCILCOMBOBOX:{
			int i = MOpc->getOpcID(Par->Opcoes,Par->getValor());
			SendMessage(hwnd,CB_SETCURSEL,(WPARAM)i, (LPARAM)0);
			Par->Color = OKCOLOR;
		}
		break;
		case PCIATVBIT:
		case PCIATVBYTE:{
			std::string str;
			str += Par->getValor();
			GetWindowText(hwnd,OldValor,sizeof(OldValor));
			if ( strcmp(str.c_str(),OldValor) != 0){
				SetWindowText(hwnd,str.c_str());
			}
		}
		break;
		case PCILABEL:{
			std::string str;
			str += Par->Nome;
			str += Par->getValor();
			GetWindowText(hwnd,OldValor,sizeof(OldValor));
			if ( strcmp(str.c_str(),OldValor) != 0){
				SetWindowText(hwnd,str.c_str());
			}
		}
		break;
		case PCITVBIT:
		case PCITVBYTE:{
			HWND hwndFocus;
			hwndFocus = GetFocus();
			if ( hwnd != hwndFocus ){
				SetWindowText(hwnd,Par->getValor());
			}
			InvalidateRect(hwnd, NULL, NULL);
		}
		break;
		case PCIERRORBIT:
		case PCISTATUSBIT:{
			int i = MOpc->getOpcID(Par->Opcoes,Par->getValor());
			if (i){
				SendMessage(hwnd,BM_SETCHECK,(WPARAM)BST_CHECKED, (LPARAM)0);
			}
			else{
				SendMessage(hwnd,BM_SETCHECK,(WPARAM)BST_UNCHECKED, (LPARAM)0);
			}
		}
		break;
		default:{
		}
		break;
	}
}

void CPCtrl::SetHWNDToPar(CPPar* Par){
	HWND hwnd;
	hwnd = getHWND(Par->ID);
	//printf("Par:%s\n",Par->Nome);
	CPMOpc* MOpc = GetMOpc(Par);
	char Valor[25];
	switch(Par->getTipo()){
		case PCIBUTTON:{
		}
		break;
		case PCILEDITH:
		case PCILEDITL:
		case PCILEDIT:{
			GetWindowText(hwnd,Valor,sizeof(Valor));
			Par->setValor(Valor);
		}
		break;
		case PCILCOMBOBOX:{
			//system("pause");
			int ID = SendMessage(hwnd,CB_GETCURSEL,(WPARAM)0, (LPARAM)0);
			char* _Valor = MOpc->getOpcStr(Par->Opcoes,ID);
			if ( _Valor == NULL ){printf("Opcoes não existem\n");}
			else{			
				Par->setValor(_Valor);
			}
		}
		break;
		case PCITESTEVERIFICACAO:{
			GetWindowText(hwnd,Valor,sizeof(Valor));
			Par->setValor(Valor);
			ClearCommPage();
			CPEPage* Page = GetPage(Par);
			Page->ChangeTesteVer(0);
			SetCommPage(Page);
			SetAParToHWND();
		}
		break;
		case PCITVBIT:
		case PCITVBYTE:{
			GetWindowText(hwnd,Valor,sizeof(Valor));
			Par->setValor(Valor);
			SendMessage(hwnd,WM_KILLFOCUS,0,0);
		}
		break;		
		default:{
		}
		break;
	}
	
	if ( strcmp(Par->Opcoes,"GetComOp")==0){
		CPEixo* Eixo = GetAxis(Par);
		printf("Muda porta\n");
		Eixo->SetRTChangePort();
	}
	if ( strcmp(Par->Opcoes,"DefCanal")==0){
		CPEixo* Eixo = GetAxis(Par);
		printf("Muda canal\n");
		Eixo->SetRTChangeCanal();
	}
	if ( strcmp(Par->Opcoes,"MENFAT")==0){
		CPEixo* Eixo = GetAxis(Par);
		printf("Muda fator\n");
		Eixo->SetRTChangeFator();
	}
	if ( strcmp(Par->Opcoes,"PGiro")==0){
		CPEixo* Eixo = GetAxis(Par);
		printf("Muda pulso/volta\n");
		Eixo->SetRTChangePGiro();
	}
}

void CPCtrl::SetTVByteToBit(CPPar* Par){
	switch(Par->getTipo()){
		case PCITVBYTE:{
			ClearCommPage();
			CPEPage* Page = GetPage(Par);
			Page->SetBitTstVer(Par);
			SetCommPage(Page);
			SetAParToHWND();
			printf("Seta Bit\n");
		}
		break;
		default:{
		}
		break;
	}
}

int CPCtrl::sizeat(char* AxisType ){
	if (strcmp(AxisType,"User")==0){
		return APageUser.size();
	}
	else{
		return APageConfig.size();
	}
	return 0;
}

void CPCtrl::EndAxis(){
	for (int i = 0;i<PEixoList.size();i++){
		PEixoList[i].EndAxis();
	}
	//Running = false;
	//Sleep(1);
	//SuspendThread(Thread);
}

void CPCtrl::InitAxis(){
	for (int i = 0;i<PEixoList.size();i++){
		PEixoList[i].InitAxis();
	}
	Running = true;
	FTimer = 20.0;
	EtapRA = 0;
	EtapRB = 0;	
	EtapRC = 0;	
	Buffer = 0;
	Send = 0;
	
//Inicia
	Thread = CreateThread( 
		NULL,
		0,
		(LPTHREAD_START_ROUTINE) &RTimer,
		this, 
		0, 
		NULL
	);		
}

void CPCtrl::Save_AxisFile(const char* File,char *AxisType){
	FILE* FileHandle = fopen(File,"w");
	if (FileHandle == NULL) CLog::Log.Add("\r\nNao foi possivel criar %s \r\n\r\n",File);
	char Escrita[100];
	bool writing = true;
	bool writeOk = false;
	int etapas = 0;
	int nEixo=0;
	int nMenu=0;
	CPEPage* Page;
	fpos_t Pos;
	while (writing){
		switch (etapas){
			//Escreve comando e cabeçario
			case 0:{
				fprintf(FileHandle,	"BEGINPEIXO\n"
									"Eixo\t\t\tNome\t\t\t\tArquivo de eixo\n");
				etapas++;
			}
			break;
			//Escreve Eixos,Paginas e Arquivos de eixo 
			case 1:{
				for (int i =0;i<sizeat(AxisType);i++){
					Page = GivePage(AxisType,i);
					if(Page == NULL){printf("DeuRuim\n");}
					fprintf(FileHandle,"%04d\t\t\t%s\t\t\t\t%s\n",Page->NEixo,Page->Nome,Page->File);
				}
				etapas++;
			}
			break;
			case 2:{
				fprintf(FileHandle,	"ENDPEIXO\n\n");
				etapas++;
			}
			break;
			case 3:{
				if (nEixo < sizeat(AxisType)){
					Page = GivePage(AxisType,nEixo);
					if(Page == NULL){printf("DeuRuim\n");}
					fprintf(FileHandle,	"BEGINPCF\n"
										"//Nome\t\t\t\t\t\t\t\tArquivo de eixo\n"
										"//%s\t\t\t\t\t\t\t%s\n"
										,Page->Nome,Page->File);
					etapas++;
				}
				else{
					etapas=6;
				}
			}
			break;
			case 4:{
				if (nMenu < Page->PMenuList.size()){
				int tab = 38-strlen(Page->PMenuList[nMenu].Nome);
					tab = (tab + 3) /4;
					char* stab = new char[tab+1];
					memset (stab,'\0',tab+1);
					memset (stab,'\t',tab);
					fprintf(FileHandle,	"//--------------------------------------------------\n"
										"//%s\t%sValor\n"
										"//--------------------------------------------------\n"
										,Page->PMenuList[nMenu].Nome,stab);
					delete stab;
					etapas++;
				}
				else{
					fprintf(FileHandle,	"//--------------------------------------------------\n"
										"ENDPCF\n\n");
					nEixo++;
					nMenu=0;
					etapas=3;
				}
			}
			break;
			case 5:{
				CPMenu* Menu = &Page->PMenuList[nMenu];
				//Esse for todo é para descobrir o numero de tab's.
				for(int i=0;i<Menu->ParList.size();i++){
					int tab = 40-strlen(Menu->ParList[i].Nome);
					tab = (tab + 3) /4;
					char* stab = new char[tab+1];
					memset (stab,'\0',tab+1);
					memset (stab,'\t',tab);
					fprintf(FileHandle,"%s\t%s%s\n",Menu->ParList[i].Nome,stab,Menu->ParList[i].Valor);
					delete stab;
				}
				fprintf(FileHandle,"\n");
				etapas=4;
				nMenu++;
			}
			break;
			case 6:{
				writing = false;
				fclose(FileHandle);
				CLog::Log.Add("Salvo:\r\n%s\r\n\r\n",File);
			}
			break;
			default:{
				writing = false;
				fclose(FileHandle);
			}
			break;
		}
	}
}

void CPCtrl::SendToAxis(CPPar* Par){
	if ( Par->End == 0){
		Par->Color = OKCOLOR;
		return;
	}
	CPEixo* Eixo = GetAxis(Par);
	if (Eixo == NULL) {printf("Não encontrou o eixo do paramentro\n");return;}
	if (Eixo->PushParCmd(Par)){
		Par->Color = OKCOLOR;
	}
}

void CPCtrl::ResetError(){
	for (int i=0;i<PEixoList.size();i++){
		PEixoList[i].ResetError();
	}
}

void CPCtrl::SetError(){
	for (int i=0;i<PEixoList.size();i++){
		PEixoList[i].SetError();
	}
}

void ConvReceiveD(char* buffer,const char * format, ...){
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);	
}	


void CPCtrl::ReceiveAll(){
	CPPar* Par;
	uint16_t Dado;
	char Valor[25];
	for (int i=0;i<ListComm.size();i++){
		while ( ListComm[i].PopQFIFO(Par,&Dado) ){
			ConvReceiveD(Valor,"%x",Dado);
			Par->setValor(Valor);
		}
	}
}

CPEixo* CPCtrl::GetAxis(CPPar* Par){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					if ( PEixoList[a].PageList[b].PMenuList[c].ParList[d].ID == Par->ID){
						return &PEixoList[a];
					}
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				if ( PEixoList[a].PageList[b].TesteVerList[c].ID == Par->ID){
					return &PEixoList[a];
				}
			}
		}
	}			
	return NULL;
}

CPEPage* CPCtrl::GetPage(CPPar* Par){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					if ( PEixoList[a].PageList[b].PMenuList[c].ParList[d].ID == Par->ID){
						return &PEixoList[a].PageList[b];
					}
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				if ( PEixoList[a].PageList[b].TesteVerList[c].ID == Par->ID){
					return &PEixoList[a].PageList[b];
				}
			}
		}
	}			
	return NULL;
}

CPEixo* CPCtrl::GetAxis(std::vector<CPEixo>* _EixoList,int AxisNumber){
	for (int a = 0;a<(*_EixoList).size();a++){
		if ( (*_EixoList)[a].Number == AxisNumber){
			return &(*_EixoList)[a];
		}
	}
	return NULL;
}

CPEixo* CPCtrl::GetAxis(int AxisNumber){
	for (int a = 0;a<PEixoList.size();a++){
		if ( PEixoList[a].Number == AxisNumber){
			return &PEixoList[a];
		}
	}
	return NULL;
}

CPEPage* CPCtrl::GivePage(int NPage){
	if ( !(NPage < APage.size()) ) return NULL;
	return &PEixoList[APage[NPage].NEixo].PageList[APage[NPage].NPage];
}

CPMOpc* CPCtrl::GetMOpc(CPPar* Par){
	for (int a = 0;a<PEixoList.size();a++){
		for (int b = 0;b<PEixoList[a].PageList.size();b++){
			for (int c = 0;c<PEixoList[a].PageList[b].PMenuList.size();c++){
				for (int d = 0;d<PEixoList[a].PageList[b].PMenuList[c].ParList.size();d++){
					if ( PEixoList[a].PageList[b].PMenuList[c].ParList[d].ID == Par->ID){
						return &PEixoList[a].PageList[b].MOpc;
					}
				}
			}
			for(int c = 0;c<PEixoList[a].PageList[b].TesteVerList.size();c++){
				if ( PEixoList[a].PageList[b].TesteVerList[c].ID == Par->ID){
					return &PEixoList[a].PageList[b].MOpc;
				}
			}			
		}
	}
	return NULL;	
}

void CPCtrl::CommAll(){
	for (int a = 0;a<PEixoList.size();a++){
		PEixoList[a].SetRTSendAll();
	}
}

int CPCtrl::GetCommand(char* cmd){
	if (strcmp(cmd,"CMD_SALVAUSER")==0){
		return CMD_SALVAUSER;
	}
	if (strcmp(cmd,"CMD_SALVACONFIG")==0){
		return CMD_SALVACONFIG;
	}
	if (strcmp(cmd,"CMD_SENDALL")==0){
		return CMD_SENDALL;
	}
	return NULL;
}

CPEPage* CPCtrl::GivePage(char* AxisType,int Pos){
	if (strcmp(AxisType,"User")==0){
		if ( !(Pos < APageUser.size()) ) return NULL;
		return &PEixoList[APageUser[Pos].NEixo].PageList[APageUser[Pos].NPage];
	}
	else{
		if ( !(Pos < APageConfig.size()) ) return NULL;
		return &PEixoList[APageConfig[Pos].NEixo].PageList[APageConfig[Pos].NPage];
	}
	return NULL;
}


int CPCtrl::GetNPages(){
	int Counter;
	for (int i=0;i<PEixoList.size();i++){
		for (int j=0;j<PEixoList[i].PageList.size();j++){
			Counter++;
		}
	}
	return Counter;
}

int CPCtrl::GetEixoIndex(CPEixo* Eixo){
	for (int a = 0;a<PEixoList.size();a++){
		if ( &PEixoList[a] == Eixo ){
			return a;
		}
	}
	return NULL;
}

void CPCtrl::DelLastWarn(){
	WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
	if ( ListAxisError.size() > 0 ){
		ListAxisError[0]->Status = false;
		//printf("Oia:%s\n",ListAxisError[0]->Comments);
		ListAxisError.erase(ListAxisError.begin());
		CLog::Log.RemoveWarn(ListAxisError.size());
	}
	ReleaseMutex(DMan::DM.ThreadTime);	
}

void CPCtrl::DelAllWarn(){
	WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
	int Size = ListAxisError.size();
	if ( Size > 0){
		for (int i = 0;i < Size ; i++ ){
			ListAxisError[0]->Status = false;
			ListAxisError.erase(ListAxisError.begin());
			CLog::Log.RemoveWarn(ListAxisError.size());
		}
	}
	ReleaseMutex(DMan::DM.ThreadTime);	
}

int CPCtrl::GetStatus(){
	int Status_;
	WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
	Status_ = StatusOld;
	ReleaseMutex(DMan::DM.ThreadTime);	
	return Status_;
}

void CPCtrl::RTimer(void* Param){
	CPCtrl* RTtmp;
	RTtmp = (CPCtrl*) Param;
	RTtmp->PCtrl = (CPCtrl*)Param;
	RTtmp->PCtrl->RtimerUse = 0;
	double dftDuration = 0;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER liNow;
	LARGE_INTEGER liOld;	
	LARGE_INTEGER liRt;	
	
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&liOld);
	while (RTtmp->PCtrl->Running){
		QueryPerformanceCounter(&liNow);
		LONGLONG llTimeDiff = liNow.QuadPart - liOld.QuadPart;
		dftDuration = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
//		printf("Tempo decorrido:%f,ref:%f\n",dftDuration,RTtmp->PCtrl->FTimer);
		if (dftDuration < RTtmp->PCtrl->FTimer){
			//printf("Tempo decorrido:%f\n",dftDuration);
			Sleep(5);
		}
		else{		
			WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
			QueryPerformanceCounter(&liOld);
			//Fluxo do programa principal
			switch (RTtmp->PCtrl->EtapRA){
				case PCtrlRAN0	: RTtmp->PCtrl->PCtrlRA00(); 	break;	//
				case PCtrlRANEnd: RTtmp->PCtrl->PCtrlRAEnd(); 	break;	//
				default: RTtmp->PCtrl->PCtrlRAError();			break;	//Deu Ruim
			}
			//Status da transmissão
			switch (RTtmp->PCtrl->EtapRB){
				case PCtrlRBN0	: RTtmp->PCtrl->PCtrlRB00(); 	break;	//
				case PCtrlRBN1	: RTtmp->PCtrl->PCtrlRB01(); 	break;	//
				case PCtrlRBN2	: RTtmp->PCtrl->PCtrlRB02(); 	break;	//
				case PCtrlRBNEnd: RTtmp->PCtrl->PCtrlRBEnd(); break;	//
				default: RTtmp->PCtrl->PCtrlRBError();		break;	//Deu Ruim
			}
			//
			RTtmp->PCtrl->PCtrlRCEnd();
			switch (RTtmp->PCtrl->EtapRC){
				case PCtrlRCN0	: RTtmp->PCtrl->PCtrlRC00(); 	break;	//
				case PCtrlRCN1	: RTtmp->PCtrl->PCtrlRC01(); 	break;	//
				case PCtrlRCN2	: RTtmp->PCtrl->PCtrlRC02(); 	break;	//
				case PCtrlRCNEnd: RTtmp->PCtrl->PCtrlRCEnd(); break;	//
				default: RTtmp->PCtrl->PCtrlRCError();		break;	//Deu Ruim
			}
			//Configura CommPage
			RTtmp->PCtrl->PCtrlRDEnd();
			switch (RTtmp->PCtrl->EtapRD){
				case PCtrlRDN0	: RTtmp->PCtrl->PCtrlRD00(); 	break;	//
				case PCtrlRDN1	: RTtmp->PCtrl->PCtrlRD01(); 	break;	//
				case PCtrlRDN2	: RTtmp->PCtrl->PCtrlRD02(); 	break;	//
				case PCtrlRDNEnd: RTtmp->PCtrl->PCtrlRDEnd(); break;	//
				default: RTtmp->PCtrl->PCtrlRBError();		break;	//Deu Ruim
			}
			//Envio do 1º Estado apos conectar
			RTtmp->PCtrl->PCtrlREEnd();
			switch (RTtmp->PCtrl->EtapRE){
				case PCtrlREN0	: RTtmp->PCtrl->PCtrlRE00(); 	break;	//
				case PCtrlREN1	: RTtmp->PCtrl->PCtrlRE01(); 	break;	//
				case PCtrlREN2	: RTtmp->PCtrl->PCtrlRE02(); 	break;	//
				case PCtrlRENEnd: RTtmp->PCtrl->PCtrlREEnd(); break;	//
				default: RTtmp->PCtrl->PCtrlREError();		break;	//Deu Ruim
			}
			//

			
			QueryPerformanceCounter(&liRt);
			llTimeDiff = liRt.QuadPart - liOld.QuadPart;
			RTtmp->PCtrl->RtimerUse = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
			ReleaseMutex(DMan::DM.ThreadTime);		
		}
    }	
}

//Temporizador
bool CPCtrl::TimerElapseEtap(int& Timer){
	Timer--;
	if ( Timer <= 0 ){
		return true;
	}
	else{
		return false;
	}
}

//Fluxo do programa principal
void CPCtrl::PCtrlRA00(){
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		if ( PCtrl->PEixoList[i].MErros.ListError.size() > 0 ){
			CPErro *Erro = PCtrl->PEixoList[i].MErros.GetLastError();
			bool Verificado = false;
			for (int j = 0;j<ListAxisError.size();j++){
				if ( ListAxisError[j] == Erro ){
					Verificado = true;
				}
			}
			if (!Verificado){
				ListAxisError.push_back(Erro);
				PostMessage(hwnd,WM_APP+1,(WPARAM)Erro,0);
			}
		}
		else{
		}
	}
	PCtrl->EtapRA = PCtrlRANEnd;
}	

void CPCtrl::PCtrlRAEnd(){
	PCtrl->EtapRA =  PCtrlRAN0;	
}

void CPCtrl::PCtrlRAError(){
}

//Status envio
void CPCtrl::PCtrlRB00(){
	PCtrl->Buffer = 0;
	PCtrl->Send = 0;
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		PCtrl->Buffer+= PCtrl->PEixoList[i].Buffer;
		PCtrl->Send+= PCtrl->PEixoList[i].Send;
	}
	PCtrl->EtapRB++;
}	

void CPCtrl::PCtrlRB01(){
	if ( PCtrl->TimerB >= 1 ){
		PCtrl->TimerB = 0;
		PCtrl->EtapRB++;
	}
	else{
		PCtrl->TimerB++;
	}		
}	

void CPCtrl::PCtrlRB02(){
	PostMessage(hwnd,WM_APP+3,0,0);
	PCtrl->EtapRB=PCtrlRBNEnd;	
}	

void CPCtrl::PCtrlRBEnd(){
	PCtrl->EtapRB=PCtrlRBN0;
}

void CPCtrl::PCtrlRBError(){
}

//Status
//Inicializa Status
void CPCtrl::PCtrlRC00(){
	PCtrl->StatusOld = LOG_WAIT;
	PCtrl->Status = LOG_WAIT;
	PostMessage(hwnd,WM_APP+4,0,0);
	PCtrl->EtapRC++;
}	

void CPCtrl::PCtrlRC01(){
	//Atualiza Status
	if ( PCtrl->Status == LOG_ERROR ){
		if ( PCtrl->StatusError == LOG_OK ){
			SetError();
			PCtrl->StatusError = PCtrl->Status;
		}
	}
	if ( PCtrl->Status == LOG_OK ){
		if ( PCtrl->StatusError == LOG_ERROR ){
			ResetError();
			PCtrl->StatusError = PCtrl->Status;
		}
	}
	if ( PCtrl->StatusOld != PCtrl->Status){
		PCtrl->StatusOld = PCtrl->Status;
		PostMessage(hwnd,WM_APP+4,0,0);
	}
}	

void CPCtrl::PCtrlRC02(){
}	

void CPCtrl::PCtrlRCEnd(){
	PCtrl->Status = LOG_OK;
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		if (	
				PEixoList[i].EtapRA==EixoRANEnd && 
				PEixoList[i].EtapRB==EixoRBNEnd &&  
				PEixoList[i].EtapRC==EixoRCNEnd && 
				PEixoList[i].EtapRD==EixoRDNEnd &&
				PEixoList[i].EtapRE==EixoRENEnd &&
				PEixoList[i].EtapRG==EixoRGNEnd 
				){
		}
		else{
			PCtrl->Status = LOG_WAIT;
		}
	}
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		for (int j = 0;j< PCtrl->PEixoList[i].MErros.ErrorTable.size();j++){
			if (PCtrl->PEixoList[i].MErros.ErrorTable[j].Status){
				PCtrl->Status = LOG_ERROR;
			}
		}
	}
}

void CPCtrl::PCtrlRCError(){
}


//Configura CommPage
void CPCtrl::PCtrlRD00(){
	PCtrl->EtapRD++;
}	

void CPCtrl::PCtrlRD01(){
	PostMessage(hwnd,WM_APP+6,(WPARAM)0,0);
	PCtrl->EtapRD = PCtrlRDNEnd;
}	

void CPCtrl::PCtrlRD02(){
}	

void CPCtrl::PCtrlRDEnd(){
	bool AxisOk = true;
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		if (	
				PEixoList[i].EtapRA==EixoRANEnd && 
				PEixoList[i].EtapRB==EixoRBNEnd &&  
				PEixoList[i].EtapRC==EixoRCNEnd && 
				PEixoList[i].EtapRD==EixoRDNEnd &&
				PEixoList[i].EtapRE==EixoRENEnd 
				){
		}
		else{
			AxisOk = false;
		}
	}
	if (!AxisOk) PCtrl->EtapRD = PCtrlRDN0;
}

void CPCtrl::PCtrlRDError(){
}

////Envio do 1º Estado apos conectar
void CPCtrl::PCtrlRE00(){
	bool OK = true;
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		if (	
				PEixoList[i].EtapRA==EixoRANEnd && 
				PEixoList[i].EtapRB==EixoRBNEnd &&  
				PEixoList[i].EtapRC==EixoRCNEnd && 
				PEixoList[i].EtapRD==EixoRDNEnd &&
				PEixoList[i].EtapRE==EixoRENEnd 
				){
		}
		else{
			OK = false;
		}
	}
	if (OK)PCtrl->EtapRE++;
}	

void CPCtrl::PCtrlRE01(){
	if ( PCtrl->Status == LOG_ERROR ){
		SetError();
	}
	if ( PCtrl->Status == LOG_OK ){
		ResetError();
	}
	PCtrl->EtapRE++;
}	

void CPCtrl::PCtrlRE02(){
}	

void CPCtrl::PCtrlREEnd(){
	for (int i = 0;i<PCtrl->PEixoList.size();i++){
		if (	
				PEixoList[i].EtapRA==EixoRANEnd && 
				PEixoList[i].EtapRB==EixoRBNEnd &&  
				PEixoList[i].EtapRC==EixoRCNEnd && 
				PEixoList[i].EtapRD==EixoRDNEnd &&
				PEixoList[i].EtapRE==EixoRENEnd 
				){
		}
		else{
			PCtrl->EtapRE = PCtrlREN0;
		}
	}
}

void CPCtrl::PCtrlREError(){
}

//--------------------------------------------------------------------------