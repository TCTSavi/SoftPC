#include "..\Inc\CPComm.h"

CPComm::CPComm(){
	C_VTable = 0;
	C_Page = 0;
	BQFIFOSMutex = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (BQFIFOSMutex == NULL) 
    {
        //ERROR;
	}	
	
	BQFIFORMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (BQFIFORMutex == NULL) 
    {
        //ERROR;
	}

	BVTableSMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (BVTableSMutex == NULL) 
    {
        //ERROR;
	}
	//system("pause");

	BPageSMutex	  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (BPageSMutex	 == NULL) 
    {
        //ERROR;
	}
	//system("pause");
	
	MainMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (MainMutex == NULL) 
    {
        //ERROR;
	}

	
	
	BFSizeMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (BFSizeMutex == NULL) 
    {
        //ERROR;
	}

	ErrorMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (ErrorMutex == NULL) 
    {
        //ERROR;
	}

	Porta = NULL;
	SCount = 0;
	BFSize = 0;
	//Thread = NULL;
	Running	 = false;
	Errors = 0;
	bConnect = false;
	bDisconnect = true;
}

void CPComm::OnInit(){
	Thread = CreateThread( 
		NULL,
		0,
		(LPTHREAD_START_ROUTINE) &Dialog,
		this, 
		0, 
		NULL
	);
	Running	 = true;

	dwRead = new DWORD;
	lpBuf = new unsigned char[64];
	StatusData.Par = NULL;
	
}

void CPComm::OnEnd(){
	Running = false;
	CloseHandle(Thread);	
	delete dwRead;	
	delete lpBuf;
	printf("finalizou comm\n");
}

void CPComm::Dialog(void* Param){
	CPComm* RTtmp = (CPComm*) Param;
	RTtmp->Comm = (CPComm*) Param;
	RTtmp->EtapRA = CommConne;
	while (RTtmp->Running){
		//Etapas da comunicação
		//printf("Etapa:%d\n",RTtmp->EtapRA);
		switch (RTtmp->EtapRA){
			//QFIFO
			case CommRAN00: RTtmp->QFIFOSize(CommRAN17);	break;	//Checa Buffer QFifo
			case CommRAN01: RTtmp->UpdateBS(0);				break;	//Atualiza contador BFSize e SCount
			case CommRAN02: RTtmp->GetQFIFO(0);				break;	//Pega Dado QFIFO
			case CommRAN03: RTtmp->GetPort(0);				break;	//Trava intervenções
			case CommRAN04: RTtmp->Send(0);					break;	//Envia
			case CommRAN05: RTtmp->WaitR(CommRAN13);		break;	//Aguarda retorno
			case CommRAN06: RTtmp->FreePort(0);				break;	//Libera porta 
			case CommRAN07: RTtmp->TreatR(CommRAN14);		break;	//Trata retorno
			case CommRAN08: RTtmp->DecQFIFO(0);				break;	//Decrementa Dado QFIFO
			case CommRAN09: RTtmp->SendC(0);				break;	//Incrementa o envio
			case CommRAN10: RTtmp->Wait(0);					break;	//Sleep
			case CommRAN11: RTtmp->FDisconnect(CommConne);	break;	//Disconnect?		
			case CommRAN12: RTtmp->End(CommRAN00);			break;	//Finalização
			case CommRAN13: RTtmp->FreePort(0);				break;	//Libera porta 
			case CommRAN14: RTtmp->Wait(0);					break;	//Sleep
			case CommRAN15: RTtmp->FDisconnect(CommConne);	break;	//Disconnect?		
			case CommRAN16: RTtmp->End(CommRAN00);			break;	//Finalização
			//VTable
			case CommRAN17: RTtmp->ResetBS(0);				break;	//Reseta contator BFSize e SCount
			case CommRAN18: RTtmp->VTableSize(CommRAN00);	break;	//Checa Buffer VTable
			case CommRAN19: RTtmp->GetVTable(0);			break;	//Pega Dado VTable
			case CommRAN20: RTtmp->GetPort(0);				break;	//Trava intervenções
			case CommRAN21: RTtmp->Send(0);					break;	//Envia
			case CommRAN22: RTtmp->WaitR(CommRAN13);		break;	//Aguarda retorno
			case CommRAN23: RTtmp->FreePort(0);				break;	//Libera porta 
			case CommRAN24: RTtmp->TreatR(CommRAN14);		break;	//Trata retorno
			case CommRAN25: RTtmp->DecVTable(0);			break;	//Decrementa Dado VTable
			case CommRAN26: RTtmp->Wait(0);					break;	//Aguarda 1ms
			case CommRAN27: RTtmp->FDisconnect(CommConne);	break;	//Disconnect?		
			case CommRAN28: RTtmp->End(CommRAN29);			break;	//Finalização
			//PageTable
			case CommRAN29: RTtmp->PageSize(CommRAN00);		break;	//Checa Buffer PageTable
			case CommRAN30: RTtmp->GetPage(0);				break;	//Pega Dado PageTable
			case CommRAN31: RTtmp->GetPort(0);				break;	//Trava intervenções
			case CommRAN32: RTtmp->Send(0);					break;	//Envia
			case CommRAN33: RTtmp->WaitR(CommRAN13);		break;	//Aguarda retorno
			case CommRAN34: RTtmp->FreePort(0);				break;	//Libera porta 
			case CommRAN35: RTtmp->TreatR(CommRAN14);		break;	//Trata retorno
			case CommRAN36: RTtmp->DecPage(0);				break;	//Decrementa Dado VTable
			case CommRAN37: RTtmp->Wait(0);					break;	//Aguarda 1ms
			case CommRAN38: RTtmp->FDisconnect(CommConne);	break;	//Disconnect?		
			case CommRAN39: RTtmp->End(CommRAN00);			break;	//Finalização
			case CommConne:	RTtmp->FConnect(CommRAN00);		break;	//Conect?
			default: RTtmp->Error(0);						break;	//Deu Ruim
		}
	}
}

