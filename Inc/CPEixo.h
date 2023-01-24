#ifndef _CPEIXO_H_
#define _CPEIXO_H_

#include "windows.h"
#include <tchar.h>
#include <stdint.h>
#include <stdio.h>
#include <Vector>

#include "CPEPage.h"
#include "CPMenu.h"
#include "CPMPar.h"
#include "CPMOpc.h"
#include "CLog.h"
#include "CPPorta.h"
#include "CPComm.h"
#include "CPMascErro.h"
#include "CPDevMan.h"

//Inicialização da porta serial
enum {
   EixoRAN0 = 0,
   EixoRAN1,
   EixoRAN2,
   EixoRAN3,
   EixoRAN4,
   EixoRAN5,
   EixoRANEnd,
};

//Inicialização do canal
enum {
   EixoRBN0 = 0,
   EixoRBN1,
   EixoRBN2,
   EixoRBNEnd,
};

//Inicialização do Fator
enum {
   EixoRCN0 = 0,
   EixoRCN1,
   EixoRCN2,
   EixoRCNEnd,
};

//Inicialização do Pulso/Volta
enum {
   EixoRDN0 = 0,
   EixoRDN1,
   EixoRDN2,
   EixoRDNEnd,
};

//Inicializa comunicação
enum {
   EixoREN0 = 0,
   EixoREN1,
   EixoREN2,
   EixoREN3,
   EixoREN4,
   EixoREN5,
   EixoREN6,
   EixoRENEnd,
};

//Status Envio
enum {
   EixoRFN0 = 0,
   EixoRFN1,
   EixoRFN2,
   EixoRFNEnd,
};

//Tratamento de comandos e envios
enum {
   EixoRGN0 = 0,
   EixoRGN1,
   EixoRGN2,
   EixoRGN3,
   EixoRGNEnd,
};

//Fifo IN
enum {
   EixoRHN0 = 0,
   EixoRHN1,
   EixoRHN2,
   EixoRHN3,
   EixoRHNEnd,
};

//Inicialização do Status
enum {
   EixoRIN0 = 0,
   EixoRIN1,
   EixoRIN2,
   EixoRINEnd,
};

//Inicialização do Flag de Erro
enum {
   EixoRJN0 = 0,
   EixoRJN1,
   EixoRJN2,
   EixoRJNEnd,
};

//Verefica ErrorBit
enum {
   EixoRLN0 = 0,
   EixoRLN1,
   EixoRLN2,
   EixoRLN3,
   EixoRLN4,
   EixoRLN5,
   EixoRLN6,
   EixoRLN7,
   EixoRLNEnd,
};

//Verifica Erros na Placa
enum {
   EixoRMN0 = 0,
   EixoRMN1,
   EixoRMN2,
   EixoRMNEnd,
};

//Inicialização do ErrorOut
enum {
   EixoRNN0 = 0,
   EixoRNN1,
   EixoRNN2,
   EixoRNNEnd,
};

