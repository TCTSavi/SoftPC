#ifndef _PCOMS1701_H_
#define _PCOMS1701_H_

/*
#ifndef UNICODE
#define UNICODE
#endif 
*/
#define _WIN32_IE 0x301
#define _WIN32_WINNT 0x0501
//#define WINVER 0x501 

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <commctrl.h>
#include <sstream>
#include <string>
#include <stdint.h>
#include <tchar.h>
#include <Vector>
#include <functional> 
#include <winuser.h>
#include <Uxtheme.h>
#include <tmschema.h>



//Meus Includes
#include "Define.h"
#include "Inc\CPCI.h"
#include "Inc\CPMOpc.h"
#include "Inc\CPPar.h"
#include "Inc\CPMenu.h"
#include "Inc\CPEPage.h"
#include "Inc\CPEixo.h"
#include "Inc\CPCtrl.h"
#include "Inc\CLog.h"
#include "Inc\CPMPar.h"
#include "Inc\CPComm.h"
#include "Inc\CPMascErro.h"
#include "Inc\CPEpage.h"

extern HWND MainWindow;
extern HWND	ChildWindow;
extern int contador;
extern HANDLE hMonitor;
extern DWORD count;
extern HWND hwndStatic;
extern CPEixo PEixo;
extern CPCtrl PCtrl;
extern CPCtrl Default_Ctrl;
extern CPCI PCI;
extern int XMouseMain,YMouseMain;
extern char* FileName_apf;
extern char* FileName_acf;
extern bool Initializing;

#define IDT_TIMER1	0x100

using namespace std;

#ifdef _UNICODE
//extern stringstream oss;
extern wostringstream oss;
#else
//extern stringstream oss;
extern ostringstream oss;
#endif

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
BOOL InitApplication(HINSTANCE); 
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
void OnEnd(); 

BOOL InitInstance(HINSTANCE, int); 
DWORD WINAPI fMonitor();

void MMenus(HWND hwnd);
void OpenFile(HWND hwnd,char* AxisType,char *Filter);
void Save(HWND hwnd,char* AxisType,char *Filter);
void SaveAs(HWND hwnd,char* AxisType,char *Filter);
void NewFile(HWND hwnd,char* AxisType);
void Teste(HWND hwnd);
char* GetFileExt(const char* AxisType );

#endif