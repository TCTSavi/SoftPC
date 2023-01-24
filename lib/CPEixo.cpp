#include "..\Inc\CPEixo.h"

CPEixo::CPEixo() {
	Canal = 0;
	//Porta = NULL;
}

CPEixo::~CPEixo() {
}

CRPar::CRPar(){
}

void CPEixo::InitAxis(){
	Running = true;
	Comm.OnInit();
	FTimer = 20.0;
	EtapRA = 0;
	EtapRB = 0;
	EtapRC = 0;
	EtapRD = 0;	
	EtapRE = 0;
	EtapRF = 0;
	EtapRG = 0;
	EtapRH = 0;	
	EtapRI = 0;
	EtapRJ = 0;
	EtapRL = 0;
	EtapRM = 0;
	TimerF = 0;
	TimerE = 0;
	TimerS = 0;
	TimerL = 0;
	
//Inicia
	Thread = CreateThread( 
		NULL,
		0,
		(LPTHREAD_START_ROUTINE) &RTimer,
		this, 
		0, 
		NULL
	);
//Cria lista de parametros relacionados	
	MakeRPar();
	MErros.Init();
	GetErrorPar();

//Inicializa saida de erro com endereço 00;	
	ParErrorSet.End  = 0;
	ParErrorReset.End= 0;
}

void CPEixo::GetErrorPar(){
	for (int a =0;a<PageList.size();a++){
		for (int b=0;b<PageList[a].PMenuList.size();b++){
			for (int c=0;c<PageList[a].PMenuList[b].ParList.size();c++){
				if ( strcmp(PageList[a].PMenuList[b].ParList[c].Opcoes,"ERRORTF")==0){
					MErros.SetError(&PageList[a].PMenuList[b].ParList[c]);
					ErrorBitList.push_back(&PageList[a].PMenuList[b].ParList[c]);
				}
			}
		}
	}
}

void CPEixo::EndAxis(){
	//Running = false;
	//Comm.Disconnect();
	//Comm.OnEnd();
}

