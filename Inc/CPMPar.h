#ifndef _CPMPAR_H_
#define _CPMPAR_H_

#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <sstream>
//#include <tchar.h>
#include <Vector>

#include "CPPar.h"
#include "CLog.h"

class CPCPar {
    public:
		int			NPage;
		char		Menu[25];
		char		Par[25];
	public:
		CPCPar();
		~CPCPar();
};


class CPMPar {
    public:
		std::vector<CPCPar> CParList;
		char		Tipo[50];
		char		Valor[25];
	public:
		CPMPar();
		~CPMPar();
		void Load(char* File);
};

#endif
