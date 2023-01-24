#include "..\Inc\CPPorta.h"

CPPorta::CPPorta(){
	PortaMutex  = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (PortaMutex == NULL) 
    {
        //ERROR;
	}
}

int CPPorta::OnInit(){
	std::string _PortName;
	_PortName = "\\\\.\\";
	_PortName += PortName;

	if (hCom == INVALID_HANDLE_VALUE){
	}
	else{
		FreehCom();
	}
		
	hCom = CreateFile( 
		_PortName.c_str(),
		GENERIC_READ | GENERIC_WRITE,	
		0,    // exclusive access 
		NULL, // default security attributes 
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL 
	);
	
	if (hCom == INVALID_HANDLE_VALUE){
		return GetLastError();

	}

	if (!GetCommTimeouts( hCom, &timeouts)){
		//CLog::Log.SetErrorStatus( CLOGERROR_INITPORTA,"%s",GetLastError());
		return GetLastError();
	}
		
	timeouts.ReadIntervalTimeout = 30; 
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;

	if (!SetCommTimeouts(hCom, &timeouts)){
		//CLog::Log.SetErrorStatus( CLOGERROR_INITPORTA,"%s",GetLastError());
		return GetLastError();
	}
	
	DCB dcb = {0};
	dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(hCom, &dcb)){
		//CLog::Log.SetErrorStatus( CLOGERROR_INITPORTA,"%s",GetLastError());
		return GetLastError();
	}

    dcb.BaudRate = CBR_2400;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
	
    if (!SetCommState(hCom, &dcb)){
		//CLog::Log.InsertWarn("PC",GetLastError(),"Erro da porta serial");
		return GetLastError();
	}
	
	SetupComm(hCom, 2048, 1024);
	
	
	DWORD dwStoredFlags;
	dwStoredFlags = EV_TXEMPTY ;
	if (!SetCommMask(hCom, dwStoredFlags))	
	
	TimerOutInterno = 0;
	StartReadTime = 0;
	return 0;
}

void CPPorta::OnEnd(){
	CloseHandle(hCom);
}

bool CPPorta::Read(unsigned char * lpBuf, DWORD* dwRead){
	BOOL fWaitingOnRead = FALSE;
	DWORD dwRes;           // result from WaitForSingleObject
	OVERLAPPED osReader = {0};  // overlapped structure for read operations
	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	
	bool StatusRead = false;
	if (osReader.hEvent == NULL){
		//ERRO
	}
	if (!fWaitingOnRead) {
		if (!ReadFile(hCom, lpBuf, 64, dwRead, &osReader)) {
			if (GetLastError() != ERROR_IO_PENDING){	  // read not delayed?
				//printf ("Erro\n");
                   //Erro
			}
			fWaitingOnRead = TRUE;
		}
		else {    // read completed immediately
			if (*dwRead){
				//Trata
			}
		}
	}
	if( fWaitingOnRead ){
		dwRes = WaitForSingleObject(osReader.hEvent,1000);		
		switch(dwRes){
			case WAIT_OBJECT_0:{
				if (!GetOverlappedResult(hCom, &osReader, dwRead, FALSE)){
				// Error in communications; report it.
				}
				else{
					if (*dwRead){
						StatusRead = true;
						//printf(" Retorno: ");
						//	for(int i=0;i<*dwRead;i++){
						//		printf("%02x ",lpBuf[i]);
						//	}
						//printf("\n\n");
						//Trata
					}
				}
				fWaitingOnRead = FALSE;
			}
			break;
			case WAIT_TIMEOUT:
				CancelIo(hCom);
				//printf ("TimeOut\n");
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
	CloseHandle (osReader.hEvent);
	return StatusRead;
}

bool CPPorta::Write(unsigned char * lpBuf, DWORD dwToWrite){
    OVERLAPPED osWrite = {0};
    DWORD dwWritten;
    DWORD dwRes;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER liStart;
	LARGE_INTEGER liStop;	
	bool StatusWrite = false;
	QueryPerformanceFrequency(&Frequency);
    //
    // create this writes overlapped structure hEvent
    //
    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osWrite.hEvent == NULL){
        //ERRO
	}
	QueryPerformanceCounter(&liStart);
	if (!WriteFile(hCom, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
        if (GetLastError() != ERROR_IO_PENDING) { 
			// WriteFile failed, but isn't delayed. Report error and abort.
			//Enviando = false;
		}
		dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
		switch(dwRes){
			// OVERLAPPED structure's event has been signaled. 
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hCom, &osWrite, &dwWritten, TRUE)){
					//Enviando = false;
				}
				else{
					QueryPerformanceCounter(&liStop);
					LONGLONG llTimeDiff = liStop.QuadPart - liStart.QuadPart;
					double dftDuration = (double) llTimeDiff * 1000.0 / (double) Frequency.QuadPart;
					//printf(" Envio__: ");
					//for(int i=0;i<dwToWrite;i++){
					//	printf("%02x ",lpBuf[i]);
					//}
					//printf(" (Time F:%4.3f)\n",dftDuration);
					StatusWrite = true;
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
    else {// Enviou imediatamente
		//TimerOutInterno = GetTickCount() - StartReadTime;
		//printf(" Tick:%d\n",GetTickCount());
		for(int i=0;i<dwToWrite;i++){
		printf("%02x ",lpBuf[i]);
		}
		printf(" (Time:%d) %d bytes\n",TimerOutInterno,dwWritten);
    }
    CloseHandle(osWrite.hEvent);
	return StatusWrite;
}

void  CPPorta::SetName(const char* Name){
	strcpy(PortName,Name);
}

void CPPorta::FreehCom(){
	CloseHandle(hCom);
}