void CPEixo::RTimer(void* Param){
	CPEixo* RTtmp;
	RTtmp = (CPEixo*) Param;
	RTtmp->Eixo = (CPEixo*)Param;
	RTtmp->Eixo->RtimerUse = 0;
	double dftDuration = 0;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER liNow;
	LARGE_INTEGER liOld;	
	LARGE_INTEGER liRt;	
	
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&liOld);
	while (RTtmp->Eixo->Running){
		QueryPerformanceCounter(&liNow);
		LONGLONG llTimeDiff = liNow.QuadPart - liOld.QuadPart;
		dftDuration = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
//		printf("Tempo decorrido:%f,ref:%f\n",dftDuration,RTtmp->Eixo->FTimer);
		if (dftDuration < RTtmp->Eixo->FTimer){
			//printf("Tempo decorrido:%f\n",dftDuration);
			Sleep(5);
		}
		else{
			WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );			
			//printf("AquiA0\n");	
			QueryPerformanceCounter(&liOld);
			//Inicialização da porta serial
			switch (RTtmp->Eixo->EtapRA){
				case EixoRAN0	: RTtmp->Eixo->EixoRA00(); 	break;	//
				case EixoRAN1	: RTtmp->Eixo->EixoRA01(); 	break;	//
				case EixoRAN2	: RTtmp->Eixo->EixoRA02(); 	break;	//
				case EixoRAN3	: RTtmp->Eixo->EixoRA03(); 	break;	//
				case EixoRAN4	: RTtmp->Eixo->EixoRA04(); 	break;	//
				case EixoRAN5	: RTtmp->Eixo->EixoRA05(); 	break;	//
				case EixoRANEnd: RTtmp->Eixo->EixoRAEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRAError();		break;	//Deu Ruim
			}
			//Definição do Canal
			switch (RTtmp->Eixo->EtapRB){
				case EixoRBN0	: RTtmp->Eixo->EixoRB00(); 	break;	//
				case EixoRBN1	: RTtmp->Eixo->EixoRB01(); 	break;	//
				case EixoRBN2	: RTtmp->Eixo->EixoRB02(); 	break;	//
				case EixoRBNEnd: RTtmp->Eixo->EixoRBEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRBError();		break;	//Deu Ruim
			}
			//Definição do fator
			switch (RTtmp->Eixo->EtapRC){
				case EixoRCN0	: RTtmp->Eixo->EixoRC00(); 	break;	//
				case EixoRCN1	: RTtmp->Eixo->EixoRC01(); 	break;	//
				case EixoRCN2	: RTtmp->Eixo->EixoRC02(); 	break;	//
				case EixoRCNEnd: RTtmp->Eixo->EixoRCEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRCError();		break;	//Deu Ruim
			}
			//Definição do Pulso/mm
			switch (RTtmp->Eixo->EtapRD){
				case EixoRDN0	: RTtmp->Eixo->EixoRD00(); 	break;	//
				case EixoRDN1	: RTtmp->Eixo->EixoRD01(); 	break;	//
				case EixoRDN2	: RTtmp->Eixo->EixoRD02(); 	break;	//
				case EixoRDNEnd: RTtmp->Eixo->EixoRDEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRDError();		break;	//Deu Ruim
			}
			//Inicializa comunicação
			RTtmp->Eixo->EixoREEnd();
			switch (RTtmp->Eixo->EtapRE){
				case EixoREN0	: RTtmp->Eixo->EixoRE00(); 	break;	//
				case EixoREN1	: RTtmp->Eixo->EixoRE01(); 	break;	//
				case EixoREN2	: RTtmp->Eixo->EixoRE02(); 	break;	//
				case EixoREN3	: RTtmp->Eixo->EixoRE03(); 	break;	//
				case EixoREN4	: RTtmp->Eixo->EixoRE04(); 	break;	//
				case EixoREN5	: RTtmp->Eixo->EixoRE05(); 	break;	//
				case EixoREN6	: RTtmp->Eixo->EixoRE06(); 	break;	//
				case EixoRENEnd: RTtmp->Eixo->EixoREEnd(); 	break;	//
				default: RTtmp->Eixo->EixoREError();		break;	//Deu Ruim
			}
			//Status comunicação
			RTtmp->Eixo->EixoRFEnd();
			switch (RTtmp->Eixo->EtapRF){
				case EixoRFN0	: RTtmp->Eixo->EixoRF00(); 	break;	//
				case EixoRFN1	: RTtmp->Eixo->EixoRF01(); 	break;	//
				case EixoRFN2	: RTtmp->Eixo->EixoRF02(); 	break;	//
				case EixoRFNEnd: RTtmp->Eixo->EixoRFEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRFError();		break;	//Deu Ruim
			}
			//Tratamento de comandos e envios
			RTtmp->Eixo->EixoRGEnd();
			switch (RTtmp->Eixo->EtapRG){
				case EixoRGN0	: RTtmp->Eixo->EixoRG00(); 	break;	//
				case EixoRGN1	: RTtmp->Eixo->EixoRG01(); 	break;	//
				case EixoRGN2	: RTtmp->Eixo->EixoRG02(); 	break;	//
				case EixoRGN3	: RTtmp->Eixo->EixoRG03(); 	break;	//
				case EixoRGNEnd: RTtmp->Eixo->EixoRGEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRGError();		break;	//Deu Ruim
			}
			//Fifo IN
			RTtmp->Eixo->EixoRHEnd();
			switch (RTtmp->Eixo->EtapRH){
				case EixoRHN0	: RTtmp->Eixo->EixoRH00(); 	break;	//
				case EixoRHN1	: RTtmp->Eixo->EixoRH01(); 	break;	//
				case EixoRHN2	: RTtmp->Eixo->EixoRH02(); 	break;	//
				case EixoRHN3	: RTtmp->Eixo->EixoRH03(); 	break;	//
				case EixoRHNEnd: RTtmp->Eixo->EixoRHEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRHError();		break;	//Deu Ruim
			}
			//Definição do Status
			RTtmp->Eixo->EixoRIEnd();
			switch (RTtmp->Eixo->EtapRI){
				case EixoRIN0	: RTtmp->Eixo->EixoRI00(); 	break;	//
				case EixoRIN1	: RTtmp->Eixo->EixoRI01(); 	break;	//
				case EixoRIN2	: RTtmp->Eixo->EixoRI02(); 	break;	//
				case EixoRINEnd: RTtmp->Eixo->EixoRIEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRIError();		break;	//Deu Ruim
			}
			//
			//Definição do Flag de Erro na placa
			switch (RTtmp->Eixo->EtapRJ){
				case EixoRJN0	: RTtmp->Eixo->EixoRJ00(); 	break;	//
				case EixoRJN1	: RTtmp->Eixo->EixoRJ01(); 	break;	//
				case EixoRJN2	: RTtmp->Eixo->EixoRJ02(); 	break;	//
				case EixoRJNEnd: RTtmp->Eixo->EixoRJEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRJError();		break;	//Deu Ruim
			}
			//Verifica ErrorBit
			switch (RTtmp->Eixo->EtapRL){
				case EixoRLN0	: RTtmp->Eixo->EixoRL00(); 	break;	//
				case EixoRLN1	: RTtmp->Eixo->EixoRL01(); 	break;	//
				case EixoRLN2	: RTtmp->Eixo->EixoRL02(); 	break;	//
				case EixoRLN3	: RTtmp->Eixo->EixoRL03(); 	break;	//
				case EixoRLN4	: RTtmp->Eixo->EixoRL04(); 	break;	//
				case EixoRLN5	: RTtmp->Eixo->EixoRL05(); 	break;	//
				case EixoRLN6	: RTtmp->Eixo->EixoRL06(); 	break;	//
				case EixoRLN7	: RTtmp->Eixo->EixoRL07(); 	break;	//
				case EixoRLNEnd: RTtmp->Eixo->EixoRLEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRLError();		break;	//Deu Ruim
			}
			//Verifica Erros na placa
			RTtmp->Eixo->EixoRMEnd();
			switch (RTtmp->Eixo->EtapRM){
				case EixoRMN0	: RTtmp->Eixo->EixoRM00(); 	break;	//
				case EixoRMN1	: RTtmp->Eixo->EixoRM01(); 	break;	//
				case EixoRMN2	: RTtmp->Eixo->EixoRM02(); 	break;	//
				case EixoRMNEnd: RTtmp->Eixo->EixoRMEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRMError();		break;	//Deu Ruim
			}
			//
			//Definição de ErrorOut
			RTtmp->Eixo->EixoRNEnd();
			switch (RTtmp->Eixo->EtapRN){
				case EixoRNN0	: RTtmp->Eixo->EixoRN00(); 	break;	//
				case EixoRNN1	: RTtmp->Eixo->EixoRN01(); 	break;	//
				case EixoRNN2	: RTtmp->Eixo->EixoRN02(); 	break;	//
				case EixoRNNEnd: RTtmp->Eixo->EixoRNEnd(); 	break;	//
				default: RTtmp->Eixo->EixoRNError();		break;	//Deu Ruim
			}
			QueryPerformanceCounter(&liRt);
			llTimeDiff = liRt.QuadPart - liOld.QuadPart;
			RTtmp->Eixo->RtimerUse = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
			ReleaseMutex(DMan::DM.ThreadTime);		
			//printf("AquiA1\n");	
		}
    }	
}

//Temporizador
bool CPEixo::TimerElapseEtap(int& Timer){
	Timer--;
	if ( Timer <= 0 ){
		return true;
	}
	else{
		return false;
	}
}

//Conversor de valor para string
void CPEixo::ConvReceiveD(char* buffer,const char * format, ...){
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);	
}	

//Conversor de string para valor
void CPEixo::ConvVtoD ( const char * str, const char * format, ... ){
	va_list args;
	va_start (args, format);
	vsscanf (str, format, args);
	va_end (args);
}

//Inicialização da porta serial e comunicação
void CPEixo::EixoRA00(){
	Eixo->PortName = Eixo->GetValor("GetComOp");
	if (Eixo->PortName == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_FINDPORTA,"Eixo %d",Eixo->Number);
		Eixo->EtapRA++;
	}
	else{
		if ( (strcmp(Eixo->PortName,"COM:NC") == 0)){
			Eixo->MErros.SetErrorStatus(CLOGERROR_PORTANC,"Eixo %d",Eixo->Number);
			Eixo->Comm.Porta == NULL;
			Eixo->EtapRA++;
		}
		else{
			//Nome da porta encontrado
			Eixo->EtapRA+=2;
		}
	}
}	