void CPComm::FConnect(int Desvio){
	WaitForSingleObject( Comm->MainMutex,INFINITE );
	if ( Comm->bConnect && Comm->bDisconnect ){
		Comm->EtapRA = Desvio;
		Comm->bDisconnect =  false;
	}
	ReleaseMutex( Comm->MainMutex );	
	Sleep(10);
}

void CPComm::FDisconnect(int Desvio){
	WaitForSingleObject( Comm->MainMutex,INFINITE );
	if ( !Comm->bConnect && !Comm->bDisconnect){
		Comm->EtapRA = Desvio;
		Comm->bDisconnect =  true;
		WaitForSingleObject(Comm->BFSizeMutex,INFINITE);
		Comm->BFSize = 0;
		Comm->SCount = 0;
		ReleaseMutex(Comm->BFSizeMutex);
		WaitForSingleObject( Comm->BQFIFOSMutex,INFINITE );	
		WaitForSingleObject( Comm->BQFIFORMutex,INFINITE );
		WaitForSingleObject( Comm->BVTableSMutex,INFINITE );
		WaitForSingleObject( Comm->BPageSMutex,INFINITE );
		while (!QFIFO_Out.empty()){QFIFO_Out.pop();}	
		while (!QFIFO_In.empty()){QFIFO_In.pop();}	
		while (!VTable.empty()){VTable.pop_back();}	
		while (!PageTable.empty()){PageTable.pop_back();}	
		ReleaseMutex( Comm->BQFIFOSMutex );	
		ReleaseMutex( Comm->BQFIFORMutex );
		ReleaseMutex( Comm->BVTableSMutex ); 
		ReleaseMutex( Comm->BPageSMutex ); 
	}
	else{
		Comm->EtapRA++;
	}
	ReleaseMutex( Comm->MainMutex );	
}

