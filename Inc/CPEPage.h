#ifndef _CPEPAGE_H_
#define _CPEPAGE_H_

#include "windows.h"
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <Vector>

#include "CPMenu.h"
#include "CPMPar.h"
#include "CPMOpc.h"
#include "CLog.h"
#include "CPPorta.h"

class CRPar {
	public:
		std::vector<CPPar*> ParList;
		CPPar Par;
		uint16_t Dado;
	public:
		CRPar();
};

class CPEPage {
	public:
		CPMOpc MOpc;
		int  NEixo;
		char Nome[50];
		char File[50];
		char Tipo[50];
	public:
		std::vector<HWND> PHWNDList;
		std::vector<CPMenu> PMenuList;
        std::vector<CPMPar> MParList;
		std::vector<CRPar> RParList;
		std::vector<CRPar> ReadRParList;
		//Teste e verificação
		CPPar* AdressByte;
		CPPar* AdressBit;
		void SetBitTstVer(CPPar* Par);
		std::vector<CPPar> TesteVerList;
		void MakeRPar();
		void IncPages();
		CPEPage();
		~CPEPage();
		void Load();
		void LoadMPar();
		bool HasTesteVer(int IDbit);
		void ChangeTesteVer(int IDbit);
		bool Is_at_type(char *AxisType);// .atc ou .atf
		CPMPar* getMPar(const char* Valor);
		void ConvVtoD( const char * str, const char * format, ... );
};

#endif