void CPEixo::EixoRA01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_FINDPORTA) || Eixo->MErros.GetErrorStatus(CLOGERROR_PORTANC) ){
		//printf("Erro Eixo %d\n",Eixo->Number);
	}
	else{
		Eixo->EtapRA = EixoRAN0;
	}
}

void CPEixo::EixoRA02(){
	Eixo->Comm.Porta = DMan::DM.GetPort(Eixo->PortName);
	if (Eixo->Comm.Porta == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_INITPORTA,"Eixo %d",Eixo->Number);
		Eixo->EtapRA++;
	}
	else{
		printf("Inicializado %s Eixo:%d\n",Eixo->Comm.Porta->PortName,Eixo->Number);	
		Eixo->EtapRA=EixoRANEnd;
	}
}

void CPEixo::EixoRA03(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_INITPORTA) ){
	}
	else{
		Eixo->EtapRA = EixoRAN0;
	}	
}

void CPEixo::EixoRA04(){	
	if (Eixo->Comm.Porta == NULL){
		Eixo->EtapRA = EixoRAN0;
	}
	else{
		Eixo->Comm.Disconnect();	
		Eixo->EtapRA++;		
	}
}

void CPEixo::EixoRA05(){	
	if ( Eixo->Comm.IsDisconnect() ) {
		DMan::DM.FreePort( Eixo->Comm.Porta );
		Eixo->PortName = NULL;
		Eixo->Comm.Porta = NULL;
		Eixo->EtapRA = EixoRAN0;
	}
	else{
	}
}


void CPEixo::EixoRAEnd(){
}

void CPEixo::EixoRAError(){
}

//Definição do Canal
void CPEixo::EixoRB00(){
	char* Canal;
	Canal = Eixo->GetValor("DefCanal");
	if (Canal == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFCANAL,"Eixo %d",Eixo->Number);
		Eixo->EtapRB++;
	}
	else{
		Eixo->Canal = atoi(Canal);
		printf("Canal:%d\n",Eixo->Canal);
		Eixo->EtapRB=EixoRBNEnd;;
	}
}

void CPEixo::EixoRB01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFCANAL) ){
	}
	else{
		Eixo->EtapRB = EixoRBN0;
	}	
}

void CPEixo::EixoRB02(){
	Eixo->EtapRB = EixoRBN0;
}

void CPEixo::EixoRBEnd(){
}

void CPEixo::EixoRBError(){
}

//Definição do fator
void CPEixo::EixoRC00(){
	char* Fator;
	Fator = Eixo->GetValor("MENFAT");
	if (Fator == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFFATOR,"Eixo %d",Eixo->Number);
		Eixo->EtapRC++;
	}
	else{
		Eixo->FatorPulso_mm = atof(Fator);
		printf("Fator:%f\n",Eixo->FatorPulso_mm);
		Eixo->EtapRC=EixoRCNEnd;;
	}
}

void CPEixo::EixoRC01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFFATOR) ){
	}
	else{
		Eixo->EtapRC = EixoRCN0;
	}	
}

void CPEixo::EixoRC02(){
	Eixo->EtapRC = EixoRCN0;
}

void CPEixo::EixoRCEnd(){
}

void CPEixo::EixoRCError(){
}

//Definição do Pulso/Volta
void CPEixo::EixoRD00(){
	char* PGiro;
	PGiro = Eixo->GetValor("PGiro");
	if (PGiro == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFPGIRO,"Eixo %d",Eixo->Number);
		Eixo->EtapRD++;
	}
	else{
		Eixo->PulsoVolta = atoi(PGiro);
		printf("PulsoVolta:%d\n",Eixo->PulsoVolta);
		Eixo->EtapRD=EixoRDNEnd;;
	}
}

void CPEixo::EixoRD01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFPGIRO) ){
	}
	else{
		Eixo->EtapRD = EixoRDN0;
	}	
}

void CPEixo::EixoRD02(){
	Eixo->EtapRD = EixoRDN0;
}

void CPEixo::EixoRDEnd(){
}

void CPEixo::EixoRDError(){
}

//Inicializa comunicação
void CPEixo::EixoRE00(){
	if ( 	Eixo->EtapRA==EixoRANEnd && 
			Eixo->EtapRB==EixoRBNEnd &&  
			Eixo->EtapRC==EixoRCNEnd && 
			Eixo->EtapRD==EixoRDNEnd 
			){
		Eixo->EtapRE++;
	}
	else{
		Eixo->EtapRE = EixoREN0;
	}
}

void CPEixo::EixoRE01(){
	if ( Eixo->Comm.IsDisconnect() ) {
		Eixo->EtapRE++;
	}
	else{
	}
}

void CPEixo::EixoRE02(){
	//printf("Envia tudo %d\n",Eixo->Number);
	Eixo->CommTSAll();
	Eixo->EtapRE++;
}

void CPEixo::EixoRE03(){
	Eixo->Comm.Connect();
	Eixo->EtapRE++;
//	printf("Eixo %d conectado\n",Eixo->Number);
}

void CPEixo::EixoRE04(){
	//Inicializa Timer
	Eixo->TimerE = 10;
	Eixo->EtapRE++;
}

void CPEixo::EixoRE05(){
	//Temporiza
	if ( Eixo->TimerElapseEtap( Eixo->TimerE )) {
		Eixo->EtapRE++;
		//Atualiza Buffer
		Eixo->Comm.GetQFIFOStatus(&Eixo->Buffer,&Eixo->Send);
	}
}

void CPEixo::EixoRE06(){
	if ( Eixo->Buffer <= 0){
		Eixo->EtapRE = EixoRENEnd; 
	}
	if ( Eixo->Send > 0 ){
		Eixo->MErros.ResetErrorStatus(CLOGERROR_TIMEIN);
	}
}

