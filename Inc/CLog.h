#ifndef _CLOGSUM_H_
#define _CLOGSUM_H_

#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <windows.h>
#include <commctrl.h>
#include "..\Define.h"
#include <Vector>

using namespace std;

class CLErro{
	public:
		CLErro();
		int NEixo;
		int Cod;
};

struct CLogSave{
	public:
		char C_User_File[256];
		char C_Config_File[256];
		RECT MainRc;
};

enum {
   //States of the main program
   LOG_OK = 0,
   LOG_WARN,
   LOG_ERROR,
   LOG_WAIT,
};  

class CLog {
	public:
		static CLog Log;
		char buffer[256];
		HANDLE 		Mutex;
		HWND hwnd;
		HWND Console;
		HWND Warn;
		HWND HBarComSStatus;		
		HWND HBarLabel;
		HWND StatusC;
		bool ConsoleIni;
		bool WarnIni;
		void display();
		ostringstream oss;
		CLogSave LogSave;
		int Status;
	public:
		CLog();
		std::vector<CLErro> ListAxisError;
		void Add( const char* format, ... );
		void OnInit(HWND _hwnd);
		void OnEnd();
		bool FileOk(char *AxisType);
		char* GetCurrentFile(char *AxisType);
		void SetCurrentFile (const char* File,char *AxisType);
		void SetLogConsole(HWND hwnd);
		void SetLogWarn(HWND hwnd);
		void SetBarComSStatus(HWND hwnd);
		void SetBarLabel(HWND hwnd);
		void SetStatusC(HWND hwnd);
		void SetFileName(); //Define o texto na barra superior da janela
		void InsertWarn(const char* Origem,int Cod,const char* Men);
		void RemoveWarn(int Cod);
		void DelLastWarn();
		void DelAllWarn();
};

#endif
