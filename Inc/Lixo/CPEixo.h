#ifndef _CPEIXO_H_
#define _CPEIXO_H_

#include "windows.h"
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <Vector>

#include "CPRTimer.h"
#include "CPMenu.h"
#include "CPMPar.h"
#include "CPMOpc.h"
#include "CLog.h"
#include "CPPorta.h"
#include "CPMascErro.h"

class CPEixo {
	public:
		CPMOpc MOpc;
		int  Eixo;
		char Nome[50];
		char File[50];
		char Tipo[50];
		CPPorta Porta;
		int Canal;
		float FatorPulso_mm;
		int PulsoVolta;
		char* GetCanal();
		int GetEnd();
		int GetLei();
		char* GetFator();
		char* GetPulsoVolta();
		char* GetPorta();
		HWND GetHWND(int ID);
		//CPRTimer MainTimer01;
	public:
		std::vector<HWND> PHWNDList;
		std::vector<CPMenu> PMenuList;
        std::vector<CPMPar> MParList;
		CPMErro MErros;
		CPEixo();
		~CPEixo();
		bool Is_at_type(char *AxisType);// .atc ou .atf
		void Load();
		void LoadMPar();
		CPMPar* getMPar(const char* Valor);
};

#endif