void CPEixo::EixoREEnd(){
	if (	
			Eixo->EtapRA==EixoRANEnd && 
			Eixo->EtapRB==EixoRBNEnd &&  
			Eixo->EtapRC==EixoRCNEnd && 
			Eixo->EtapRD==EixoRDNEnd 
			){
	}
	else{
		Eixo->EtapRE = EixoREN0;
		Eixo->Comm.Disconnect();
	}
	if ( Eixo->Comm.GetErrors( COMMTIMEIN ) ){
		if ( Eixo->MErros.GetErrorStatus(CLOGERROR_TIMEIN) ){
		}
		else{
			Eixo->MErros.SetErrorStatus(CLOGERROR_TIMEIN,"Eixo %d",Eixo->Number);
		}
		Eixo->EtapRE = EixoREN0;
		Eixo->Comm.Disconnect();
	}
	if ( Eixo->Comm.GetErrors( COMMPROTOCOL ) ){
		if ( Eixo->MErros.GetErrorStatus(CLOGERROR_PROTOCOLO) ){
		}
		else{
			Eixo->MErros.SetErrorStatus(CLOGERROR_PROTOCOLO,"Eixo %d",Eixo->Number);
		}
	}
}



void CPEixo::EixoREError(){
}
	
//Status envio
void CPEixo::EixoRF00(){
	if ( Eixo->TimerF >= 1 ){
		Eixo->TimerF = 0;
		Eixo->EtapRF++;
	}
	else{
		Eixo->TimerF++;
	}	
}

void CPEixo::EixoRF01(){
	PostMessage(hwnd,WM_APP+2,(WPARAM)Eixo,0);
	Eixo->EtapRF=EixoRFN0;
}

void CPEixo::EixoRF02(){
}

void CPEixo::EixoRFEnd(){
	Eixo->Comm.GetQFIFOStatus(&Eixo->Buffer,&Eixo->Send);
}

void CPEixo::EixoRFError(){	
}

//Tratamento de comandos e envios
void CPEixo::EixoRG00(){
	//Inicializa Buffer de comandos
	while (!Eixo->FIFOParCmd.empty()){Eixo->FIFOParCmd.pop();}	
	Eixo->EtapRG++;
}

void CPEixo::EixoRG01(){
	CPPar* Par;
	if (Eixo->FIFOParCmd.empty()){
		Eixo->EtapRG++;
	}
	else{
		Par = Eixo->FIFOParCmd.front();
		Eixo->FIFOParCmd.pop();
		Eixo->CommTS(Par);
	}
}

void CPEixo::EixoRG02(){
	if ( Eixo->Buffer <= 0){
		Eixo->EtapRG = EixoRGNEnd; 
	}
}

void CPEixo::EixoRG03(){
}

void CPEixo::EixoRGEnd(){
	if (!Eixo->FIFOParCmd.empty()){
		Eixo->EtapRG = EixoRGN1;
	}	
	if (	
			Eixo->EtapRA==EixoRANEnd && 
			Eixo->EtapRB==EixoRBNEnd &&  
			Eixo->EtapRC==EixoRCNEnd && 
			Eixo->EtapRD==EixoRDNEnd &&
			Eixo->EtapRE==EixoRENEnd 
			){
	}
	else{
		Eixo->EtapRG = EixoRGN0;
	}
}

void CPEixo::EixoRGError(){	
}

//Fifo IN
void CPEixo::EixoRH00(){
	//Eixo->EtapRH++;
}

void CPEixo::EixoRH01(){
}

void CPEixo::EixoRH02(){
}

void CPEixo::EixoRH03(){
}

void CPEixo::EixoRHEnd(){
	CPPar* Par;
	uint16_t Dado;
	char Valor[10];
	while ( Eixo->Comm.PopQFIFO(Par,&Dado) ){
		Eixo->AllComPPar(&RParList,Par,Dado);
		for (int i = 0;i<Eixo->PageList.size();i++){
			Eixo->AllComPPar(&Eixo->PageList[i].RParList,Par,Dado);
		}
	}
}

void CPEixo::EixoRHError(){	
}

//Definição do Status
void CPEixo::EixoRI00(){
	CPPar* Par;
	Par = Eixo->GetParByOption("STATTF");
	if (Par == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFSTATUS,"Eixo %d",Eixo->Number);
		Eixo->EtapRI++;
	}
	else{
		Eixo->Comm.StatusData.Par = Par;
		Eixo->EtapRI+=2;
	}
}

void CPEixo::EixoRI01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFSTATUS) ){
	}
	else{
		Eixo->EtapRI = EixoRIN0;
	}	
}

void CPEixo::EixoRI02(){
	//Configura o Status;
	uint16_t Dado =0;
	int _Canal = Canal;
	_Canal|= DIRECAO_SOLICITACAO;
	//Envia pela porta e canal correspondente
	CommSer(Eixo->Comm.StatusData.Par,COMMTABLE,&Dado,_Canal);
	Eixo->EtapRI=EixoRINEnd;
}

void CPEixo::EixoRIEnd(){
	if (	
			Eixo->EtapRA==EixoRANEnd && 
			Eixo->EtapRB==EixoRBNEnd &&  
			Eixo->EtapRC==EixoRCNEnd && 
			Eixo->EtapRD==EixoRDNEnd &&
			Eixo->EtapRE==EixoRENEnd 
			){
	}
	else{
		Eixo->EtapRI = EixoRIN0;
	}	
}

void CPEixo::EixoRIError(){
}

//Definição de Bit(Flag) de erro na placa
void CPEixo::EixoRJ00(){
	CPPar* Par;
	Par = Eixo->GetParByOption("FLAGERROR");
	if (Par == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFFERROR,"Eixo %d",Eixo->Number);
		Eixo->EtapRJ++;
	}
	else{
		Eixo->ErrorBit = Par;
		Eixo->EtapRJ=EixoRJNEnd;
	}
}

void CPEixo::EixoRJ01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFFERROR) ){
	}
	else{
		Eixo->EtapRJ = EixoRJN0;
	}	
}

void CPEixo::EixoRJ02(){
	Eixo->EtapRJ = EixoRJN0;
}

void CPEixo::EixoRJEnd(){
}

void CPEixo::EixoRJError(){
}

