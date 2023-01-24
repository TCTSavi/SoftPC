#include "..\PComS1701.h"

void OnEnd(){
	CLog::Log.OnEnd();
	PCtrl.EndAxis();
	DMan::DM.OnEnd();
}