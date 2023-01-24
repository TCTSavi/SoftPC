#ifndef _CPMASCERRO_H_
#define _CPMASCERRO_H_

#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <Vector>
#include <string.h>
#include "CLog.h"
#include "CPPar.h"

enum {
	//Erros do programa
	CLOGERROR_MAINPARAXIS =0,
	CLOGERROR_FINDPORTA,
	CLOGERROR_INITPORTA,
	CLOGERROR_PORTANC,
	CLOGERROR_OPCMENU,
	CLOGERROR_DEFCANAL,
	CLOGERROR_DEFFATOR,
	CLOGERROR_DEFPGIRO,
	CLOGERROR_TIMEIN,
	CLOGERROR_PROTOCOLO,
	CLOGERROR_DEFSTATUS,
	CLOGERROR_DEFFERROR,
	CLOGERROR_PLACA,
	CLOGERROR_DEFERROROUT,
};  

//#pragma pack(push, 1)
class CPErro{
	public:
		CPErro();
		CPPar* 	Par;
		bool 	Status;
		char 	Origem[50];
		int 	Cod;
		char 	Men[128];
		char 	Comments[128];
		int 	Level;
};
//#pragma pack(pop)

class CPMErro {
	public:
		std::vector<CPErro> ErrorTable;
		std::vector<CPErro*> ListError;		
	public:
		CPMErro();
		void Init();
		void SetError(int Cod,char* Origem,char* Men);
		void SetError(CPPar* Par);
		void SetErrorStatus(int Cod);
		void SetErrorStatus(CPPar* Par);
		void SetErrorStatus(int Cod,const char* Comments,...);
		void SetErrorStatus(CPPar* Par,const char* Comments,...);
		void ResetErrorStatus(int Cod);
		void ResetErrorStatus(CPPar* Par);
		bool GetErrorStatus(int Cod);
		bool GetErrorStatus(CPPar* Par);
		CPErro* GetLastError();
};

#endif