//Verifica ErrorBit
void CPEixo::EixoRL00(){
	if (	
		Eixo->EtapRJ==EixoRJNEnd 
		){
		Eixo->EtapRL = EixoRLNEnd;
	}
}

void CPEixo::EixoRL01(){
	//Inicializa Timer
	Eixo->TimerL = 5;
	Eixo->EtapRL++;
}

void CPEixo::EixoRL02(){
	//Temporiza
	if ( Eixo->TimerElapseEtap( Eixo->TimerL )) {
		Eixo->EtapRL++;
		//Atualiza Buffer
		Eixo->Comm.GetQFIFOStatus(&Eixo->Buffer,&Eixo->Send);
	}
}


void CPEixo::EixoRL03(){
	//Aguarda solicitar todos
	if ( Eixo->Buffer <= 0){
		Eixo->EtapRL++; 
	}
}

void CPEixo::EixoRL04(){
	//Envia reset para os erros
	Eixo->ResetErrors();
	Eixo->EtapRL++;
}

void CPEixo::EixoRL05(){
	//Inicializa Timer
	Eixo->TimerL = 5;
	Eixo->EtapRL++;
}

void CPEixo::EixoRL06(){
	//Temporiza
	if ( Eixo->TimerElapseEtap( Eixo->TimerL )) {
		Eixo->EtapRL++;
		//Atualiza Buffer
		Eixo->Comm.GetQFIFOStatus(&Eixo->Buffer,&Eixo->Send);
	}
}

void CPEixo::EixoRL07(){
	//Aguarda Enviar todos;
	if ( Eixo->Buffer <= 0){
		Eixo->EtapRL++; 
	}
}

void CPEixo::EixoRLEnd(){
	CPMOpc* MOpc = Eixo->GetMOpc(Eixo->ErrorBit);
	if ( MOpc != NULL ){
		int i = MOpc->getOpcID(Eixo->ErrorBit->Opcoes,Eixo->ErrorBit->getValor());		
		if (i){
			//printf("ERRO NA PLACA\n");
			Eixo->GetErrors();
			Eixo->EtapRL = EixoRLN1;
		}
	}
}

void CPEixo::EixoRLError(){
}

//Verifica Erros da Placa
void CPEixo::EixoRM00(){
}

void CPEixo::EixoRM01(){
}

void CPEixo::EixoRM02(){
}

void CPEixo::EixoRMEnd(){
	if ( Eixo->ErrorBitList.size() > 0){
		CPMOpc* MOpc = Eixo->GetMOpc(Eixo->ErrorBitList[0]);
		for (int i=0;i<Eixo->ErrorBitList.size();i++){
			int Error = MOpc->getOpcID(Eixo->ErrorBitList[i]->Opcoes,Eixo->ErrorBitList[i]->getValor());
			if (Error){
				if ( Eixo->MErros.GetErrorStatus(Eixo->ErrorBitList[i])){
				}
				else{
					Eixo->MErros.SetErrorStatus(Eixo->ErrorBitList[i],"Eixo %d",Eixo->Number);
				}
			}
			char* _Valor = MOpc->getOpcStr(Eixo->ErrorBitList[i]->Opcoes,0);
			if (_Valor != NULL){
				Eixo->ErrorBitList[i]->setValor(_Valor);						
			}
		}
	}
}

void CPEixo::EixoRMError(){
}

//Definição do ErrorOut
void CPEixo::EixoRN00(){
	CPPar* Par;
	Par = Eixo->GetParByOption("ERROROUT");
	if (Par == NULL){
		Eixo->MErros.SetErrorStatus(CLOGERROR_DEFERROROUT,"Eixo %d",Eixo->Number);
		Eixo->EtapRN++;
	}
	else{
		Eixo->ParErrorSet = *Par;
		Eixo->ParErrorReset= *Par;
		strcpy(Eixo->ParErrorSet.Tipo,"ERROROUTSET");
		strcpy(Eixo->ParErrorReset.Tipo,"ERROROUTRESET");
		Eixo->EtapRN+=2;
	}
}

void CPEixo::EixoRN01(){
	if ( Eixo->MErros.GetErrorStatus(CLOGERROR_DEFERROROUT) ){
	}
	else{
		Eixo->EtapRN = EixoRNN0;
	}	
}

void CPEixo::EixoRN02(){
	Eixo->EtapRN=EixoRNNEnd;
}

void CPEixo::EixoRNEnd(){
	if (	
			Eixo->EtapRA==EixoRANEnd && 
			Eixo->EtapRB==EixoRBNEnd &&  
			Eixo->EtapRC==EixoRCNEnd && 
			Eixo->EtapRD==EixoRDNEnd &&
			Eixo->EtapRE==EixoRENEnd 
			){
	}
	else{
		Eixo->EtapRN = EixoRIN0;
	}	
}

void CPEixo::ResetError(){
	PushParCmd(&ParErrorReset);
}

void CPEixo::SetError(){
	PushParCmd(&ParErrorSet);
}

void CPEixo::EixoRNError(){
}


//--------------------------------------------------------------------------

void CPEixo::Load(HWND _hwnd) {
	hwnd = _hwnd;
}

char* CPEixo::GetValor(const char* Option){
	for (int a =0;a<PageList.size();a++){
		for (int b=0;b<PageList[a].PMenuList.size();b++){
			for (int c=0;c<PageList[a].PMenuList[b].ParList.size();c++){
				if ( strcmp(PageList[a].PMenuList[b].ParList[c].Opcoes,Option)==0){
					return PageList[a].PMenuList[b].ParList[c].Valor;
				}
			}
		}
	}
	return NULL;
}

CPPar* CPEixo::GetParByOption(const char* Option){
	for (int a =0;a<PageList.size();a++){
		for (int b=0;b<PageList[a].PMenuList.size();b++){
			for (int c=0;c<PageList[a].PMenuList[b].ParList.size();c++){
				if ( strcmp(PageList[a].PMenuList[b].ParList[c].Opcoes,Option)==0){
					return &PageList[a].PMenuList[b].ParList[c];
				}
			}
		}
	}
	return NULL;
}

void CPEixo::SetRTChangePort(){
	SetRT(&EtapRA,EixoRAN4);
}

