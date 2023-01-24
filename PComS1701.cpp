#include "PComS1701.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	Initializing = true;
	if (!InitApplication(hinstance)) 
		return FALSE; 
	
	if (!InitInstance(hinstance, nCmdShow)) 
		return FALSE;

	while (GetMessage(&msg, (HWND) NULL, 0, 0)) 
	{ 
		//printf("%d : GetMessage msg->%X\n\n",count,msg);
		//count++;
		if (!IsDialogMessage(MainWindow, &msg)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
		}
	} 
	return msg.wParam; 
        UNREFERENCED_PARAMETER(lpCmdLine); 
}
