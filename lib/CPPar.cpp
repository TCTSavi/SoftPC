#include    "..\Inc\CPPar.h"

CPPar::CPPar(){
	Mutex = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (Mutex == NULL) 
    {
        //ERROR;
	}
	Color =	WARNCOLOR;
}

int CPPar::getTipo(){
	if (strcmp(Tipo,"LOGC")==0){
		return PCILOGC;
	}
	if (strcmp(Tipo,"BOTAOC")==0){
		return PCIBUTTONC;
	}
	if (strcmp(Tipo,"BOTAO")==0){
		return PCIBUTTON;
	}
	if (strcmp(Tipo,"BOTOP")==0){
		return PCIBUTOP;
	}
	if (strcmp(Tipo,"LEDIT")==0){
		return PCILEDIT;
	}
	if (strcmp(Tipo,"LEDITL")==0){
		return PCILEDITL;
	}
	if (strcmp(Tipo,"LEDITH")==0){
		return PCILEDITH;
	}
	if (strcmp(Tipo,"LCOMBOBOX")==0){
		return PCILCOMBOBOX;
	}
	if (strcmp(Tipo,"LISTVIEWC")==0){
		return PCILISTVIEWC;
	}
	if (strcmp(Tipo,"LABELC")==0){
		return PCILABELC;
	}
	if (strcmp(Tipo,"LABEL")==0){
		return PCILABEL;
	}
	if (strcmp(Tipo,"BCMACHSTATUS")==0){
		return PCIBUTTONCMACHINESTATUS;
	}
	if (strcmp(Tipo,"TABCONTROL")==0){
		return PCITABCONTROL;
	}
	if (strcmp(Tipo,"COMBUFSENDBAR")==0){
		return PCICOMBUFSENDBAR;
	}
	if (strcmp(Tipo,"COMBUFSENDBARC")==0){
		return PCICOMBUFSENDBARC;
	}
	if (strcmp(Tipo,"STATUSC")==0){
		return PCISTATUSC;
	}
	if (strcmp(Tipo,"STATUSBIT")==0){
		return PCISTATUSBIT;
	}
	if (strcmp(Tipo,"ERRORBIT")==0){
		return PCIERRORBIT;
	}
	if (strcmp(Tipo,"TESTEVERIFICACAO")==0){
		return 	PCITESTEVERIFICACAO;
	}
	if (strcmp(Tipo,"TVBYTE")==0){
		return 	PCITVBYTE;
	}
	if (strcmp(Tipo,"TVBIT")==0){
		return 	PCITVBIT;
	}
	if (strcmp(Tipo,"ATVBYTE")==0){
		return 	PCIATVBYTE;
	}
	if (strcmp(Tipo,"ATVBIT")==0){
		return 	PCIATVBIT;
	}
	if (strcmp(Tipo,"SCROLLBARC")==0){
		return 	PCISCROLLBARC;
	}
	if (strcmp(Tipo,"ERROROUTSET")==0){
		return 	PCIERROROUTSET;
	}
	if (strcmp(Tipo,"ERROROUTRESET")==0){
		return 	PCIERROROUTRESET;
	}
	CLog::Log.Add("Tipo '%s' nao existe\n",Tipo);
	return PCIERROR;
}


int CPPar::getFator(){
	if (strcmp(Fator,"NOFAT")==0){
		return NOFAT;
	}
	if (strcmp(Fator,"MMFAT")==0){
		return MMFAT;
	}
	if (strcmp(Fator,"MMFAT200")==0){
		return MMFAT200;
	}
	if (strcmp(Fator,"MILISEC")==0){
		return MILISEC;
	}
	if (strcmp(Fator,"HEXFAT")==0){
		return HEXFAT;
	}
	if (strcmp(Fator,"BITFAT")==0){
		return BITFAT;
	}
	return FATERROR;
}

char* CPPar::getValor(){
	char* tmpValor;
	DWORD WaitMutex;
	WaitMutex = WaitForSingleObject( Mutex,INFINITE);  	// no time-out interval	
	tmpValor = Valor;
	ReleaseMutex(Mutex);
	return tmpValor;
}