void CPEixo::SetRTChangeCanal(){
	SetRT(&EtapRB,EixoRBN2);
}

void CPEixo::SetRTChangeFator(){
	SetRT(&EtapRC,EixoRCN2);
}

void CPEixo::SetRTChangePGiro(){
	SetRT(&EtapRD,EixoRDN2);
}

void CPEixo::SetRTSendAll(){
	//To usando o Change Canal que tem o mesmo efeito
	SetRT(&EtapRB,EixoRBN2);
}

void CPEixo::SetRT(int *RTState,int StateNumber){
	WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
	*RTState = StateNumber;
	ReleaseMutex(DMan::DM.ThreadTime);	
}

CPMOpc* CPEixo::GetMOpc(CPPar* Par){
	for (int b = 0;b<PageList.size();b++){
		for (int c = 0;c<PageList[b].PMenuList.size();c++){
			for (int d = 0;d<PageList[b].PMenuList[c].ParList.size();d++){
				if ( PageList[b].PMenuList[c].ParList[d].ID == Par->ID){
					return &PageList[b].MOpc;
				}
			}
		}
	}
	return NULL;	
}

void CPEixo::CommTSAll(){
	//Envia todos parametros de endereços comuns
	for (int i = 0;i<RParList.size();i++){
		PParComAll( &RParList[i] );
	}
	//Configura solicitaçoes de pagina
}

void CPEixo::MakeRPar(){
	for (int b = 0;b<PageList.size();b++){
		PageList[b].MakeRPar();
		for (int c = 0;c<PageList[b].PMenuList.size();c++){
			for (int d = 0;d<PageList[b].PMenuList[c].ParList.size();d++){
				if(RParList.empty()){
					std::string NomePar;
					CRPar tmpRPar;
					tmpRPar.ParList.push_back(&PageList[b].PMenuList[c].ParList[d]);
					NomePar = "Grupo de endereco";
					tmpRPar.Par = PageList[b].PMenuList[c].ParList[d];
					strcpy(tmpRPar.Par.Nome,NomePar.c_str());
					RParList.push_back(tmpRPar);
				}
				else{
					bool found = false;
					for (int i=0;i<RParList.size();i++){
						if ( RParList[i].ParList[0]->End == PageList[b].PMenuList[c].ParList[d].End ){
							RParList[i].ParList.push_back(&PageList[b].PMenuList[c].ParList[d]);
							found = true;
							break;
						}
					}
					if (!found){
						std::string NomePar;
						CRPar tmpRPar;
						tmpRPar.ParList.push_back(&PageList[b].PMenuList[c].ParList[d]);
						NomePar = "Grupo de endereco";
						tmpRPar.Par = PageList[b].PMenuList[c].ParList[d];
						strcpy(tmpRPar.Par.Nome,NomePar.c_str());
						RParList.push_back(tmpRPar);
					}
				}
			}
		}
	//for (int i=0;i<RParList.size();i++){
	//	printf("Parametros de mesmo endereco:%s \n",RParList[i].Par.Nome);
	//	for (int j=0;j<RParList[i].ParList.size();j++){
	//		printf(" End:%d %s\n",RParList[i].ParList[j]->End,RParList[i].ParList[j]->Nome);
	//	}
	//	printf("\n");
	//}
	}
}


void CPEixo::GetErrors(){
	int _Canal = Canal;
	int CommTipo = COMMFIFO;
	_Canal|= DIRECAO_SOLICITACAO;
	for (int i = 0;i<RParList.size();i++){
		RParList[i].Dado = 0;
		bool ErrorBitFound = false;
		for (int j = 0;j<RParList[i].ParList.size();j++){
			switch (RParList[i].ParList[j]->getTipo()){
				case PCIERRORBIT:{
					//printf ("%s \n",RParList[i].ParList[j]->Nome);
					ErrorBitFound =true;
				}
				break;
				default:{
				}
				break;
			}
		}
		if (ErrorBitFound){
			CommSer(&RParList[i].Par,CommTipo,&RParList[i].Dado,_Canal);
			//printf ("%s:%d \n",RParList[i].Par.Nome,RParList[i].Par.End);
		}
	}
}

void CPEixo::ResetErrors(){
//Reseta flag de indicação de erro
	int _Canal = Canal;
	int CommTipo = COMMFIFO;
	_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
	uint16_t VDado = 0x0001;
	VDado <<= ErrorBit->Bit;
	CommSer(ErrorBit,CommTipo,&VDado,_Canal);
//Reseta todos bits de erro
	_Canal = Canal;
	CommTipo = COMMFIFO;
	_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
	for (int i = 0;i<RParList.size();i++){
		RParList[i].Dado = 0;
		bool ErrorBitFound = false;
		for (int j = 0;j<RParList[i].ParList.size();j++){
			switch (RParList[i].ParList[j]->getTipo()){
				case PCIERRORBIT:{
					ErrorBitFound =true;
					uint16_t VDado = 0x0001;
					VDado <<= RParList[i].ParList[j]->Bit;
					RParList[i].Dado |= VDado;
				}
				break;
				default:{
				}
				break;
			}
		}
		if (ErrorBitFound){
			CommSer(&RParList[i].Par,CommTipo,&RParList[i].Dado,_Canal);
			//printf ("%s:%d Dado:%x \n",RParList[i].Par.Nome,RParList[i].Par.End,RParList[i].Dado);
		}
	}
}


