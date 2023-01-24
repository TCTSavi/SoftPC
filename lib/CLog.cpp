#include    "..\Inc\CLog.h"

CLog CLog::Log;

CLErro::CLErro(){
}

CLog::CLog(){
	Mutex = CreateMutex( 
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL
				);             			// unnamed mutex;
	if (Mutex == NULL) 
    {
        //ERROR;
	}
}

void CLog::display(){
	if (ConsoleIni){
		oss.clear();
		oss.str("");
		oss << buffer;
		SendMessageA(Console, EM_SETSEL, 0, -1);
		SendMessageA(Console, EM_SETSEL, -1, -1);
		SendMessageA(Console, EM_REPLACESEL, 0, (LPARAM)oss.str().c_str());
	}
}

void CLog::Add( const char* format, ... ){
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	display();
	vprintf (format, args);
	va_end (args);	
}

void CLog::OnInit(HWND _hwnd){
	FILE * File;
	char szPath[260];
	std::string Path;

//Open Log
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\PComS1701.ini";
	File = fopen (Path.c_str(), "rb");
	if (File==NULL) {
		printf("\n Arquivo de inicializacao nao pode ser aberto\n");
	}else{
		fread (&LogSave,sizeof(CLogSave),1,File);
	}
	fclose (File);
//-------------------------------------------------------------		
//Windows Position	
	RECT Windows,Result;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &Windows);
	hwnd = _hwnd;
	Result.left = LogSave.MainRc.left;
	Result.top = LogSave.MainRc.top;
	
	if ( LogSave.MainRc.left < Windows.left ){
		Result.left = Windows.left;
	}
	if ( (LogSave.MainRc.right) > (Windows.right) ){
		Result.left = Windows.right - (MAINW);
	}
	if ( LogSave.MainRc.top < Windows.top ){
		Result.top = Windows.top;
	}
	if ( (LogSave.MainRc.bottom) > (Windows.bottom) ){
		Result.top = Windows.bottom - (MAINH);
	}
	SetWindowPos(hwnd, 
				HWND_TOP, 
				Result.left, 
				Result.top, 
				0, 0,          // Ignores size arguments. 
				SWP_NOSIZE);
//-------------------------------------------------------------		

	SetFileName();
	Status = LOG_WARN;
}


void CLog::OnEnd(){
	FILE * File;
	char szPath[260];
	std::string Path;
//Window position	
	GetWindowRect(hwnd,&(LogSave.MainRc));
	
//Save Log	
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="SFiles\\PComS1701.ini";
	File = fopen (Path.c_str(), "wb");
	oss.clear();
	oss.str("");
	if (File==NULL) {
		CLog::Log.Add("\n Arquivo de inicializacao nao pode ser escrito\n");
	}else{
		fwrite (&LogSave,sizeof(CLogSave),1,File);
	}
	fclose (File);	
//-------------------------------------------------------------
}

bool CLog::FileOk(char *AxisType){
	if(strcmp(AxisType,"User")==0){
		if ( strcmp("",LogSave.C_User_File)!=0 ){
			FILE* FileHandle = fopen(LogSave.C_User_File,"r");
			if (FileHandle == NULL) {
				CLog::Log.Add("\nNao foi possivel encontrar:\r\n%s \r\n\r\n",LogSave.C_User_File);
				fclose (FileHandle);	
			}
			else{
				fclose (FileHandle);	
				return true;
			}
		}
	}
	if(strcmp(AxisType,"Config")==0){
		if ( strcmp("",LogSave.C_Config_File)!=0 ){
			FILE* FileHandle = fopen(LogSave.C_Config_File,"r");
			if (FileHandle == NULL) {
				CLog::Log.Add("\nNao foi possivel encontrar:\r\n%s \r\n\r\n",LogSave.C_Config_File);
				fclose (FileHandle);	
			}
			else{
				fclose (FileHandle);	
				return true;
			}
		}
	}
	return false;
}

char* CLog::GetCurrentFile(char *AxisType){
	if(strcmp(AxisType,"User")==0){
		return	LogSave.C_User_File;
	}
	if(strcmp(AxisType,"Config")==0){
		return	LogSave.C_Config_File;
	}
	return NULL;
}

void CLog::SetCurrentFile(const char* File,char *AxisType){
	if(strcmp(AxisType,"User")==0){
		LogSave.C_User_File[0]='\0';
		strcpy(LogSave.C_User_File,File);
	}
	if(strcmp(AxisType,"Config")==0){
		LogSave.C_Config_File[0]='\0';
		strcpy(LogSave.C_Config_File,File);
	}
	SetFileName();
}

void CLog::SetLogConsole(HWND hwnd){
	ConsoleIni = true;
	Console = hwnd;
}

void CLog::SetLogWarn(HWND hwnd){
	WarnIni = true;
	Warn = hwnd;
}

void CLog::SetBarComSStatus(HWND hwnd){
	HBarComSStatus = hwnd;
}

void CLog::SetBarLabel(HWND hwnd){
	HBarLabel = hwnd;
}

void CLog::SetStatusC(HWND hwnd){
	StatusC = hwnd;
}

void CLog::SetFileName(){
	std::string strEnd,str1,str2;
	if ( Log.FileOk("User") ) {
		str1 += LogSave.C_User_File;
		str1 += "  ";
		str1.erase(0,str1.find_last_of('\\')+1);	
	}
	else{
		str1 += "Novo.apf ";
	}
	if ( Log.FileOk("Config") ) {
		str2 += LogSave.C_Config_File;
		str2.erase(0,str2.find_last_of('\\')+1);	
		str2 += "  ";
	}
	else{
		str2 += "Novo.acf ";
	}
	strEnd += "Progama = " + str1 + "Configuracao = " + str2 + " - PCOMS1701";
	SetWindowText(hwnd, strEnd.c_str());
}

void CLog::InsertWarn(const char* Origem,int Cod,const char* Men){
	LVITEM lvI;
	std::string str;
	char thisbuffer[25];
	str =  Origem;
	lvI.pszText   = const_cast<char *>(str.c_str()); // Sends an LVN_GETDISPINFO message.
    lvI.mask      = LVIF_TEXT;
    lvI.iSubItem  = 0;
    lvI.state     = 0;
	
	lvI.iItem  	  = 0;
	//printf("fundo\n");
	ListView_InsertItem(Warn, &lvI);
	str =  itoa(Cod,thisbuffer,10);
	lvI.pszText   = const_cast<char *>(str.c_str());; // Sends an LVN_GETDISPINFO message.
	lvI.iItem  	  = 0;	
    lvI.iSubItem  = 1;
	SendMessage(Warn,LVM_SETITEM,(WPARAM)0,(LPARAM)&lvI);
	str = Men;
	lvI.pszText   = const_cast<char *>(str.c_str());; // Sends an LVN_GETDISPINFO message.
	lvI.iItem  	  = 0;	
    lvI.iSubItem  = 2;
	SendMessage(Warn,LVM_SETITEM,(WPARAM)0,(LPARAM)&lvI);
	
}

void CLog::DelLastWarn(){
	SendMessage(Warn,LVM_DELETEITEM,(WPARAM)0,(LPARAM)0);
}

void CLog::RemoveWarn(int Cod){
	SendMessage(Warn,LVM_DELETEITEM,(WPARAM)Cod,(LPARAM)0);
}


void CLog::DelAllWarn(){
	SendMessage(Warn,LVM_DELETEALLITEMS,(WPARAM)0,(LPARAM)0);
}