void CPComm::QFIFOSize(int Desvio){
	WaitForSingleObject( Comm->BQFIFOSMutex,INFINITE );  	// no time-out interval	
	int Size = Comm->QFIFO_Out.size();
	ReleaseMutex(Comm->BQFIFOSMutex);
	if (Size == 0){
		Comm->EtapRA=Desvio;
	}
	else{
		Comm->EtapRA++;
	}
}

void CPComm::UpdateBS(int Desvio){
	WaitForSingleObject( Comm->BQFIFOSMutex,INFINITE );  	// no time-out interval	
	int Size = Comm->QFIFO_Out.size();
	ReleaseMutex(Comm->BQFIFOSMutex);	
	WaitForSingleObject(Comm->BFSizeMutex,INFINITE);
	if ( Comm->BFSize <= (Size + Comm->SCount) ){
		Comm->BFSize = Size + Comm->SCount;
	}
	//printf("Buffer:%d Etapa:%d\n",Comm->BFSize,Comm->EtapRA);
	ReleaseMutex(Comm->BFSizeMutex);	
	Comm->EtapRA++;
}

void CPComm::SendC(int Desvio){
	WaitForSingleObject(Comm->BFSizeMutex,INFINITE);
	Comm->SCount++;
	ReleaseMutex(Comm->BFSizeMutex);	
	Comm->EtapRA++;
}

void CPComm::ResetBS(int Desvio){
	WaitForSingleObject(Comm->BFSizeMutex,INFINITE);
	Comm->BFSize = 0;
	Comm->SCount = 0;
	ReleaseMutex(Comm->BFSizeMutex);	
	Comm->EtapRA++;
}

void CPComm::VTableSize(int Desvio){
	WaitForSingleObject( Comm->BVTableSMutex,INFINITE );  	// no time-out interval	
	int Size = Comm->VTable.size();
	ReleaseMutex(Comm->BVTableSMutex);
	if (Size == 0){
		Comm->EtapRA=Desvio;
	}
	else{
		Comm->EtapRA++;
	}
}

void CPComm::PageSize(int Desvio){
	WaitForSingleObject( Comm->BPageSMutex,INFINITE );  	// no time-out interval	
	int Size = Comm->PageTable.size();
	ReleaseMutex(Comm->BPageSMutex);
	if (Size == 0){
		Comm->EtapRA=Desvio;
	}
	else{
		Comm->EtapRA++;
	}
}

void CPComm::GetQFIFO(int Desvio){
	WaitForSingleObject( Comm->BQFIFOSMutex,INFINITE );  	// no time-out interval	
	Comm->Data = Comm->QFIFO_Out.front();
	ReleaseMutex(Comm->BQFIFOSMutex);
	Comm->EtapRA++;
}

void CPComm::GetVTable(int Desvio){
	WaitForSingleObject( Comm->BVTableSMutex,INFINITE );  	// no time-out interval	
	Comm->Data = Comm->VTable[Comm->C_VTable];
	ReleaseMutex(Comm->BVTableSMutex);
	Comm->EtapRA++;
}

void CPComm::GetPage(int Desvio){
	WaitForSingleObject( Comm->BPageSMutex,INFINITE );  	// no time-out interval	
	Comm->Data = Comm->PageTable[Comm->C_Page];
	ReleaseMutex(Comm->BPageSMutex);
	Comm->EtapRA++;
}

void CPComm::DecQFIFO(int Desvio){
	WaitForSingleObject( Comm->BQFIFOSMutex,INFINITE );  	// no time-out interval	
	Comm->QFIFO_Out.pop();
	ReleaseMutex(Comm->BQFIFOSMutex);
	Comm->EtapRA++;
}

void CPComm::DecVTable(int Desvio){
	WaitForSingleObject( Comm->BVTableSMutex,INFINITE );  	// no time-out interval	
	Comm->C_VTable++;
	if ( Comm->C_VTable >= Comm->VTable.size() ){
		Comm->C_VTable = 0;
	}
	ReleaseMutex(Comm->BVTableSMutex);
	Comm->EtapRA++;
}