void CPEixo::PParComAll(CRPar* RPar){
	int _Canal = Canal;
	RPar->Dado = 0;
	int CommTipo = COMMFIFO;
	_Canal|= DIRECAO_ENVIO;
	bool Send = false;
	for ( int i =0;i<RPar->ParList.size();i++){
		switch (RPar->ParList[i]->getTipo()){
			case PCIERROR:
			case PCITABCONTROL:
			case PCICOMBUFSENDBAR:
			case PCIERRORBIT:
			case PCIBUTOP:
			case PCISTATUSBIT:
			case PCILABEL:
			case PCITESTEVERIFICACAO:
			case PCITVBYTE:
			case PCITVBIT:
			case PCIATVBYTE:
			case PCIATVBIT:
			case PCIBUTTON:{
			}
			break;
			case PCILEDIT:{
				RPar->Dado = ConvValToD(RPar->ParList[i]);
				Send = true;
			}
			break;
			case PCILEDITL:{
				uint16_t Dado = ConvValToD(RPar->ParList[i]);
				 Dado &= 0x00FF;
				RPar->Dado |= Dado;
				Send = true;
			}
			break;
			case PCILEDITH:{
				uint16_t Dado = ConvValToD(RPar->ParList[i]);
				Dado<<=8;
				Dado &= 0xFF00;
				RPar->Dado |= Dado;
				Send = true;
			}
			break;
			case PCILCOMBOBOX:{
				uint16_t shift=0;
				CPMOpc* MOpc = GetMOpc(RPar->ParList[i]);
				shift = MOpc->getMaskReset(RPar->ParList[i]->Opcoes);
				if (RPar->ParList[i]->Bit == 0){
					shift = MOpc->getOpcID(RPar->ParList[i]->Opcoes,RPar->ParList[i]->getValor());
				}
				else{
					shift = MOpc->getOpcID(RPar->ParList[i]->Opcoes,RPar->ParList[i]->getValor());
					shift<<=RPar->ParList[i]->Bit;
				}
				RPar->Dado |= shift;
				Send = true;
			}
			break;
			default:{
				printf("Nao definido metodo de envio COMMALL de %s\n",RPar->ParList[i]->Tipo);
			}
			break;
		}
	}
	//Envia pela porta e canal correspondente
	if (Send){
		CommSer(&RPar->Par,CommTipo,&RPar->Dado,_Canal);
	}
}

void CPEixo::PParComAllReadPage(CPEPage* Page){
	int _Canal = Canal;
	uint16_t Dado = 0;
	_Canal|= DIRECAO_SOLICITACAO;
	//printf("Page:%s\n ",Page->Nome);
	for (int i = 0;i<Page->ReadRParList.size();i++){
		CommSer(&Page->ReadRParList[i].Par,COMMPAGE,&Dado,_Canal);
		//printf(" Par:%x\n ",Page->ReadRParList[i].Par.End);
	}
	//printf("\n");
}

void CPEixo::AllComPPar(std::vector<CRPar>* RParL,CPPar* Par,uint16_t Dado){
	for ( int i =0;i<(*RParL).size();i++){
		if ( (*RParL)[i].Par.End == Par->End ){
			for ( int j =0;j<(*RParL)[i].ParList.size();j++){
				switch ((*RParL)[i].ParList[j]->getTipo()){
					case PCIERROR:
					case PCITABCONTROL:
					case PCICOMBUFSENDBAR:
					case PCIBUTTON: 
					case PCIBUTOP:
					case PCILEDIT:
					case PCILEDITL:
					case PCILEDITH:
					case PCIATVBYTE:
					case PCIATVBIT:
					case PCITESTEVERIFICACAO:
					case PCILCOMBOBOX:{
						//Não interpretam entrada
					}
					break;
					case PCITVBIT:{
						int VDado = Dado;
						uint16_t shift=0;
						shift = (*RParL)[i].ParList[j]->Bit;
						VDado = VDado>>shift;
						VDado &= 0x0001;
						ConvDToVal((*RParL)[i].ParList[j],VDado);
						(*RParL)[i].ParList[j]->Color = TESTVERCOLOR;
					}
					break;
					case PCITVBYTE:{
						ConvDToVal((*RParL)[i].ParList[j],Dado);
						(*RParL)[i].ParList[j]->Color = TESTVERCOLOR;
					}
					case PCILABEL:{
						ConvDToVal((*RParL)[i].ParList[j],Dado);
					}
					break;
					case PCIERRORBIT:
					case PCISTATUSBIT:{
						int VDado = Dado;
						CPMOpc* MOpc = GetMOpc((*RParL)[i].ParList[j]);
						uint16_t shift=0;
						shift = (*RParL)[i].ParList[j]->Bit;
						VDado = VDado>>shift;
						VDado &= 0x0001;
						char* _Valor = MOpc->getOpcStr((*RParL)[i].ParList[j]->Opcoes,VDado);
						if (_Valor != NULL){
							(*RParL)[i].ParList[j]->setValor(_Valor);						
						}
					}
					break;
					default:{
						printf("Nao definido metodo de recebimento COMMALL de %s\n",(*RParL)[i].ParList[j]->Tipo);
					}
					break;
				}
				PostMessage(hwnd,WM_APP+5,(WPARAM)(*RParL)[i].ParList[j],0);
			}
			break;
		}
	}
}

