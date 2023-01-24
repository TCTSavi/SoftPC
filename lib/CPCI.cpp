#include "..\Inc\CPCI.h"

CPCI::CPCI() {

}

void CPCI::Load(HWND _hwnd){
	hwnd = _hwnd;
	TabID = -1;
//--------------------------------------------------------------------	
//Fonte para o botão grande	
//--------------------------------------------------------------------	
	const long nFontSize = 30;
	const char* fontName = "BigButton";
    HDC hdc = GetDC(hwnd);
	LOGFONT logFont = {0};
    logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    logFont.lfWeight = FW_NORMAL;
    strcpy(logFont.lfFaceName, fontName);
    HF_BigButton  = CreateFontIndirect(&logFont);
    ReleaseDC(hwnd, hdc);

	const long TSTVERnFontSize = 15;
	const char* TSTVERfontName = "TSTVERFont";
	HDC hdc2 = GetDC(hwnd);
	LOGFONT TSTVERlogFont = {0};
    TSTVERlogFont.lfHeight = -MulDiv(TSTVERnFontSize, GetDeviceCaps(hdc2, LOGPIXELSY), 100);
    TSTVERlogFont.lfWeight = FW_BOLD;
    strcpy(TSTVERlogFont.lfFaceName, TSTVERfontName);
    HF_TSTVERFont  = CreateFontIndirect(&TSTVERlogFont);
    ReleaseDC(hwnd, hdc2);
	
	
//--------------------------------------------------------------------	
//--------------------------------------------------------------------	
//Fonte para o botão grande	
//--------------------------------------------------------------------	
//--------------------------------------------------------------------	
}