void CPComm::DecPage(int Desvio){
	WaitForSingleObject( Comm->BPageSMutex,INFINITE );  	// no time-out interval	
	Comm->C_Page++;
	if ( Comm->C_Page >= Comm->PageTable.size() ){
		Comm->C_Page = 0;
	}
	ReleaseMutex(Comm->BPageSMutex);
	Comm->EtapRA++;
}

void CPComm::GetPort(int Desvio){
	WaitForSingleObject( Comm->Porta->PortaMutex,INFINITE );
	Comm->EtapRA++;
}

void CPComm::Send(int Desvio){
	Comm->Porta->Write(&Comm->Data.Pack[0],Comm->Data.Pack.size());	
	Comm->EtapRA++;	
}

void CPComm::WaitR(int Desvio){
	*Comm->dwRead = 0;
	if ( !(Comm->Porta->Read(Comm->lpBuf,Comm->dwRead)) ){
		//TimeIn Error
		WaitForSingleObject( Comm->ErrorMutex,INFINITE );
		Comm->Errors |= (COMMTIMEIN);
		ReleaseMutex(Comm->ErrorMutex);
		Comm->EtapRA = Desvio;
	}
	else{
		//Limpa TimeIn Error
		WaitForSingleObject( Comm->ErrorMutex,INFINITE );
		Comm->Errors &= (~COMMTIMEIN);
		ReleaseMutex(Comm->ErrorMutex);
		Comm->EtapRA++;
	}
}

void CPComm::FreePort(int Desvio){
	ReleaseMutex(Comm->Porta->PortaMutex);
	Comm->EtapRA++;
}

void CPComm::TreatR(int Desvio){
	if ( (Comm->dwRead != NULL) & (*Comm->dwRead != 0)){
		if (GetUnpack(&Comm->Data,Comm->lpBuf,Comm->dwRead)){
			uint8_t Dir = Comm->Data.MainPack.direcao_e_canal & (DIRECAO_SOLICITACAO|DIRECAO_MASCARA_RESETAR_BITS|DIRECAO_MASCARA_SETAR_BITS|DIRECAO_ENVIO);
			WaitForSingleObject( Comm->ErrorMutex,INFINITE );
			Comm->Errors &= (~COMMPROTOCOL);
			ReleaseMutex(Comm->ErrorMutex);
			if ( Dir == DIRECAO_SOLICITACAO ){
				//Guarda na FIFO IN
				WaitForSingleObject( Comm->BQFIFORMutex,INFINITE );  	// no time-out interval	.
				Comm->QFIFO_In.push(Comm->Data);
				ReleaseMutex(Comm->BQFIFORMutex);
			}
			else{
				//Guarda no Status
				if ( Comm->StatusData.Par != NULL ){
					Comm->StatusData.MainPack = Comm->Data.MainPack;
					WaitForSingleObject( Comm->BQFIFORMutex,INFINITE );  	// no time-out interval	.
					Comm->QFIFO_In.push(Comm->StatusData);
					ReleaseMutex(Comm->BQFIFORMutex);
				}
			}
			Comm->EtapRA++;	
		}
		else{
			//Erro de protocolo
			WaitForSingleObject( Comm->ErrorMutex,INFINITE );
			Comm->Errors |= (COMMPROTOCOL);
			ReleaseMutex(Comm->ErrorMutex);
			Comm->EtapRA = Desvio;	
		}
	}
}

void CPComm::Wait(int Desvio){
	Sleep(0);
	Comm->EtapRA++;
}

void CPComm::Stop(int Desvio){
}

void CPComm::End(int Desvio){
	Comm->EtapRA=Desvio;
}

void CPComm::Error(int Desvio){
	Comm->EtapRA=Desvio;
}

//---------------------------------------------------------------------------------

