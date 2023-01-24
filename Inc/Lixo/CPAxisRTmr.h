#ifndef _CPAXISRTMR_H_
#define _CPAXISRTMR_H_

#include <windows.h>
#include <Vector>
#include <queue> 
#include <string>
#include <stdint.h>

#include "CPEixo.h"
#include "CPEPage.h"
#include "CPMenu.h"
#include "CPPar.h"
#include "CLog.h"
#include "CPMOpc.h"
#include "CPMPar.h"
#include "CPComm.h"
#include "CPMascErro.h"


class CPAxisRTmr {
	public:
		HANDLE Thread;
		HANDLE Updating;
		
	public:
		CPAxisRTmr();
		CPAxisRTmr *Rtimer;
		HWND hwnd;
		double FTimer;
		double RtimerUse;
		bool Runnig;
		void RTimer(void* Param);
		void OnInit(CPEixo* _Eixo);
		void OnEnd();
		void EtapaError();      //
		CPEixo* Eixo;
	//Fluxo principal 
	public:
		int RT3MainR;
		void MainRA00();		//
		void MainRA01();		//
		void MainRA02();		//
		void MainRA03();		//
		void MainRA04();		//
		void MainRA05();		//
		void MainRA06();		//
		void MainRA07();		//
		void MainRAEnd();		//
		void MainRAError();		//Error
		
};	

#endif
