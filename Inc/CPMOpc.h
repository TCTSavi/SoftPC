#ifndef _CPMOPC_H_
#define _CPMOPC_H_

#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <Vector>
#include <string.h>
#include <windows.h>
#include "CLog.h"

struct SOpc {
	char Opc[25];
};

class CPLOpc {
	public:
		char Opcoes[25];
		std::vector<SOpc> OpcList;
	public:
		CPLOpc();
		~CPLOpc();
		void Load(FILE* FileHandle);
};

class CPMOpc {
	public:
		std::vector<CPLOpc> MOpcList;
	public:
		CPMOpc();
		~CPMOpc();
		void Load(char* File);
		CPLOpc* getOpcList(char* Opcoes);
		CPLOpc* getComPort();
		int getOpcID(char* Opcoes,char *opcao);
		char* getOpcStr(char* Opcoes,int ID);
		int getMaskReset(char* Opcoes);

};

#endif