class CPEixo {
	public:
		int  Number;
		char *PortName;
		CPComm Comm;
		int Canal;
		float FatorPulso_mm;
		int PulsoVolta;
		char* GetValor(const char* Option);//"GetComOp" "DefCanal" "MENFAT" "PGiro"
		CPPar* GetParByOption(const char* Option);
		HWND hwnd;
	public:
		CPEixo();
		~CPEixo();
		std::vector<CPEPage> PageList;
		std::queue<CPPar*> FIFOParCmd;
		std::vector<CRPar> RParList;
		std::vector<CPPar*> ErrorBitList;
		bool PushParCmd(CPPar* Par);
		CPMErro MErros;
		void Load(HWND _hwnd);
		void CommTS(CPPar* Par);
		void PParComAll(CRPar* RPar);
		void PParComAllReadPage(CPEPage* Page);
		void AllComPPar(std::vector<CRPar>* RParL,CPPar* Par,uint16_t Dado);
		void CommTSAll();
		void CommSer(CPPar* Par,int Option,uint16_t* Dado,int _Canal);
		CPPar* ParToSend;
		CPMOpc* GetMOpc(CPPar* Par);
		uint16_t ConvValToD(CPPar* Par);
		void ConvDToVal(CPPar* Par,uint16_t Dado);
		void MakeRPar();
		void GetErrorPar();
		CPPar* ErrorBit;
	//Ferramentas
		bool TimerElapseEtap(int& Timer);
		void ConvReceiveD(char* buffer,const char * format, ...);
		void ConvVtoD( const char * str, const char * format, ... );
	//Controle do Fluxo do eixo
		HANDLE Thread;
	public:
		CPEixo *Eixo;
		double FTimer;
		double RtimerUse;
		bool Running;
		void RTimer(void* Param);
		void InitAxis();
		void EndAxis();
		void SetRT(int *RTState,int StateNumber);
	public:
	//Inicialização da porta serial
		int  EtapRA;
		void EixoRA00();		//
		void EixoRA01();		//
		void EixoRA02();		//
		void EixoRA03();		//
		void EixoRA04();		//
		void EixoRA05();		//
		void EixoRAEnd();		//
		void EixoRAError();		//Error	
		void SetRTChangePort();
	public:
	//Inicialização do Canal
		int  EtapRB;
		void EixoRB00();		//
		void EixoRB01();		//
		void EixoRB02();		//
		void EixoRBEnd();		//
		void EixoRBError();		//Error	
		void SetRTChangeCanal();
	//Inicialização do fator
		int  EtapRC;
		void EixoRC00();		//
		void EixoRC01();		//
		void EixoRC02();		//
		void EixoRCEnd();		//
		void EixoRCError();		//Error	
		void SetRTChangeFator();	
	//Inicialização do Pulso/Volta
		int  EtapRD;
		void EixoRD00();		//
		void EixoRD01();		//
		void EixoRD02();		//
		void EixoRDEnd();		//
		void EixoRDError();		//Error	
		void SetRTChangePGiro();			
	//Inicializa comunicação
		int  EtapRE;
		void EixoRE00();		//
		void EixoRE01();		//
		void EixoRE02();		//
		void EixoRE03();		//
		void EixoRE04();		//
		void EixoRE05();		//
		void EixoRE06();		//
		void EixoREEnd();		//
		void EixoREError();		//Error	
		void SetRTSendAll();
		void SetRTSend(CPPar* Par);
		int  TimerE;
		int  TimerS;
	//Status envio
		int  EtapRF;
		void EixoRF00();		//
		void EixoRF01();		//
		void EixoRF02();		//
		void EixoRFEnd();		//
		void EixoRFError();		//Error	
		HWND HBarComSStatus;
		HWND HBarLabel;
		int  Buffer;
		int  Send;
		int  HBarPos;
		int  TimerF;
	//Tratamento de comandos e envios
		int  EtapRG;
		void EixoRG00();		//
		void EixoRG01();		//
		void EixoRG02();		//
		void EixoRG03();		//
		void EixoRGEnd();		//
		void EixoRGError();		//Error	
	//Fifo IN
		int  EtapRH;
		void EixoRH00();		//
		void EixoRH01();		//
		void EixoRH02();		//
		void EixoRH03();		//
		void EixoRHEnd();		//
		void EixoRHError();		//Error	
	//Inicialização do Status
		int  EtapRI;
		void EixoRI00();		//
		void EixoRI01();		//
		void EixoRI02();		//
		void EixoRIEnd();		//
		void EixoRIError();		//Error	
	//Definição de Bit(Flag) de erro na placa
		int  EtapRJ;
		void EixoRJ00();		//
		void EixoRJ01();		//
		void EixoRJ02();		//
		void EixoRJEnd();		//
		void EixoRJError();		//Error	
	//Verifica ErrorBit
		int  EtapRL;
		void EixoRL00();		//
		void EixoRL01();		//
		void EixoRL02();		//
		void EixoRL03();		//
		void EixoRL04();		//
		void EixoRL05();		//
		void EixoRL06();		//
		void EixoRL07();		//
		void EixoRLEnd();		//
		void EixoRLError();		//Error	
		int TimerL;
		void GetErrors();
		void ResetErrors();
	//Verifica Erros na Placa
		int  EtapRM;
		void EixoRM00();		//
		void EixoRM01();		//
		void EixoRM02();		//
		void EixoRMEnd();		//
		void EixoRMError();		//Error	
	//Inicialização da Saida de Erro
		int  EtapRN;
		void EixoRN00();		//
		void EixoRN01();		//
		void EixoRN02();		//
		void EixoRNEnd();		//
		void EixoRNError();		//Error	
		CPPar ParErrorSet;
		CPPar ParErrorReset;
		void ResetError();
		void SetError();
};

//CPAxisRTmr RTimer;

#endif


