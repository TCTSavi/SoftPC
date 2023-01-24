#ifndef _SERIAL_V01_H_
#define _SERIAL_V01_H_

#include <windows.h>
#include <Vector>
#include "CLog.h"
#include <string>

class CPPorta {
	public:
		void Teste(void* Param );
	public:
		HANDLE hCom;
		HANDLE PThread;
		COMMTIMEOUTS timeouts;
		char PortName[12];
	public:
		CPPorta();
		void OnInit();
		void OnEnd();
		void Read();
		void Write(int * lpBuf, DWORD dwToWrite);
};	

class CPSerial {
	public:
		std::vector<CPPorta> PortList;
	public:
		CPSerial();
		void NewPort(const char* PortName);
		void OnInit();
		void OnEnd();
};	

#endif
