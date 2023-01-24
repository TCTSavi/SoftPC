#ifndef _CPPORTA_H_
#define _CPPORTA_H_

#include <windows.h>
#include <Vector>
#include "CLog.h"
#include <string>
#define TIMEOUT	400

class CPPorta {
	public:
		HANDLE hCom;
		HANDLE PortaMutex;
		COMMTIMEOUTS timeouts;
		char PortName[12];
		int TimerOutInterno;
		int StartReadTime;
	public:
		CPPorta();
		int OnInit();	//Retorna 0 se Ok, ou retorna o
		void OnEnd();
		bool GetTimeOutError();
		bool Read(unsigned char * lpBuf, DWORD* dwRead);
		bool Write(unsigned char * lpBuf, DWORD dwToWrite);
		void SetName(const char* Name);
		void FreehCom();
};	

#endif
