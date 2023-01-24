#include    "..\Inc\CPDevMan.h"

DMan DMan::DM;

DMan::DMan(){
}

void DMan::OnInit(){
	ThreadTime = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
	);
}

CPPorta* DMan::GetPort(const char* PortName){
	for (int i = 0; i < PortList.size() ;i++){
		if ( strcmp (PortList[i]->PortName,PortName) == 0){
			PortList.push_back(PortList[i]);
			return PortList[i];
		}
	}
	CPPorta* Porta = new CPPorta;
	Porta->SetName(PortName);
	int Erro;
	Erro  = Porta->OnInit();
	if (Erro !=0){
		//Não conseguiu inicializar a porta
		return NULL;
	}
	PortList.push_back(Porta);
	return Porta;
}

void DMan::OnEnd(){
	for (int i = 0; i < PortList.size() ;i++){
		PortList[i]->FreehCom();
		delete PortList[i];
	}
	//CloseHandle(ThreadTime);
}

void DMan::FreePort(CPPorta* Porta){
	if ( Porta == NULL){
		return;
	}
	//int i=0;
	for (int i = 0; i < PortList.size() ;i++){
		if ( Porta == PortList[i] ){
			PortList.erase (PortList.begin()+i);
			break;
		}
	}
	for (int i = 0; i < PortList.size() ;i++){
		if ( Porta == PortList[i] ){
			return;
		}
	}
	Porta->FreehCom();
	printf("Libera porta %s\n",Porta->PortName);
	delete Porta;
}