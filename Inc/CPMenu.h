#ifndef _CPMENU_H_
#define _CPMENU_H_

#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <sstream>
//#include <tchar.h>
#include <Vector>

#include "CPPar.h"
#include "CPMPar.h"
#include "CPMOpc.h"
#include "CLog.h"

class CPMenu {
    public:
        std::vector<CPPar> ParList;
		char		Nome[50];
		char		Menu[25];
		int 		x,y,w,h;
	public:
		CPMenu();
		~CPMenu();
		void Load(char* File);
		
};

#endif
