#include "..\Inc\CPAxisRTmr.h"

CPAxisRTmr::CPAxisRTmr(){
}

void CPAxisRTmr::OnInit(){
	Updating = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
	);
	Runnig = true;
	FTimer = 1.0;
	RT3MainR = 0;
	
//Inicia
	Thread = CreateThread( 
		NULL,
		0,
		(LPTHREAD_START_ROUTINE) &RTimer,
		this, 
		0, 
		NULL
	);
}

void CPAxisRTmr::OnEnd(){
	Runnig = false;
	Sleep(1);
	SuspendThread(Thread);
}

void CPAxisRTmr::RTimer(void* Param){
	CPAxisRTmr* RTtmp;
	RTtmp = (CPAxisRTmr*) Param;
	RTtmp->Rtimer = (CPAxisRTmr*)Param;
	DWORD WaitMutex;
	RTtmp->Rtimer->RtimerUse = 0;
	double dftDuration = 0;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER liNow;
	LARGE_INTEGER liOld;	
	LARGE_INTEGER liRt;	
	
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&liOld);
	while (RTtmp->Rtimer->Runnig){
		QueryPerformanceCounter(&liNow);
		LONGLONG llTimeDiff = liNow.QuadPart - liOld.QuadPart;
		dftDuration = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
//		printf("Tempo decorrido:%f,ref:%f\n",dftDuration,RTtmp->Rtimer->FTimer);
		if (dftDuration < RTtmp->Rtimer->FTimer){
			//printf("Tempo decorrido:%f\n",dftDuration);
			//Sleep(1);
		}
		else{
			QueryPerformanceCounter(&liOld);
			//Fluxo do programa principal
			switch (RTtmp->Rtimer->RT3MainR){
				case MainRAN0	: RTtmp->Rtimer->MainRA00(); 	break;	//
				case MainRAN1	: RTtmp->Rtimer->MainRA01(); 	break;	//
				case MainRAN2	: RTtmp->Rtimer->MainRA02(); 	break;	//
				case MainRAN3	: RTtmp->Rtimer->MainRA03(); 	break;	//
				case MainRAN4	: RTtmp->Rtimer->MainRA04(); 	break;	//
				case MainRAN5	: RTtmp->Rtimer->MainRA05(); 	break;	//
				case MainRAN6	: RTtmp->Rtimer->MainRA06(); 	break;	//
				case MainRAN7	: RTtmp->Rtimer->MainRA07(); 	break;	//
				case MainRANEnd: RTtmp->Rtimer->MainRAEnd(); 	break;	//

				default: RTtmp->Rtimer->MainRAError();			break;	//Deu Ruim
			}
			//
			QueryPerformanceCounter(&liRt);
			llTimeDiff = liRt.QuadPart - liOld.QuadPart;
			RTtmp->Rtimer->RtimerUse = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
			ReleaseMutex(RTtmp->Rtimer->Updating);		
		}
    }	
}

////Fluxo do programa principal
void CPAxisRTmr::MainRA00(){
	//printf("OPA:%d");
}	

void CPAxisRTmr::MainRA01(){
}

void CPAxisRTmr::MainRA02(){
}

void CPAxisRTmr::MainRA03(){
}

void CPAxisRTmr::MainRA04(){
}

void CPAxisRTmr::MainRA05(){
}

void CPAxisRTmr::MainRA06(){
}

void CPAxisRTmr::MainRA07(){
}

void CPAxisRTmr::MainRAEnd(){
}

void CPAxisRTmr::MainRAError(){
}

	