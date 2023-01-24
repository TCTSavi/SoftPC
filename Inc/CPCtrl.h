#ifndef _CPCTRL_H_
#define _CPCTRL_H_

#include <windows.h>
#include <commctrl.h>
#include <Vector>
#include <stdio.h>

#include "CPEixo.h"
#include "CPEPage.h"
#include "CPMenu.h"
#include "CPPar.h"
#include "CLog.h"
#include "CPMOpc.h"
#include "CPMPar.h"
#include "CPComm.h"
#include "CPMascErro.h"

enum {
   //States of routine (Rotina do fluxo principal A)
   PCtrlRAN0 = 0,
   PCtrlRANEnd,
};  

enum {
   //States of routine (Rotina do fluxo principal B)
   PCtrlRBN0 = 0,
   PCtrlRBN1,
   PCtrlRBN2,
   PCtrlRBNEnd,
};  

enum {
   //States of routine (Rotina do fluxo principal B)
   PCtrlRCN0 = 0,
   PCtrlRCN1,
   PCtrlRCN2,
   PCtrlRCNEnd,
};  

enum {
   //Configura CommPage
   PCtrlRDN0 = 0,
   PCtrlRDN1,
   PCtrlRDN2,
   PCtrlRDNEnd,
};  

enum {
   //Configura CommPage
   PCtrlREN0 = 0,
   PCtrlREN1,
   PCtrlREN2,
   PCtrlRENEnd,
};  



enum {
	CMD_SALVAUSER =0,
	CMD_SALVACONFIG,
	CMD_SENDALL,
};

struct PageOrder{
	int NEixo;
	int NPage;
};

class CPCtrl {
	private:
		int ID;
		void setID(std::vector<CPEPage>* _PageList);
		int giveID();
		HWND hwnd;
		bool reading;
		bool readOk;
		void LeLinha();
		void VerComando(char *Comando,int etapa);
		void VerDado();
		void VerFim();
		void PrtEtp();
		int  etapas;
		char Leitura[100];
		fpos_t Pos;
		FILE* FileHandle;
		
	public:
		std::vector<CPEixo> PEixoList;
		std::vector<CPEPage> PMainList;
		std::vector<CPComm> ListComm;
		std::vector<PageOrder> APage;		//Todas as paginas em ordem
		std::vector<PageOrder> APageUser;	//Todas as paginas de User em ordem
		std::vector<PageOrder> APageConfig;	//Todas as paginas de Config em ordem
		int GetEixoIndex(CPEixo* Eixo);			//Pega o indice do ponteiro em PEixoList
		std::vector<CPErro*> ListAxisError;
		void DelLastWarn();
		void DelAllWarn();
		HANDLE Thread;
		CPCtrl *PCtrl;
		double FTimer;
		double RtimerUse;
		bool Running;
		void RTimer(void* Param);		
		void InitAxis();
		void EndAxis();
		void SendToAxis(CPPar* Par);
	//Ferramentas
		bool TimerElapseEtap(int& Timer);
	public:
		int  EtapRA;
		void PCtrlRA00();		//
		void PCtrlRAEnd();		//
		void PCtrlRAError();		//Error	
	public:
		int  EtapRB;
		void PCtrlRB00();		//
		void PCtrlRB01();		//
		void PCtrlRB02();		//
		void PCtrlRBEnd();		//
		void PCtrlRBError();		//Error	
		int  Buffer;
		int  Send;
		int  TimerB;
	public:
		int  EtapRC;
		void PCtrlRC00();		//
		void PCtrlRC01();		//
		void PCtrlRC02();		//
		void PCtrlRCEnd();		//
		void PCtrlRCError();		//Error	
		int TimerC;
		int StatusOld;
		int Status;
		int StatusError;
		int GetStatus();
	public:
		int  EtapRD;
		void PCtrlRD00();		//
		void PCtrlRD01();		//
		void PCtrlRD02();		//
		void PCtrlRDEnd();		//
		void PCtrlRDError();		//Error	
	public:
		int  EtapRE;
		void PCtrlRE00();		//
		void PCtrlRE01();		//
		void PCtrlRE02();		//
		void PCtrlREEnd();		//
		void PCtrlREError();		//Error	
	public:		
		CPCtrl();
		~CPCtrl();
		CPPar* getPar(int ID);
		CPPar* getPar(int NPag,char* MenuName,char* ParNome);
		CPPar* getPar(char *AxisType,int NPag,char* ParNome);
		CPPar* getPar(int NEixo,const char* PagName,const char* MenuName,const char* ParName);
		HWND getHWND(int ID);
		void LoadEixos(char* File);
		void LoadMain(HWND _hwnd,char* File);
		bool Load_AxisFile(char* File,char *AxisType);
		void Save_AxisFile(const char* File,char *AxisType);
		void SetAParToHWND();
		void SetAHWNDToPar();
		void SetParToHWND(CPPar* Par);
		void SetHWNDToPar(CPPar* Par);
		void SetTVByteToBit(CPPar* Par);
		int sizeat(char* AxisType );// possibilidades .atc ou .atf
		CPEixo* GetAxis(int AxisNumber);
		CPEixo* GetAxis(std::vector<CPEixo>* _EixoList,int AxisNumber);
		CPEixo* GetAxis(CPPar* Par);
		CPEixo* GetAxis(CPEPage* Page);
		CPEPage* GetPage(CPPar* Par);
		CPEPage* GivePage(char* AxisType,int Pos);
		CPEPage* GivePage(int NPage);
		void Comm(CPPar* Par);
		void CommAll();
		void PParComAll(CPPar* Par);
		void ReceiveAll();
		CPMOpc* GetMOpc(CPPar* Par);
		int GetCommand(char* cmd);
		int GetNPages();
		void ClearCommPage();
		void SetCommPage(CPEPage* Page);
		void ResetError();
		void SetError();
};	
#endif

