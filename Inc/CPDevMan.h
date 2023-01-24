#ifndef _CPDEVMAN_H_
#define _CPDEVMAN_H_

#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <windows.h>
#include <commctrl.h>
#include "..\Define.h"
#include <Vector>

#include "CPPorta.h"
#include "CPMascErro.h"

class DMan {
	public:
		static DMan DM;
		HANDLE ThreadTime;

	public:
		DMan();
		void OnInit();
		std::vector<CPPorta*> PortList;
		CPPorta* GetPort(const char* PortName);
		void FreePort(CPPorta* Porta);
		void OnEnd();
};

#endif