void CPCI::MScrollBarC(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh){
	HWND HScrollBar,HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		Par->Nome,				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x,y-lh-2,lw,lh,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HScrollBar = CreateWindow( 
        WC_SCROLLBAR,       // global string containing name of window class
        Par->Nome,             // global string containing title bar text 
        WS_CHILD | WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN | SBS_HORZ, // window styles 
        x,y,ew,eh,					// x,y,w,h
        hwnd,					// no owner window 
        (HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
    ); 
	SetScrollRange(HScrollBar,SB_CTL,0,100,TRUE);
	//SetScrollPos(HScrollBar,SB_CTL,50,TRUE);
	EnableScrollBar(HScrollBar,SB_CTL,ESB_ENABLE_BOTH);
	PagC->PHWNDList.push_back(HScrollBar);
	PagC->PHWNDList.push_back(HLabel);
}

void CPCI::MButtonC(CPPar* Par,int x,int y,int w,int h){
	HWND HButton;
	HButton = CreateWindow( 
		WC_BUTTON,				// name of window class 
		Par->Nome,				// title-bar string 
		//WS_CHILD | WS_GROUP | WS_TABSTOP | BS_FLAT | WS_CLIPCHILDREN | BS_MULTILINE, 	// top-level window 
		WS_CHILD | WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN | BS_MULTILINE , 	// top-level window 
		x,y,w,h,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	//SendMessage(HButton, WM_SETFONT, (WPARAM)HF_BigButton , (LPARAM)MAKELONG(TRUE, 0));
	PagC->PHWNDList.push_back(HButton);
}

void CPCI::MStatusC(CPPar* Par,int x,int y,int w,int h){
	HWND HEdit;
	HEdit = CreateWindow( 
		WC_STATIC,				// name of window class 
		"Painel",				// title-bar string 
		WS_CHILD | SS_CENTER| SS_CENTERIMAGE |SS_ENDELLIPSIS|SS_SUNKEN, // top-level window 
		//WS_CHILD | WS_BORDER | WS_GROUP  | ES_RIGHT | ES_READONLY,// top-level window 
		x,y,w,h,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);	
	PagC->PHWNDList.push_back(HEdit);
	CLog::Log.SetStatusC(HEdit);
}

void CPCI::MBit(CPPar* Par,int x,int y,int w,int h){
	HWND HEdit,HLabel;
	HLabel = CreateWindow( 
		WC_BUTTON,				// name of window class 
		Par->Nome,				// title-bar string 
		WS_CHILD |BS_CHECKBOX | ES_LEFT, 	// top-level window 
		x,y,w,h,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HLabel);
}

void CPCI::MButtonCMachineStatus (CPPar* Par,int x,int y,int w,int h){
	HWND HButton;
	HButton = CreateWindow( 
		WC_BUTTON,				// name of window class 
		Par->Nome,				// title-bar string 
		//WS_CHILD |BS_OWNERDRAW| WS_GROUP | WS_TABSTOP | BS_FLAT | WS_CLIPCHILDREN | BS_MULTILINE, 	// top-level window 
		WS_CHILD| WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN | BS_MULTILINE |WS_EX_COMPOSITED , 	// top-level window 
		x,y,w,h,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	//SendMessage(HButton, WM_SETFONT, (WPARAM)HF_BigButton , (LPARAM)MAKELONG(TRUE, 0));
	PagC->PHWNDList.push_back(HButton);
	CBMachStat* BMachStat = new CBMachStat;
	Par->ExpPar = BMachStat;
	UpAnHWNDList.push_back( HButton );
}

void CPCI::MLabel(CPPar* Par,int x,int y,int w,int h){
	HWND HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		Par->Nome,				// title-bar string 
		WS_CHILD | WS_GROUP | SS_CENTERIMAGE| WS_TABSTOP | BS_FLAT | WS_CLIPCHILDREN, 	// top-level window 
		x,y,w,h,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HLabel);
}


void CPCI::MLogC(CPPar* Par,int x,int y,int w,int h){
	HWND HLog;
		HLog = CreateWindow( 
		WC_EDIT,				// name of window class 
		"",						// title-bar string 
		WS_CHILD | WS_BORDER | ES_LEFT | ES_READONLY | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL,// top-level window 
		x,y,w,h,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);	
	PagC->PHWNDList.push_back(HLog);
	CLog::Log.SetLogConsole(HLog);
}

void CPCI::MListViewC(CPPar* Par,int x,int y,int w,int h){
	HWND HListView;
		HListView = CreateWindow( 
		WC_LISTVIEW,			// name of window class 
		"",						// title-bar string 
//		WS_CHILD | LVS_EDITLABELS,// top-level window 
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS,// top-level window 
		x,y,w,h-30,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HListView);
	
	HWND HButton1;
	HButton1 = CreateWindow( 
		WC_BUTTON,				// name of window class 
		"Limpar ultimo",				// title-bar string 
		WS_CHILD | WS_GROUP | WS_TABSTOP, 	// top-level window 
		x+w-100,y+h-25,100,25,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HButton1);
	
	HWND HButton2;
	HButton2 = CreateWindow( 
		WC_BUTTON,				// name of window class 
		"Limpar todos",				// title-bar string 
		WS_CHILD | WS_GROUP | WS_TABSTOP, 	// top-level window 
		x+w-205,y+h-25,100,25,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HButton2);
	
	WCHAR szText[256];			// Temporary buffer.
    LVCOLUMN lvc;
    int iCol;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.iSubItem = 0;
	lvc.pszText = "Origem";
	lvc.cx = 0.2*w;
	lvc.fmt = LVCFMT_LEFT; 
	ListView_InsertColumn(HListView, 0, &lvc);
	lvc.cx = 0.15*w;
	lvc.pszText = "Cod.";
	lvc.iSubItem = 1;
	ListView_InsertColumn(HListView, 1, &lvc);
	lvc.cx = 0.65*2*w;
	lvc.pszText = "Mensagem";
	lvc.iSubItem = 2;
	ListView_InsertColumn(HListView, 2 ,&lvc);
	CLog::Log.SetLogWarn(HListView);	
}

void CPCI::MButton(CPPar* Par,int x,int y,int w,int h){
	HWND HButton;
	HButton = CreateWindow( 
		WC_BUTTON,				// name of window class 
		Par->Nome,				// title-bar string 
		//WS_CHILD |WS_VISIBLE |BS_PUSHBUTTON | BS_OWNERDRAW, 	// top-level window 
		WS_CHILD | WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN, 	// top-level window 
		x,y,w,h,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HButton);
}

void CPCI::MComBufSendBar(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh){
	HWND HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		"1000/1000",				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE,  	// top-level window 
		x,y+2,lw,lh-4,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HLabel);
	EixoC->HBarLabel = HLabel;
	
	HWND HCBSBar;
	HCBSBar = CreateWindow( 
		PROGRESS_CLASS,				// name of window class 
		Par->Nome,				// title-bar string 
		//WS_CHILD |WS_VISIBLE |BS_PUSHBUTTON | BS_OWNERDRAW, 	// top-level window 
		WS_CHILD | WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN, 	// top-level window 
		x+lw+5,y,ew,eh,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	SendMessage(HCBSBar,PBM_SETPOS,(WPARAM)20,(LPARAM)0);
	PagC->PHWNDList.push_back(HCBSBar);
	EixoC->HBarComSStatus = HCBSBar;
	
}

void CPCI::MComBufSendBarC(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh){
	HWND HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		"1000/1000",				// title-bar string 
		WS_CHILD | SS_CENTERIMAGE,  	// top-level window 
		x,y+2,lw,lh-4,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HLabel);
	CLog::Log.SetBarLabel(HLabel);
	
	HWND HCBSBar;
	HCBSBar = CreateWindow( 
		PROGRESS_CLASS,				// name of window class 
		Par->Nome,				// title-bar string 
		//WS_CHILD |WS_VISIBLE |BS_PUSHBUTTON | BS_OWNERDRAW, 	// top-level window 
		WS_CHILD | WS_GROUP | WS_TABSTOP | WS_CLIPCHILDREN, 	// top-level window 
		x+lw+5,y,ew,eh,					// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	SendMessage(HCBSBar,PBM_SETPOS,(WPARAM)20,(LPARAM)0);
	PagC->PHWNDList.push_back(HCBSBar);
	CLog::Log.SetBarComSStatus(HCBSBar);
}

void CPCI::MTVerif(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh){
	//Inicio
	int IDC = 0;
	HWND HEditInicio,HLabelInicio,HLabelh;
	HLabelInicio = CreateWindow( 
		WC_STATIC,				// name of window class 
		"Inicio:",				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x,y,45,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HLabelh = CreateWindow( 
		WC_STATIC,				// name of window class 
		"h",				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x+84,y,10,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HEditInicio = CreateWindow( 
		WC_EDIT,				// name of window class 
		Par->Valor,						// title-bar string 
		WS_CHILD | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_RIGHT,// top-level window 
		x+42,y,40,20,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(HEditInicio);
	PagC->PHWNDList.push_back(HLabelInicio);
	PagC->PHWNDList.push_back(HLabelh);
	
	//End
	HWND HLabelEndName,HLabelEnd;
	HLabelEndName = CreateWindow( 
		WC_STATIC,				// name of window class 
		"End.",					// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x,y+25,45,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HLabelEnd = CreateWindow( 
		WC_STATIC,				// name of window class 
		PagC->TesteVerList[IDC].Valor,					// title-bar string 
		WS_CHILD| SS_CENTERIMAGE| ES_RIGHT, 	// top-level window 
		x,y+45,25,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	IDC++;	
	PagC->PHWNDList.push_back(HLabelEnd);
	PagC->PHWNDList.push_back(HLabelEndName);
	//Valores
	int XLZero = x+25;
	int YLZero = y+25;
	int XEZero = x+40;
	int YEZero = y+45;
	std::string Name;
	char Col[10];
	for (char i = 0 ;i < 8;i++){
		HWND HLabelCol,HLabelValor;
		Name = itoa(i,Col,16);
		HLabelCol = CreateWindow( 
			WC_STATIC,				// name of window class 
			Name.c_str(),					// title-bar string 
			WS_CHILD| ES_RIGHT| SS_CENTERIMAGE, 	// top-level window 
			XLZero+(i*50),YLZero,48,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)Par->ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		HLabelValor = CreateWindow( 
			WC_EDIT,				// name of window class 
			"FF",					// title-bar string 
			WS_CHILD| WS_BORDER| SS_CENTERIMAGE | ES_CENTER | WS_TABSTOP, 	// top-level window 
			XEZero+(i*50),YEZero,48,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		IDC++;
		//SendMessage(HLabelCol, WM_SETFONT, (WPARAM)HF_TSTVERFont , (LPARAM)MAKELONG(TRUE, 0));
		//SendMessage(HLabelValor, WM_SETFONT, (WPARAM)HF_TSTVERFont , (LPARAM)MAKELONG(TRUE, 0));
		PagC->PHWNDList.push_back(HLabelCol);
		PagC->PHWNDList.push_back(HLabelValor);
	}

	for (char i = 0 ;i < 8;i++){
		HWND HLabelCol,HLabelValor;
		Name = itoa(i+8,Col,16);
		HLabelCol = CreateWindow( 
			WC_STATIC,				// name of window class 
			Name.c_str(),					// title-bar string 
			WS_CHILD| ES_RIGHT| SS_CENTERIMAGE, 	// top-level window 
			XLZero+(i*50),YLZero+40,48,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)Par->ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		HLabelValor = CreateWindow( 
			WC_EDIT,				// name of window class 
			"FF",					// title-bar string 
			WS_CHILD| WS_BORDER| SS_CENTERIMAGE | ES_CENTER | WS_TABSTOP, 	// top-level window 
			XEZero+(i*50),YEZero+40,48,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		IDC++;
		//SendMessage(HLabelCol, WM_SETFONT, (WPARAM)HF_TSTVERFont , (LPARAM)MAKELONG(TRUE, 0));
		//SendMessage(HLabelValor, WM_SETFONT, (WPARAM)HF_TSTVERFont , (LPARAM)MAKELONG(TRUE, 0));
		PagC->PHWNDList.push_back(HLabelCol);
		PagC->PHWNDList.push_back(HLabelValor);
	}

	

	//Bit End.
	HWND HLabelBitName,HLabelBit;
	HLabelBitName = CreateWindow( 
		WC_STATIC,				// name of window class 
		"Bit",					// title-bar string 
		WS_CHILD| SS_CENTERIMAGE| ES_RIGHT, 	// top-level window 
		x,y+120,25,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HLabelBit= CreateWindow( 
		WC_STATIC,				// name of window class 
		PagC->TesteVerList[IDC].Valor,					// title-bar string 
		WS_CHILD| SS_CENTERIMAGE| ES_RIGHT, 	// top-level window 
		x,y+140,25,20,				// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	IDC++;	
	PagC->PHWNDList.push_back(HLabelBit);
	PagC->PHWNDList.push_back(HLabelBitName);
	//Bits
	XLZero = x+36;
	YLZero = y+120;
	XEZero = x+40;
	YEZero = y+140;
	for (char i = 15 ;i >= 0;i--){
		int j = i/4;
		HWND HLabelBitCol,HLabelBitValor;
		Name = itoa(15-i,Col,10);
		HLabelBitCol = CreateWindow( 
			WC_STATIC,				// name of window class 
			Name.c_str(),					// title-bar string 
			WS_CHILD| ES_RIGHT | SS_CENTERIMAGE, 	// top-level window 
			XLZero+(i*23)+(j*10),YLZero,21,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		HLabelBitValor = CreateWindow( 
			WC_EDIT,				// name of window class 
			"0",					// title-bar string 
			WS_CHILD| WS_BORDER| SS_CENTERIMAGE | ES_RIGHT | WS_TABSTOP, 	// top-level window 
			XEZero+(i*23)+(j*10),YEZero,21,20,				// x,y,w,h
			hwnd,					// no owner window 
			(HMENU)PagC->TesteVerList[IDC].ID,			// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
			NULL					// no window-creation data		
		);
		IDC++;	
		PagC->PHWNDList.push_back(HLabelBitValor);
		PagC->PHWNDList.push_back(HLabelBitCol);
	}
}

void CPCI::MLEdit(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh){
	HWND HEdit,HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		Par->Nome,				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x,y+2,lw,lh,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HEdit = CreateWindow( 
		WC_EDIT,				// name of window class 
		"",						// title-bar string 
		WS_CHILD | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_RIGHT,// top-level window 
		x+lw+5,y,ew,lh,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);	
	PagC->PHWNDList.push_back(HEdit);
	PagC->PHWNDList.push_back(HLabel);
}

void CPCI::MLCombobox(CPPar* Par,int x,int y,int lw,int lh,int cw,int ch){
	HWND HCombobox,HLabel;
	HLabel = CreateWindow( 
		WC_STATIC,				// name of window class 
		Par->Nome,				// title-bar string 
		WS_CHILD| SS_CENTERIMAGE, 	// top-level window 
		x,y+2,lw,lh,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	HCombobox=CreateWindow(
		WC_COMBOBOX, 
		"", 
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_GROUP | WS_TABSTOP,
		x+lw+5,y,cw,ch, 
		hwnd,(HMENU)Par->ID,
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL
	);
	PagC->PHWNDList.push_back(HCombobox);
	PagC->PHWNDList.push_back(HLabel);
	HWND hwndEdit = GetWindow(HCombobox, GW_CHILD);
	SetWindowLong(hwndEdit, GWL_ID, Par->ID); 
	CPLOpc *LOpc = PagC->MOpc.getOpcList(Par->Opcoes);	
	if (LOpc == NULL) {
		//CLog::Log.SetErrorStatus( CLOGERROR_OPCMENU,"%s",Par->Opcoes);
		//CLog::Log.SetErrorStatus( CLOGERROR_OPCMENU);
		//CLog::Log.SetErrorStatus( CLOGERROR_OPCMENU );		
		return;
	}
	for (int i=0;i<LOpc->OpcList.size();i++){
		SendMessage(HCombobox,CB_ADDSTRING,(WPARAM)0,(LPARAM)LOpc->OpcList[i].Opc);
	}
	SendMessage(HCombobox,CB_SETCURSEL,(WPARAM)0, (LPARAM)0);	
	//HCombobox.setBackground
}

void CPCI::MMenu(CPMenu* Menu,int x,int y){
	HWND Hmenu;
	if ( Menu->w == 0 && Menu->h == 0 ){
		//Menu oculto
		return;
	}
	Hmenu = CreateWindow( 
		WC_BUTTON,				// name of window class 
		Menu->Nome,				// title-bar string 
		WS_CHILD | BS_GROUPBOX , 	// top-level window 
		Menu->x+x,Menu->y+y,Menu->w,Menu->h,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)NULL,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	PagC->PHWNDList.push_back(Hmenu);
	for (int i=0; i< Menu->ParList.size();i++){
		switch (Menu->ParList[i].getTipo()){
			case PCILOGC:{
						MLogC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCISCROLLBARC:{
						MScrollBarC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCIBUTTONC: {
						MButtonC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCIERRORBIT: 
			case PCISTATUSBIT: {
						MBit(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;			
			case PCISTATUSC: {
						MStatusC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;			
			case PCIBUTTON: {
				MButton(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCICOMBUFSENDBAR: {
				MComBufSendBar(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCICOMBUFSENDBARC: {
				MComBufSendBarC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCILEDIT: {
				MLEdit(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCILCOMBOBOX: {
				MLCombobox(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCILISTVIEWC: {
					MListViewC(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCILABELC: {
					MLabel(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCILABEL: {
					MLabel(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCIBUTOP: {
				MButton(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCILEDITL: {
				MLEdit(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCILEDITH: {
				MLEdit(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			case PCIBUTTONCMACHINESTATUS: {
						MButtonCMachineStatus(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1
				);
			}
			break;
			case PCITESTEVERIFICACAO: {			
				MTVerif(&Menu->ParList[i],
						Menu->x+x+Menu->ParList[i].x,
						Menu->y+y+Menu->ParList[i].y,
						Menu->ParList[i].w1,
						Menu->ParList[i].h1,
						Menu->ParList[i].w2,
						Menu->ParList[i].h2
				);
			}
			break;
			default:{
			}
			break;
		}
	}
}

void CPCI::MEixo(CPEixo* Eixo,CPEPage* Pag,int x,int y){
	PagC = Pag;
	EixoC = Eixo;
	std::string str;
	char NEixo[50];
	tie.mask = TCIF_TEXT;
	str = itoa(EixoC->Number,NEixo,10);
	str += ":";
	str += PagC->Nome;
	tie.pszText = const_cast<char *>(str.c_str());
	TabCtrl_InsertItem(HTab,giveTabID(),&tie);
	for (int i=0; i< PagC->PMenuList.size();i++){
		MMenu(&PagC->PMenuList[i],x,y);	
	}
}

int CPCI::giveTabID(){
	TabID++;
	return TabID;
}

void CPCI::MCtrl(CPCtrl* Ctrl,int x,int y ,int w,int h){
	CPPar* Par = Ctrl->getPar(0,"Controle Principal","MTABCONTROL","Par Tab Control");
	if (Par == NULL){
		printf("Nao encontrou o paramentro do Tab Control\n");
		return;
	}
	
	HTab=CreateWindow( 
		WC_TABCONTROL,			// name of window class 
		"",				// title-bar string 
		//WS_CHILD | TCS_OWNERDRAWFIXED |WS_CLIPSIBLINGS | WS_VISIBLE, 	// top-level window 
		WS_CHILD | TCS_OWNERDRAWFIXED | WS_VISIBLE, 	// top-level window 
		x,y,w,h,			// x,y,w,h
		hwnd,					// no owner window 
		(HMENU)Par->ID,			// use class menu 
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),	// handle to application instance 
		NULL					// no window-creation data		
	);
	for (int i=0; i< Ctrl->APage.size();i++){
		MEixo(&Ctrl->PEixoList[Ctrl->APage[i].NEixo],&Ctrl->PEixoList[Ctrl->APage[i].NEixo].PageList[Ctrl->APage[i].NPage],x,y);
	}
	CTab* Tab = new CTab;
	Par->ExpPar = Tab;
}

void CPCI::ShowCtrl(CPEPage* Pag){
	for (int i = 0; i < Pag->PHWNDList.size();i++){
		ShowWindow(Pag->PHWNDList[i],SW_SHOW);
	}
}

void CPCI::UShowCtrl(CPEPage* Pag){
	for (int i = 0; i < Pag->PHWNDList.size();i++){
		ShowWindow(Pag->PHWNDList[i],SW_HIDE);
	}
}

void CPCI::MMain(CPCtrl* Ctrl){
	PagC = &Ctrl->PMainList[0];
	for (int i=0; i< PagC->PMenuList.size();i++){
		MMenu(&PagC->PMenuList[i],0,0);	
	}
}

CPPar& CPCI::SetPar(CPPar* Par){
	switch (Par->getTipo()){
		case PCILOGC:{
		}
		break;
		case PCIBUTTONC: {
		}
		break;
		case PCIBUTTON: {
		}
		break;
		case PCILEDIT: {
		}
		break;
		case PCILCOMBOBOX: {
		}
		break;
		case PCILISTVIEWC: {
		}
		break;
		case PCILABELC: {
		}
		break;
		case PCILABEL: {
		}
		break;
		case PCIBUTOP: {
		}
		break;
		case PCILEDITL: {
		}
		break;
		case PCILEDITH: {
		}
		break;
		case PCIBUTTONCMACHINESTATUS: {
		}
		break;
		default:{
		}
		break;
	}	
}