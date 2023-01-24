#include    "..\Inc\CPMascErro.h"

CPErro::CPErro(){
	memset (Origem,'\0',50);
	memset (Men,'\0',128);	
	memset (Comments,'\0',128);	
	Status = false;
	Par = NULL;
}

CPMErro::CPMErro(){
}

void CPMErro::Init(){
//Erros internos
	SetError( CLOGERROR_MAINPARAXIS,"SFiles","Erro nos parametros principais dos eixos");
	SetError( CLOGERROR_FINDPORTA,"WIN","Nao encontrou a Porta serial(GetComOp)");
	SetError( CLOGERROR_INITPORTA,"WIN","Nao conseguiu inicializar a Porta serial");
	SetError( CLOGERROR_PORTANC,"SFiles","Porta serial nao definida");
	SetError( CLOGERROR_OPCMENU,"SFiles","Nao encontrou opcoes de menu");
	SetError( CLOGERROR_DEFCANAL,"SFiles","Nao encontrou canal (DefCanal)");
	SetError( CLOGERROR_DEFFATOR,"SFiles","Nao encontrou fator (MENFAT)");
	SetError( CLOGERROR_DEFPGIRO,"SFiles","Nao encontrou pulso/volta (PGiro)");
	SetError( CLOGERROR_TIMEIN,"COM","Serial TimerIn");	
	SetError( CLOGERROR_PROTOCOLO,"COM","Erro de protocolo");	
	SetError( CLOGERROR_DEFSTATUS,"SFiles","Nao encontrou Status (STATTF)");
	SetError( CLOGERROR_DEFFERROR,"SFiles","Nao encontrou Flag de erro (FLAGERROR)");
	SetError( CLOGERROR_DEFERROROUT,"SFiles","Nao encontrou Saida de erro (ERROROUT)");
}

void CPMErro::SetError(CPPar* Par){
	CPErro Erro;
	Erro.Par = Par;
	memset (Erro.Origem,'\0',49);
	memset (Erro.Men,'\0',127);
	strcpy(Erro.Origem,"Placa");
	strcpy(Erro.Men,Par->Nome);
	Erro.Cod = CLOGERROR_PLACA;
	ErrorTable.push_back(Erro);
}

void CPMErro::SetError(int Cod,char* Origem,char* Men){
	CPErro Erro;
	memset (Erro.Origem,'\0',49);
	memset (Erro.Men,'\0',127);
	strcpy(Erro.Origem,Origem);
	strcpy(Erro.Men,Men);
	Erro.Cod = Cod;
	ErrorTable.push_back(Erro);
}

void CPMErro::SetErrorStatus(int Cod){
	if (!GetErrorStatus(Cod)){
		for (int i = 0;i < ErrorTable.size();i++){
			if (Cod == ErrorTable[i].Cod){
				ErrorTable[i].Status = true;
				ListError.push_back(&ErrorTable[i]);
			}
		}
	}
}

void CPMErro::SetErrorStatus(CPPar* Par){
	if (!GetErrorStatus(Par)){
		for (int i = 0;i < ErrorTable.size();i++){
			if (Par == ErrorTable[i].Par){
				ErrorTable[i].Status = true;
				ListError.push_back(&ErrorTable[i]);
			}
		}
	}
}

void CPMErro::SetErrorStatus(int Cod,const char* Comments,...){
	char buffer[128];
	if (!GetErrorStatus(Cod)){
		va_list args;
		va_start (args, Comments);
		vsprintf (buffer,Comments, args);
		for (int i = 0;i < ErrorTable.size();i++){
			if (Cod == ErrorTable[i].Cod){
				ErrorTable[i].Status = true;
				strcpy(ErrorTable[i].Comments,buffer);
				ListError.push_back(&ErrorTable[i]);
			}
		}
	}
}

void CPMErro::SetErrorStatus(CPPar* Par,const char* Comments,...){
	char buffer[128];
	if (!GetErrorStatus(Par)){
		va_list args;
		va_start (args, Comments);
		vsprintf (buffer,Comments, args);
		for (int i = 0;i < ErrorTable.size();i++){
			if (Par == ErrorTable[i].Par){
				ErrorTable[i].Status = true;
				strcpy(ErrorTable[i].Comments,buffer);
				ListError.push_back(&ErrorTable[i]);
			}
		}
	}
}

void CPMErro::ResetErrorStatus(int Cod){
	for (int i = 0;i < ErrorTable.size();i++){
		if (Cod == ErrorTable[i].Cod){
			ErrorTable[i].Status = false;
		}
	}
}

void CPMErro::ResetErrorStatus(CPPar* Par){
	for (int i = 0;i < ErrorTable.size();i++){
		if (Par == ErrorTable[i].Par){
			ErrorTable[i].Status = false;
		}
	}
}

bool CPMErro::GetErrorStatus(int Cod){
	for (int i = 0;i < ErrorTable.size();i++){
		if (Cod == ErrorTable[i].Cod){
			return ErrorTable[i].Status;
		}
	}
	return true;
}

bool CPMErro::GetErrorStatus(CPPar* Par){
	for (int i = 0;i < ErrorTable.size();i++){
		if (Par == ErrorTable[i].Par){
			return ErrorTable[i].Status;
		}
	}
	return true;
}

CPErro* CPMErro::GetLastError(){
	if (ListError.size() <= 0){
		return NULL;
	}
	else{
		CPErro *Erro = ListError.front();
		//printf("ErroAdress:%x\n",Erro);
		//printf("ErroAdress:%x\n",ListError.front());
		//system ("pause");
		ListError.erase(ListError.begin());
		return Erro;
	}
}