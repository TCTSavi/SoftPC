#ifndef _CPCI_H_
#define _CPCI_H_

#include <windows.h>
#include <commctrl.h>
#include <Vector>
#include <stdio.h>

#include "CPCtrl.h"
#include "CPEixo.h"
#include "CPEPage.h"
#include "CPMenu.h"
#include "CPPar.h"
#include "CPMOpc.h"
#include "CLog.h"

#define TABCTRL	1000

class CPCI {
	public:
		HWND hwnd;
		HWND HTab;
		int TabID;
		TCITEM tie;
		CPEixo* EixoC;
		CPEPage* PagC;
		int giveTabID();
		HFONT HF_BigButton,HF_TSTVERFont;
		std::vector<HWND> UpAnHWNDList;	//Lista de hwnd para atualizar(Animar)
	public:
		CPCI();
		void Load(HWND _hwnd);
		void MButton(CPPar* Par,int x,int y,int w,int h);
		void MComBufSendBar(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh);
		void MComBufSendBarC(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh);
		void MTVerif(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh);
		void MButOp(CPPar* Par,int x,int y,int w,int h);
		void MLogC(CPPar* Par,int x,int y,int w,int h);
		void MListViewC(CPPar* Par,int x,int y,int w,int h);
		void MScrollBarC(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh);
		void MButtonC(CPPar* Par,int x,int y,int w,int h);
		void MButtonCMachineStatus (CPPar* Par,int x,int y,int w,int h);
		void MLabelC(CPPar* Par,int x,int y,int w,int h);
		void MLabel(CPPar* Par,int x,int y,int w,int h);
		void MLCombobox(CPPar* Par,int x,int y,int lw,int lh,int cw,int ch);
		void MLEdit(CPPar* Par,int x,int y,int lw,int lh,int ew,int eh); 
		void MStatusC(CPPar* Par,int x,int y,int w,int h);
		void MBit(CPPar* Par,int x,int y,int w,int h);
		void MMenu(CPMenu* Menu,int x,int y);
		void MEixo(CPEixo* Eixo,CPEPage* Pag,int x,int y);
		void MCtrl(CPCtrl* Ctrl,int x,int y ,int w,int h);
		void ShowCtrl(CPEPage* Pag);
		void UShowCtrl(CPEPage* Pag);
		void MMain(CPCtrl* Ctrl);
		CPPar& SetPar(CPPar* Par);

	public:
		void Draw(DRAWITEMSTRUCT dis);
};

#endif