void CPEixo::CommTS(CPPar* Par){
	int _Canal;
	_Canal = Canal;
	uint16_t Dado = 0;
	//Converte
	switch (Par->getTipo()){
		case PCIBUTTON: {
			CPMOpc* MOpc = GetMOpc(Par);
			int shift = MOpc->getOpcID(Par->Opcoes,Par->getValor())+1;
			shift<<=6;
			_Canal|= shift;
			uint16_t Mask = 0x01;
			for (int j=0;j<Par->Bit;j++){
				Mask*=2;
			}
			Dado = Mask;
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCIBUTOP: {
			int shift=0;
			CPMOpc* MOpc = GetMOpc(Par);
			shift = MOpc->getMaskReset(Par->Opcoes);
			_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			if (Par->Bit == 0){
			}
			else{
				shift <<= (Par->Bit);
			}
			Dado = shift;
			CommSer(Par,COMMFIFO,&Dado,_Canal);
			
			_Canal = Canal;
			Dado = 0;
			_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			if (Par->Bit == 0){
				Dado = MOpc->getOpcID(Par->Opcoes,Par->getValor());
			}
			else{
				shift = MOpc->getOpcID(Par->Opcoes,Par->getValor());
				if (Par->Bit == 0){
				}
				else{
					shift<<=Par->Bit;
				}
				Dado = shift;
			}
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCITVBIT:{
			uint16_t SetRes  = ConvValToD(Par);
			int shift = Par->Bit;
			Dado = 0x0001;
			Dado <<= shift;
			if (SetRes){
				_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			}
			else{
				_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			}
			CommSer(Par,COMMFIFO,&Dado,_Canal);			
		}
		break;
		case PCITVBYTE:
		case PCILEDIT: {
			_Canal|= DIRECAO_ENVIO;
			Dado = ConvValToD(Par);
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCILEDITL: {
			_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			Dado = 0x00FF;
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
			
			_Canal = Canal;
			_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			Dado = ConvValToD(Par);
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCILEDITH: {
			_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			Dado = 0xFF00;
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
			
			_Canal = Canal;
			_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			Dado = ConvValToD(Par);
			Dado<<=8;
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCILCOMBOBOX: {
			int shift=0;
			CPMOpc* MOpc = GetMOpc(Par);
			shift = MOpc->getMaskReset(Par->Opcoes);
			_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			if (Par->Bit == 0){
			}
			else{
				shift <<= (Par->Bit);
			}
			Dado = shift;
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMFIFO,&Dado,_Canal);
			
			_Canal = Canal;
			Dado = 0;
			_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			if (Par->Bit == 0){
				Dado = MOpc->getOpcID(Par->Opcoes,Par->getValor());
			}
			else{
				shift = MOpc->getOpcID(Par->Opcoes,Par->getValor());
				if (Par->Bit == 0){
				}
				else{
					shift<<=Par->Bit;
				}
				Dado = shift;
			}
			CommSer(Par,COMMFIFO,&Dado,_Canal);
		}
		break;
		case PCILABEL:{
			_Canal|= DIRECAO_SOLICITACAO;
			Dado = 0;//ConvValToD(Par);
			//Envia pela porta e canal correspondente
			CommSer(Par,COMMTABLE,&Dado,_Canal);
			//CommSer(Par,COMMFIFO,Dado,Canal);
		}
		break;
		case PCIERRORBIT:{
		}
		break;
		case PCIERROROUTSET:{
			int shift = Par->Bit;
			Dado = 0x0001;
			Dado <<= shift;
			_Canal|= DIRECAO_MASCARA_RESETAR_BITS;
			CommSer(Par,COMMFIFO,&Dado,_Canal);			
			printf("SET Erro Eixo:%d!!!\n",Number);
		}
		break;
		case PCIERROROUTRESET:{
			int shift = Par->Bit;
			Dado = 0x0001;
			Dado <<= shift;
			_Canal|= DIRECAO_MASCARA_SETAR_BITS;
			CommSer(Par,COMMFIFO,&Dado,_Canal);			
			printf("RESET Erro Eixo:%d!!!\n",Number);
		}
		break;
		default:{
			printf("Não definido metodo de envio COMM de %s",Par->Tipo);
		}
		break;
	}
}

void CPEixo::CommSer(CPPar* Par,int Option,uint16_t* Dado,int _Canal){
	if ( Par->End == 0){
		return;
	}
	switch (Option){
		case COMMFIFO:{
			Comm.PushQFIFO(Par,&Par->End,Dado,&_Canal);
		}
		break;
		case COMMTABLE:{
			Comm.PushVTable(Par,&Par->End,Dado,&_Canal);
		}
		break;
		case COMMPAGE:{
			Comm.PushPageTable(Par,&Par->End,Dado,&_Canal);
			//printf()
		}
		break;
		default:{
		}
		break;
	}
}

bool CPEixo::PushParCmd(CPPar* Par){
	WaitForSingleObject( DMan::DM.ThreadTime,INFINITE );
	if (	
			EtapRA==EixoRANEnd && 
			EtapRB==EixoRBNEnd &&  
			EtapRC==EixoRCNEnd && 
			EtapRD==EixoRDNEnd &&
			EtapRE==EixoRENEnd 
			){
		FIFOParCmd.push(Par);
		ReleaseMutex(DMan::DM.ThreadTime);	
		return true;
	}
	else {
		ReleaseMutex(DMan::DM.ThreadTime);	
		return false;
	}
}

uint16_t CPEixo::ConvValToD(CPPar* Par){
	std::string strDado;
	strDado = Par->getValor();
	uint16_t Dado;
	float tmpDado = atof(strDado.c_str());
	switch (Par->getFator()){
		case NOFAT:{
			Dado = tmpDado;
		}
		break;
		case MMFAT:{
			Dado = tmpDado*(PulsoVolta/FatorPulso_mm);
		}
		break;
		case MMFAT200:{
			Dado = 512+(tmpDado*(PulsoVolta/FatorPulso_mm));
			//printf("Constantes:Fator:%f PulsoVolta:%d \n\n",FatorPulso_mm,PulsoVolta);
			//printf("Calculo:%s::%f -> %x\n",Par->Nome,tmpDado,Dado);
		}
		break;
		case MILISEC:{
			Dado = ((tmpDado*1000)*1024)/1000;
		}
		break;
		case BITFAT:
		case HEXFAT:{
			int tmpDado;
			ConvVtoD(strDado.c_str(),"%04x",&tmpDado);
			Dado = tmpDado;
		}
		break;
		default:{
		}
		break;
	}
	return Dado;
}

void CPEixo::ConvDToVal(CPPar* Par,uint16_t Dado){
	std::string strDado;
	strDado = Par->getValor();
	char Valor[25];
	float tmpDado;
	switch (Par->getFator()){
		case NOFAT:{
			ConvReceiveD(Valor,"%0.2f",Dado);
		}
		break;
		case MMFAT:{
			tmpDado = (Dado*FatorPulso_mm)/PulsoVolta;
			ConvReceiveD(Valor,"%0.2f",tmpDado);
		}
		break;
		case MMFAT200:{
			tmpDado = ((Dado - 512)*FatorPulso_mm)/PulsoVolta;
			ConvReceiveD(Valor,"%0.2f",tmpDado);
		}
		break;
		case MILISEC:{
			tmpDado = (Dado*1000)/(1024*1000);
			ConvReceiveD(Valor,"%0.2f",tmpDado);
		}
		break;
		case HEXFAT:{
			ConvReceiveD(Valor,"%04X",Dado);
		}
		break;
		case BITFAT:{
			ConvReceiveD(Valor,"%01X",Dado);
		}
		default:{
		}
		break;
	}
	Par->setValor(Valor);
}