void CPComm::Connect(){
	WaitForSingleObject( MainMutex,INFINITE );
	bConnect =  true;
	ReleaseMutex( MainMutex );	
}

void CPComm::Disconnect(){
	WaitForSingleObject( Comm->ErrorMutex,INFINITE );
	Comm->Errors &= (~(COMMTIMEIN|COMMPROTOCOL));
	ReleaseMutex( Comm->ErrorMutex );
	WaitForSingleObject( MainMutex,INFINITE );
	bConnect = false ;
	ReleaseMutex( MainMutex );	
}

bool CPComm::IsDisconnect(){
	bool State;
	WaitForSingleObject( MainMutex,INFINITE );
	if ( !bConnect && bDisconnect ){
		State = true;
	}
	else {
		State = false;
	}
	ReleaseMutex( MainMutex );
	return State;
}

void CPComm::PushVTable(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal){
	SSendPack* PackEsc = new SSendPack;
	SMainPack* Pack = new SMainPack;
	GetPack(PackEsc,Pack,End,Dado,Canal);
	PackEsc->Par = Par;
	WaitForSingleObject( BVTableSMutex,INFINITE);
	VTable.push_back(*PackEsc);
	ReleaseMutex(BVTableSMutex); 
	delete Pack;
	delete PackEsc;	
}

void CPComm::PushQFIFO(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal){
	SSendPack* PackEsc = new SSendPack;
	SMainPack* Pack = new SMainPack;
	GetPack(PackEsc,Pack,End,Dado,Canal);
	PackEsc->Par = Par;
	WaitForSingleObject( BQFIFOSMutex,INFINITE);
	QFIFO_Out.push(*PackEsc);
	ReleaseMutex(BQFIFOSMutex) ;
	delete Pack;
	delete PackEsc;
}

void CPComm::PushPageTable(CPPar* Par,uint8_t* End,uint16_t* Dado,int* Canal){
	SSendPack* PackEsc = new SSendPack;
	SMainPack* Pack = new SMainPack;
	GetPack(PackEsc,Pack,End,Dado,Canal);
	PackEsc->Par = Par;
	WaitForSingleObject( BPageSMutex,INFINITE);
	PageTable.push_back(*PackEsc);
	ReleaseMutex(BPageSMutex); 
	delete Pack;
	delete PackEsc;	
}


void CPComm::GetPack(SSendPack* PackEsc,SMainPack* Pack,uint8_t* End,uint16_t* Dado,int* Canal){
	Pack->resetAll();
	Pack->start_byte = STX;
	Pack->direcao_e_canal = (uint8_t)*Canal;
	Pack->cmd = *End;
	Pack->dado = *Dado;
	Pack->end_byte = (uint8_t)ETX;
	CheckEsc(PackEsc,Pack);
}

uint8_t CPComm::CheckSum(SMainPack* Pack){
	uint8_t CheckSum = 0;
	for (int i=0;i<(SEG_MAX_LENGTH);i++){
		CheckSum = CheckSum+Pack->dataSegment[i];
	}
	CheckSum = 0x100-CheckSum;
	return CheckSum;
}

void CPComm::CheckEsc(SSendPack* PackEsc,SMainPack* Pack){
	int ASCDuplo = 0;
	PackEsc->Pack.push_back(ESC);
	for (int i=0;i<SEG_MAX_LENGTH;i++){
		if ( i == (SEG_MAX_LENGTH-1)){
			PackEsc->Pack.push_back(ESC);
		}
		if( Pack->dataSegment[i] == ESC){
			PackEsc->Pack.push_back(Pack->dataSegment[i]);
			PackEsc->Pack.push_back(Pack->dataSegment[i]);
		}
		else{
			PackEsc->Pack.push_back(Pack->dataSegment[i]);
		}
	}
	uint8_t ChSum = CheckSum(Pack);
	if( ChSum  == ESC){
		PackEsc->Pack.push_back(ChSum);
		PackEsc->Pack.push_back(ChSum);
	}else{
	PackEsc->Pack.push_back(ChSum);
	}
}

