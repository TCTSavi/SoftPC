#include "..\PComS1701.h"

#ifdef _UNICODE
wostringstream oss;
#else
ostringstream oss;
#endif

HWND MainWindow,ChildWindow;
CPCtrl PCtrl;
HANDLE hMonitor = 0;
HWND hwndTab;
TCITEM tie;
char achTemp[256];
RECT rcClient;				
HWND hwndStatic;
CPCI PCI;
CPCtrl Default_Ctrl;
bool Initializing;

BOOL InitApplication(HINSTANCE hinstance) 
{ 
	WNDCLASSEX wcx; 
		
	// Fill in the window class structure with parameters 
	// that describe the main window. 
	
	wcx.cbSize = sizeof(wcx);          		// size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; 		// redraw if size changes 
	wcx.lpfnWndProc = MainWndProc;     		// points to window procedure 
	wcx.cbClsExtra = 0;                		// no extra class memory 
	wcx.cbWndExtra = 0;                		// no extra window memory 
	wcx.hInstance = hinstance;         		// handle to instance 
	wcx.hIcon = LoadIcon(NULL,IDI_APPLICATION);  	// predefined app. icon 
	wcx.hCursor = LoadCursor(NULL,IDC_ARROW);     	// predefined arrow 
	wcx.hbrBackground = (HBRUSH)7;//COLOR_WINDOW-3; 	// white background brush 14 7 18
	wcx.lpszMenuName =  "MainMenu";    		// name of menu resource 
	wcx.lpszClassName = "MainWClass";  		// name of window class 
	wcx.hIconSm = (HICON)LoadImage(
		hinstance, 				// small class icon 
		MAKEINTRESOURCE(5),
		IMAGE_ICON, 
		GetSystemMetrics(SM_CXSMICON), 
		GetSystemMetrics(SM_CYSMICON), 
		LR_DEFAULTCOLOR);
	RegisterClassEx(&wcx);
	
	
    wcx.lpfnWndProc = ChildWndProc;
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wcx.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcx.lpszClassName = "ChildWClass";
    wcx.lpszMenuName = NULL;
    wcx.hIcon = NULL;
	RegisterClassEx(&wcx);

	return TRUE; 
	
} 

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow) 
{
//--------------------------------------------------------------------	
//Main Window
//--------------------------------------------------------------------	
	InitCommonControls();
//	SetWindowTheme(MainWindow, L" ", L" ");
	
	MainWindow = CreateWindow( 
        "MainWClass",			// name of window class 
        "PComS1701",			// title-bar string 
		//WS_OVERLAPPEDWINDOW | WS_EX_TRANSPARENT| WS_CAPTION  | WS_CLIPCHILDREN | WS_CAPTION,
        WS_OVERLAPPEDWINDOW | WS_EX_TRANSPARENT, 	// top-level window 
        MAINX,MAINY,MAINW,MAINH,// x,y,w,h 
        NULL,         			// no owner window 
        NULL,	    			// use class menu 
        hinstance,           	// handle to application instance 
        NULL					// no window-creation data 
	);      		
   	if (!MainWindow){
		MessageBox(
			NULL,
			(LPCSTR)"Erro ao criar ( Janela Principal ) ",
			(LPCSTR)"File = OnInit",
			MB_OK
		);
	}
	ShowWindow(MainWindow, nCmdShow); //nCmdShow
	//UpdateWindow(MainWindow);

//--------------------------------------------------------------------
	DMan::DM.OnInit();

	CLog::Log.OnInit(MainWindow);

	PCtrl.LoadEixos("PComS1701.cfd");
	
	PCtrl.LoadMain(MainWindow,"PComS1701.cfd");
	
	PCI.Load(MainWindow);

	PCI.MCtrl(&PCtrl,325,0,682,650);
	
	PCI.MMain(&PCtrl);
    
	Default_Ctrl = PCtrl;
    
	if (CLog::Log.FileOk("Config")){
		PCtrl.Load_AxisFile(CLog::Log.GetCurrentFile("Config"),"Config");
	}
	if (CLog::Log.FileOk("User")){
		PCtrl.Load_AxisFile(CLog::Log.GetCurrentFile("User"),"User");
	}
	
	PCtrl.SetAParToHWND();
    //
	PCI.ShowCtrl(&PCtrl.PEixoList[0].PageList[0]);	
	PCI.ShowCtrl(&PCtrl.PMainList[0]);
	
	PCtrl.InitAxis();
	PCtrl.SetCommPage(&PCtrl.PEixoList[0].PageList[0]);	
	
//--------------------------------------------------------------------	
	Initializing = false;
	
	return TRUE;
} 


