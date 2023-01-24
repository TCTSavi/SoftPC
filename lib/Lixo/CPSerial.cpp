#include "..\Inc\CPSerial.h"

CPSerial::CPSerial(){
	PortList.clear();
}

CPPorta::CPPorta(){
}

void CPPorta::OnInit(){
	hCom = CreateFile( 
		PortName,
		GENERIC_READ | GENERIC_WRITE,
		0,    // exclusive access 
		NULL, // default security attributes 
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL 
	);
	
	if (hCom == INVALID_HANDLE_VALUE){
		std::string Erro;
		Erro = "Erro da porta serial: ";
		Erro += PortName;
		CLog::Log.InsertWarn("PC",GetLastError(),Erro.c_str());
		return;
	}

	if (!GetCommTimeouts( hCom, &timeouts)){
		CLog::Log.InsertWarn("PC",GetLastError(),"Erro da porta serial");
		return;
	}
		
	timeouts.ReadIntervalTimeout = 100; 
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 100;

	if (!SetCommTimeouts(hCom, &timeouts)){
		CLog::Log.InsertWarn("PC",GetLastError(),"Erro da porta serial");
		return;
	}
	
	DCB dcb = {0};
	dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(hCom, &dcb)){
		CLog::Log.InsertWarn("PC",GetLastError(),"Erro da porta serial");
		return;	
	}

    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
	
    if (!SetCommState(hCom, &dcb)){
		CLog::Log.InsertWarn("PC",GetLastError(),"Erro da porta serial");
		return;
	}
	
	SetupComm(hCom, 2048, 1024);
	
	/*
	DWORD dwStoredFlags;
	dwStoredFlags = EV_BREAK | EV_CTS   | EV_DSR | EV_ERR | EV_RING | EV_RLSD | EV_RXCHAR | EV_RXFLAG | EV_TXEMPTY ;
	if (!SetCommMask(hCom, dwStoredFlags))	
	*/
	
	PThread = CreateThread( 
		NULL,
		0,
		(LPTHREAD_START_ROUTINE) &Teste,
		this, 
		0, 
		NULL
	);
}

void CPPorta::OnEnd(){
	CloseHandle(hCom);
	SuspendThread(PThread);
}

void CPSerial::OnInit(){
	for (int i=0;i<PortList.size();i++){
		PortList[i].OnInit();
	}
}

void CPSerial::OnEnd(){
	for (int i=0;i<PortList.size();i++){
		PortList[i].OnEnd();
	}
}

void CPSerial::NewPort(const char* PortName){
	CPPorta Porta;
	strcpy (Porta.PortName,PortName);
	PortList.push_back(Porta);
}


void CPPorta::Read(){
	BOOL fThreadDone = FALSE;
	DWORD dwRead;          // bytes actually read
	unsigned char  	lpBuf[64];
	BOOL fWaitingOnRead = FALSE;
	DWORD dwRes;           // result from WaitForSingleObject
	OVERLAPPED osReader = {0};  // overlapped structure for read operations
	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	
	if (osReader.hEvent == NULL){
		//ERRO
	}
	while ( !fThreadDone ) {
		if (!fWaitingOnRead) {
			if (!ReadFile(hCom, lpBuf, 64, &dwRead, &osReader)) {
                if (GetLastError() != ERROR_IO_PENDING){	  // read not delayed?
                    //Erro
				}
                fWaitingOnRead = TRUE;
            }
            else {    // read completed immediately
                if (dwRead){
					for (int i =0; i<dwRead;i++){
						//oss2 << lpBuf[i] << "A";
					}
					printf ("A Serial: %i \n",lpBuf[1]);
					//oss2 << "A ";
                    //Leu
				}
            }
        }
		if ( fWaitingOnRead ) {
			dwRes = WaitForSingleObject(osReader.hEvent, 500);		
			switch(dwRes){
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hCom, &osReader, &dwRead, FALSE)){
					// Error in communications; report it.
				}
				else{
					if (dwRead){
						//for (int i =0; i<dwRead;i++){
						//	oss2 << lpBuf[i];
						//}
						printf ("B Serial: Numero de bytes %d \n",dwRead);
						for (int i =0; i<dwRead;i++){
							printf ("%X ",lpBuf[i]);
						}
						//printf ("\n");
						//oss2.str(L"");
						//oss2.clear();
						//oss2 << lpBuf;
						//Leu
					}
				}
				fWaitingOnRead = FALSE;
				break;
				case WAIT_TIMEOUT:
					//contador++;	
					// Operation isn't complete yet. fWaitingOnRead flag isn't
					// changed since I'll loop back around, and I don't want
					// to issue another read until the first one finishes.
					//
					// This is a good time to do some background work.
				break;                       

				default:
					// Error in the WaitForSingleObject; abort.
					// This indicates a problem with the OVERLAPPED structure's
					// event handle.
				break;	
			}
		}
	}
}

void CPPorta::Write(int * lpBuf, DWORD dwToWrite){
    OVERLAPPED osWrite = {0};
    HANDLE hArray[2];
    DWORD dwWritten;
    DWORD dwRes;
    //
    // create this writes overlapped structure hEvent
    //
    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osWrite.hEvent == NULL){
        //ERRO
	}
    //
    // issue write
    //
	CLog::Log.Add("Porta:%s Inside:%d:%d \r\n\r\n",PortName,dwToWrite,lpBuf);

	if (!WriteFile(hCom, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
        if (GetLastError() != ERROR_IO_PENDING) { 
			// WriteFile failed, but isn't delayed. Report error and abort.
			//Enviando = false;
		}
		dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
		switch(dwRes){
			// OVERLAPPED structure's event has been signaled. 
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hCom, &osWrite, &dwWritten, FALSE)){
					//Enviando = false;
					//Erro
				}
				else{
					//Enviou
					//Enviando = false;
				}
				break;
            default:
				// An error has occurred in WaitForSingleObject.
				// This usually indicates a problem with the
                // OVERLAPPED structure's event handle.
			break;
		}
	}
    else {
        //
        // Enviou imediatamente
        //
		//Enviando = false;
    }
    CloseHandle(osWrite.hEvent);
	return;
}

void CPPorta::Teste(void* Param){
	CPPorta* Porta = (CPPorta*) Param;
	while (true){
	}
}

/*
switch(Etapa){
	//Verifica buffer de saida se > 0 etapa++
	case 0:{
		
	}
	break;
	//
	case 1:{
	}
	break;
	default:{
	}
	break;
}
*/
	