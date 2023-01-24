#ifndef _CPComm_H_
#define _CPComm_H_

#include <windows.h>
#include <Vector>
#include <queue> 
#include "CLog.h"
#include <string>
#include <stdint.h>
#include "CPPorta.h"

#include "CPPar.h"

enum {
   //States of protocol posijet1 
   INITIAL_ESC = 0,
   START_BYTE,
   DIRECTION_AND_CHANNEL,
   COMMAND,
   DATA_LOW,
   DATA_HIGH,
   FINAL_ESC,
   ETX_BYTE,
   CHECKSUM,
   SUCESSFUL,
};  

enum {
   //States of protocol posijet1 
   COMMFIFO = 0,
   COMMTABLE,
   COMMPAGE,
};

enum {
   //Errors
   COMMTIMEIN = 0x0001,
   COMMPROTOCOL = 0x0002,
};

//Etapas da comunicação
enum {
	CommRAN00 = 0,
	CommRAN01,
	CommRAN02,
	CommRAN03,
	CommRAN04,
	CommRAN05,
	CommRAN06,
	CommRAN07,	
	CommRAN08,	
	CommRAN09,
	CommRAN10,
	CommRAN11,
	CommRAN12,
	CommRAN13,
	CommRAN14,
	CommRAN15,
	CommRAN16,
	CommRAN17,
	CommRAN18,
	CommRAN19,
	CommRAN20,
	CommRAN21,
	CommRAN22,
	CommRAN23,
	CommRAN24,
	CommRAN25,
	CommRAN26,
	CommRAN27,
	CommRAN28,
	CommRAN29,
	CommRAN30,
	CommRAN31,
	CommRAN32,
	CommRAN33,
	CommRAN34,
	CommRAN35,
	CommRAN36,
	CommRAN37,
	CommRAN38,
	CommRAN39,
	CommConne,	
	CommRANEnd,
};

#define ESC 0x1B
#define STX 0x02
#define ACK 0x06
#define ETX 0x03
#define NACK 0x15 

#define DIRECAO_SOLICITACAO 0x0
#define DIRECAO_MASCARA_RESETAR_BITS 0x40
#define DIRECAO_MASCARA_SETAR_BITS 0x80
#define DIRECAO_ENVIO 0xC0

#pragma pack(push, 1)

struct SMainPack{    
    //Main data structure of a packet of Posijet1 protocol
    //Unions allow many ways to access some data information
    // dataSegment = ESC + START_BYTE + [ (direcao/canal) + cmd + dadoHigh + dadoLow ] + FINAL_ESC + ETX_BYTE + CHECKSUM
	union {
		#define SEG_MAX_LENGTH 6    //Segment Max Length
		uint8_t dataSegment[SEG_MAX_LENGTH];
		struct {
			uint8_t start_byte;
			uint8_t direcao_e_canal;
			uint8_t cmd;
			uint16_t dado;
			uint8_t end_byte;
		};        
    };  
    void resetAll() { for(uint8_t k=0; k<=SEG_MAX_LENGTH; k++) dataSegment[k] = 0; };
};
#pragma pack(pop)

struct SSendPack{
	CPPar *Par;					//Parametro comunicado
	std::vector<uint8_t> Pack;	//Pacote formatado com ASC ,ASC duplo ,CheckSum
	SMainPack MainPack;			//Pacote base
};

class CPComm {
	public:
		std::queue<SSendPack> QFIFO_Out;
		std::queue<SSendPack> QFIFO_In;
		std::vector<SSendPack> VTable;
		std::vector<SSendPack> PageTable;
		void GetPack(SSendPack* PackEsc,SMainPack* Pack,uint8_t* End,uint16_t* Dado,int* Canal);
		bool GetUnpack(SSendPack* Data,unsigned char * lpBuf, DWORD* dwRead);
		void PushVTable(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal);
		void PushPageTable(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal);
		void PushQFIFO(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal);
		bool PopQFIFO(CPPar*& Par,uint16_t* Dado);
		void ClearPage();
		uint8_t CheckSum(SMainPack* Pack);
		void CheckEsc(SSendPack* PackEsc,SMainPack* Pack);
		bool Running;
		int C_VTable;
		int C_Page;
		HANDLE Thread;
		HANDLE BVTableSMutex;
		HANDLE BPageSMutex;
		HANDLE BQFIFOSMutex;
		HANDLE BQFIFORMutex;
		HANDLE BFSizeMutex;
		HANDLE MainMutex;
		HANDLE ErrorMutex;
		CPPorta* Porta;
		int Errors;
		bool GetErrors(int Flags);
		void GetQFIFOStatus(int* Buffer,int* Send);
		int SCount;
		int BFSize;
		int Etapas;
		bool bConnect;
		bool bDisconnect;
	public:
		CPComm* Comm;		
		SSendPack Data;
		SSendPack StatusData;
		DWORD* dwRead;
		unsigned char* lpBuf;
	public:
		int  EtapRA;
		void FConnect(int Desvio);		//Verifica se é p/ connectar
		void FDisconnect (int Desvio);	//Verifica se é p/ desconnectar
		void QFIFOSize(int Desvio);		//Checa Buffer QFifo
		void UpdateBS(int Desvio);  	//Atualiza contador BFSize e SCount
		void SendC(int Desvio);			//Incrementa o envio
		void ResetBS(int Desvio);   	//Reseta contator BFSize e SCount
		void VTableSize(int Desvio);	//Checa Buffer VTable
		void PageSize(int Desvio);		//Checa Buffer PageTable
		void GetQFIFO(int Desvio);		//Pega Dado QFFIFO
		void GetVTable(int Desvio);		//Pega Dado VTable
		void GetPage(int Desvio);		//Pega Dado PageTable
		void DecQFIFO(int Desvio);		//Decrementa Dado QFIFO
		void DecVTable(int Desvio);		//Decrementa Dado VTable
		void DecPage(int Desvio);		//Decrementa Dado PageTable
		void GetPort(int Desvio);		//Solicita porta
		void Send(int Desvio);			//Envia
		void WaitR(int Desvio);			//Aguarda retorno
		void FreePort(int Desvio);		//Libera porta 
		void TreatR(int Desvio);		//Trata retorno
		void Wait(int Desvio);			//Sleep
		void Stop(int Desvio);			//Stop
		void End(int Desvio);       	//Finalização
		void Error(int Desvio);     	//Deu Ruim
	public:
		CPComm();
		void OnInit();
		void OnEnd();
		void Dialog(void* Param);
		void Connect();
		void Disconnect();
		bool IsDisconnect();
};	

#endif
