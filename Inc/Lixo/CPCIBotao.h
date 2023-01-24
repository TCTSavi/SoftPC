#ifndef _CCONTROL_H_
#define _CCONTROL_H_

#include <windows.h>
#include <commctrl.h>
#include <Vector>
#include <stdio.h>

#include "CPEixo.h"
#include "CPMenu.h"
#include "CPPar.h"
#include "CPMOpc.h"
#include "CLog.h"

class CPCIBotao {
	public:
		HWND hwnd;
		int x,y,w,h;
	public:
		CPCIBotao(HWND _hwnd);
		void SetPlace()
		int getSizeW();
		int getSizeH();
		int getSizeX();
		int getSizeY();
		void Show(bool );
		void Draw();
};	


class CPCIMenu {
	public:
		HWND hwnd;
		int x,y,w,h;
	public:
		CPCIMenu(HWND _hwnd);
        std::vector<CPCI> CPCIList;
		void SetPlace()
		int getSizeW();
		int getSizeH();
		int getSizeX();
		int getSizeY();
		void Show(bool );
		void Draw();
};	

class CPCIEixo {
	public:
		HWND hwnd;
		int x,y,w,h;
	public:
		CPCIEixo(HWND _hwnd);
        std::vector<CPCI> CPCIList;
		void SetPlace()
		int getSizeW();
		int getSizeH();
		int getSizeX();
		int getSizeY();
		void Show(bool );
		void Draw();
};	