bool CPComm::GetUnpack(SSendPack* Data,unsigned char * lpBuf, DWORD* dwRead){
	int etapa =0;
	int i=0;
	int j=0;
	while (etapa <=3){
		switch (etapa){
			case 0:{//ESC STX
				if ((lpBuf[i] == ESC) && (lpBuf[i+1] == ACK) ){
					Data->MainPack.dataSegment[j] = 	lpBuf[i+1];
					i+=2;
					j++;
					etapa++;
				}
				else{
					//Erro de protocolo
					//Erro de protocolo
					//printf("Erro de protocolo etapa 0\n");
					return false;
				}
			}
			break;
			case 1:{//DirCanal Cmd Dado
				while(j < SEG_MAX_LENGTH-1 ){
					if (lpBuf[i] == ESC){
						if (lpBuf[i+1] == ESC){
							Data->MainPack.dataSegment[j] = (uint8_t)lpBuf[i];
							i+=2;
							j++;
						}
						else{
							//Erro de protocolo
							//printf("Erro de protocolo etapa 1\n");
							return false;
						}
					}
					else{
						Data->MainPack.dataSegment[j] = (uint8_t)lpBuf[i];
						i++;
						j++;
					}
				}
				etapa++;
			}
			break;
			case 2:{//ESC ETX
				if ((lpBuf[i] == ESC) && (lpBuf[i+1] == ETX) ){
					Data->MainPack.dataSegment[j] = lpBuf[i+1];
					i+=2;
					j++;
					etapa++;
				}
				else{
					//Erro de protocolo
					//printf("Erro de protocolo etapa 2\n");
					return false;
				}
			}
			break;
			case 3:{//CheckSum
				//printf("CheckSum Transmitido: %x\n",lpBuf[i]);
				if ((lpBuf[i] == ESC) && (lpBuf[i+1] != ESC) ){
					//Erro de protocolo
					//printf("Erro de protocolo etapa 3 I\n");
					return false;
				}
				uint8_t ChSum = CheckSum(&Data->MainPack);
				//printf("CheckSum Calculado: %x\n",ChSum);
				if (ChSum != lpBuf[i]){
					//Erro de CheckSum
					//printf("Erro de protocolo etapa 3 f\n");
					return false;
				}
				etapa++;
			}
			break;
			default:{
				etapa++;
			}
			break;
		}
	}
	return true;
}


bool CPComm::PopQFIFO(CPPar*& Par,uint16_t* Dado){
	SSendPack Data;	
	bool state = false;
	WaitForSingleObject(BQFIFORMutex,INFINITE );  	// no time-out interval	
	int Size = QFIFO_In.size();
	if ( Size == 0 ){
		state = false;
	}
	else{
		Data = QFIFO_In.front();
		//Data.Par->setValor("OIA");
		Par = Data.Par;
		*Dado = Data.MainPack.dado;
		QFIFO_In.pop();
		state = true;
	}
	ReleaseMutex(BQFIFORMutex);
	return state;
}

void CPComm::GetQFIFOStatus(int* Buffer,int* Send){
	WaitForSingleObject(BFSizeMutex,INFINITE);
	*Buffer = BFSize;	
	*Send = SCount;
	ReleaseMutex(BFSizeMutex);
	return; 
}

bool CPComm::GetErrors(int Flags){
	int ErrorsOld;
	WaitForSingleObject(ErrorMutex,INFINITE);
	ErrorsOld= Errors;
	ReleaseMutex(ErrorMutex);	
	ErrorsOld &= Flags;
	return ErrorsOld;
}

void CPComm::ClearPage(){
	WaitForSingleObject( Comm->BPageSMutex,INFINITE );  	// no time-out interval	
	while (!PageTable.empty()){PageTable.pop_back();}		
	ReleaseMutex(Comm->BPageSMutex);
}
	
