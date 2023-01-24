#ifndef _CPAXISRTIMER_H_
#define _CPAXISRTIMER_H_

#include <windows.h>
#include <Vector>
#include <queue> 
#include <string>
#include <stdint.h>

#include "CPMenu.h"
#include "CPPar.h"
#include "CLog.h"
#include "CPMOpc.h"
#include "CPMPar.h"
#include "CPComm.h"
#include "CPMascErro.h"

enum {
   //States of routine (Rotina do fluxo principal A)
   MainRAN0 = 0,
   MainRAN1,
   MainRAN2,
   MainRAN3,
   MainRAN4,
   MainRAN5,
   MainRAN6,
   MainRAN7,
   MainRANEnd,
};  

class CPRTimer {
	public:
		HANDLE Thread;
		HANDLE Updating;
		
	public:
		CPRTimer();
		CPRTimer *Rtimer;
		HWND hwnd;
		double FTimer;
		double RtimerUse;
		bool Runnig;
		void RTimer(void* Param);
		void Conect();
		void OnInit();
		void OnEnd();
		void EtapaError();      //
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
