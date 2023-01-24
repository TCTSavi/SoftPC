#ifndef _CPPAR_H_
#define _CPPAR_H_

#define _WIN32_WINNT 0x0501

#include <tchar.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <winuser.h>
#include <Uxtheme.h>
#include <tmschema.h>


#include "CLog.h"
#include "CPMOpc.h"

enum {
	WHITECOLOR = 0,
	WARNCOLOR,
	OKCOLOR,
	WRONGCOLOR,
	GREYCOLOR,
	TESTVERCOLOR,
};

enum {
	PCIERROR = 0,
	PCIBUTTON,
	PCILEDIT,
	PCILCOMBOBOX,
	PCIBUTTONC,
	PCILOGC,
	PCILISTVIEWC,
	PCILABELC,
	PCIBUTOP,
	PCILEDITL,
	PCILEDITH,
	PCILABEL,
	PCIBUTTONCMACHINESTATUS,
	PCITABCONTROL,
	PCICOMBUFSENDBAR,
	PCICOMBUFSENDBARC,
	PCISTATUSC,
	PCISTATUSBIT,
	PCIERRORBIT,
	PCITESTEVERIFICACAO,
	PCITVBYTE,
	PCITVBIT,
	PCIATVBYTE,
	PCIATVBIT,
	PCISCROLLBARC,
	PCIERROROUTSET,
	PCIERROROUTRESET,
};

enum {
	FATERROR = 0,
	NOFAT,
	MMFAT,
	MMFAT200,
	MILISEC,
	HEXFAT,
	BITFAT,
};

class CExpPar{
	public:
	virtual void Draw(DRAWITEMSTRUCT* dis){};
	virtual	void Draw(HWND MainWindow,HWND hwndPar,bool bChange){};
	CExpPar();
};


enum {
	MachStat_Ok = 0,
	MachStat_Error,
	MachStat_Warm,
};

class CBMachStat: public CExpPar{
	public:
		HTHEME hTheme;
	public:
		int 				Modo;
		bool				bChange;
		RECT rchwnd,rcedit;
		HBRUSH HB_Color;
		HBRUSH HB_Error;
		HBRUSH HB_Normal;
		HBRUSH HB_Warm;
		HBRUSH HB_Ok;
		HBRUSH HB_Hollow;
		void Draw(HWND MainWindow,HWND hwndPar,bool bChange);
		HBRUSH GetModo();
		CBMachStat();
};

class CTab: public CExpPar{
	public:
		HBRUSH HB_Red;
		HBRUSH HB_Normal;
		HBRUSH HB_Yellow;
		HBRUSH HB_Posijet;
		HBRUSH HB_Green;
		void Draw(DRAWITEMSTRUCT* dis);
		CTab();
};


class CPPar {
	public:
		char		Nome[50];
		uint8_t		End;
		uint8_t 	Bit;
		char		Opcoes[25];
		char		Tipo[25];
		char		Fator[25];
		char		Valor[25];
		int			ID;
		int 		x,y,w1,h1,w2,h2;
		HANDLE 		Mutex;
		int			Color;
	public:
		CPPar();
		int getTipo();
		int getFator();
		char* getValor();
		bool setValor(char *Valor);
		CExpPar*	ExpPar;
};

#endif