bool CPPar::setValor(char *Valor){
	DWORD WaitMutex;
	WaitMutex = WaitForSingleObject( Mutex,INFINITE);  	// no time-out interval	
	strcpy(this->Valor,Valor);
	ReleaseMutex(Mutex);
	return true;
}

void CBMachStat::Draw(HWND MainWindow,HWND hwndPar,bool bChange){
	HDC  hDC; 
	HBRUSH hbrushModo;
	hbrushModo = GetModo();
	hDC = GetDC(hwndPar);
	if ( !GetClientRect(hwndPar,&rchwnd) ){
		printf("Deu Ruim\n");
		return;
	}
	rcedit = rchwnd;
	switch (bChange){
		case true :{
			rcedit.left +=5;  
			rcedit.top +=5;
			rcedit.bottom = rcedit.top+5;  
			rcedit.right -=5;
			FillRect (hDC,&rcedit,hbrushModo);
			rcedit = rchwnd;
			rcedit.left +=5;  
			rcedit.top +=5;
			rcedit.bottom -=5;  
			rcedit.right = rcedit.left+5;
			FillRect (hDC,&rcedit,hbrushModo);
			rcedit = rchwnd;
			rcedit.left +=5;  
			rcedit.bottom -=5;  
			rcedit.top = rcedit.bottom-5;
			rcedit.right -=5;
			FillRect (hDC,&rcedit,hbrushModo);
			rcedit = rchwnd;
			rcedit.top +=5;
			rcedit.bottom -=5;  
			rcedit.right -=5;
			rcedit.left =rcedit.right-5;  
			FillRect (hDC,&rcedit,hbrushModo);
		}
		break;
		case false:{
			InvalidateRect(hwndPar, NULL, NULL);
		}
		break;
		default:{
		}
	}
	ReleaseDC(hwndPar,hDC);
	/*
	RECT rcContent;
	int iState=0;//PBS_DEFAULTED, PBS_DISABLED, PBS_HOT, PBS_NORMAL, PBS_PRESSED
	hTheme = OpenThemeData(dis->hwndItem, L"Button");
	GetThemeBackgroundContentRect(hTheme, dis->hDC, BP_PUSHBUTTON,PBS_NORMAL, &dis->rcItem, &rcContent);
	if (hTheme){
		if (dis->itemState & ODS_SELECTED){
			iState = iState | PBS_DEFAULTED;
			//printf("ODS_SELECTED \n");
		}
		else{
			//printf("Not ODS_SELECTED \n");
		}
		if (dis->itemState & 0x0040){
		//if (dis->itemState & ODS_HOTLIGHT){
			iState = iState | PBS_HOT;
			//printf("ODS_HOTLIGHT\n");
		}
		else{
			//printf("not ODS_HOTLIGHT\n");
		}
		if (dis->itemState & ODS_FOCUS){
			iState = iState | PBS_DEFAULTED;
			//printf("ODS_FOCUS\n");
		}
		else{
			//printf("not ODS_FOCUS\n");
		}
		DrawThemeBackground(hTheme, dis->hDC, BP_PUSHBUTTON, iState,  &dis->rcItem, 0);
		//Desenha primeiro retangulo de aviso
		RECT rtwarm;
		rtwarm = dis->rcItem;
		rtwarm.left +=5;  
		rtwarm.top +=5;
		rtwarm.bottom -=5;  
		rtwarm.right -=5;
		FillRect (dis->hDC,&rtwarm,GetModo());//Preenche o fundo do retangulo
		rtwarm.left +=5;  
		rtwarm.top +=5;
		rtwarm.bottom -=5;  
		rtwarm.right -=5;
		DrawThemeBackground(hTheme, dis->hDC, BP_PUSHBUTTON, iState,  &rtwarm, 0);
		FillRect (dis->hDC,&rtwarm,HB_Normal);//Preenche o fundo do retangulo

		
		if (dis->itemState & ODS_FOCUS){
			RECT rtfocus;
			rtfocus = dis->rcItem;
			rtfocus.left +=3;  
			rtfocus.top +=3;
			rtfocus.bottom -=3;  
			rtfocus.right -=3;
			DrawFocusRect( dis->hDC, &rtfocus);	
		}
		else{
		}
		int cchText = GetWindowTextLength(dis->hwndItem);
		if (cchText > 0){
			TCHAR *pszText = new TCHAR[cchText+1];
			if (pszText){
				if (GetWindowText(dis->hwndItem, pszText, cchText+1))
				{
					int widelen = MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<LPCSTR>(pszText),cchText+1, NULL, 0);
					WCHAR *pszWideText = new WCHAR[widelen+1];
					MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<LPCSTR>(pszText), cchText,pszWideText, widelen);
					SetBkMode(dis->hDC, TRANSPARENT);
					DrawThemeText(hTheme,dis->hDC,BP_PUSHBUTTON,iState,pszWideText,cchText,DT_CENTER | DT_VCENTER | DT_SINGLELINE,NULL,&rcContent);
					delete [] pszWideText;
					//printf("Texto:%s\n",pszText);
				}
				delete [] pszText;
			}
		}
	}
	else{
			CLog::Log.Add("falha ao obter tema do windows\r\n");
	}
	CloseThemeData(hTheme);
	*/
}

HBRUSH CBMachStat::GetModo(){
	HB_Color = HB_Hollow;
	switch (Modo){
		case MachStat_Ok:{
			HB_Color = HB_Ok;
		}
		break;
		case MachStat_Error:{
			HB_Color = HB_Error;
		}
		break;
		case MachStat_Warm:{
			HB_Color = HB_Warm ;
		}
		break;
		default:{
		}
		break;
		//printf("Cor %d\n",FrameCount);
	}	
	return HB_Color;
}


void CTab::Draw(DRAWITEMSTRUCT* dis){
	TCITEM tie;
	char NEixo[50];
	tie.mask = TCIF_TEXT;
	tie.pszText = NEixo;
	tie.cchTextMax = sizeof(NEixo) * sizeof(char);
	TabCtrl_GetItem(dis->hwndItem, dis->itemID, &tie);
	RECT rttemp;
	FillRect(dis->hDC,&dis->rcItem,HB_Normal);
	rttemp = dis->rcItem;
	rttemp.bottom -=19;  
	FillRect(dis->hDC,&rttemp,HB_Green);
	SetTextColor(dis->hDC, RGB(0,0,0));
	SetBkMode(dis->hDC, TRANSPARENT);
	//DrawCaption(  dis->hwndItem,  dis->hDC,  &dis->rcItem,  DC_SMALLCAP);
	//DrawEdge( dis->hDC, &dis->rcItem,(dis->itemState & ODS_SELECTED ? EDGE_BUMP : EDGE_ETCHED ),BF_MONO);
	DrawEdge( dis->hDC, &dis->rcItem,(dis->itemState & ODS_SELECTED ? EDGE_RAISED : EDGE_RAISED ),0);
	DrawText( dis->hDC,tie.pszText,_tcslen(tie.pszText),  &dis->rcItem,  DT_VCENTER|DT_SINGLELINE|DT_CENTER);//Preenche o Texto
}

CExpPar::CExpPar(){
}

CBMachStat::CBMachStat(){
	bChange = false;
	Modo = MachStat_Error;
	//Modo = MachStat_Ok;
	//Modo = MachStat_Warm;
	HB_Error = CreateSolidBrush(RGB(255, 0, 0));
	HB_Normal = CreateSolidBrush(RGB(240,240,240));
	HB_Warm = CreateSolidBrush(RGB(255,255,51));
	HB_Ok = CreateSolidBrush(RGB(0, 204, 0));
	HB_Hollow = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HB_Color = HB_Normal;
}

CTab::CTab(){
	HB_Red = CreateSolidBrush(RGB(255, 0, 0));
	HB_Normal = CreateSolidBrush(RGB(240,240,240));
	HB_Yellow = CreateSolidBrush(RGB(32,32,32));
	HB_Posijet = CreateSolidBrush(RGB(0, 76, 153));
	HB_Green = CreateSolidBrush(RGB(0, 204, 0));
}