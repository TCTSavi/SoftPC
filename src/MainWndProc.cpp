#include "..\PComS1701.h"


#ifdef _UNICODE
wostringstream oss2;
#else
ostringstream oss2;
#endif

bool Enviando = false;
unsigned char *Lido;
int XMouseMain,YMouseMain;

HWND LM1,LM2,LM3,BM1;
HBRUSH hColorBrush = 0;
DWORD count = 0;
LRESULT lRet = 0; 				 	// return value for our WindowProc.
//Main Proc
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	short int PCI_ID;
	short int PCI_CMD;
	switch (uMsg){
		case WM_CREATE:{
			MMenus(hwnd);	//Cria os menus
		}
		return 0;
		/*
		case WM_TIMER:{
			switch (wParam){
				case IDT_TIMER1:{
					PCtrl.ReceiveAll();
					PCtrl.RefreshAllIn();
				}
				break;
				default:{
				}
				break;
			}
		}
		return 0;
		*/
		/*
		case WM_ERASEBKGND:{
			
		}
		return true;
		*/
		/*
		case WM_PAINT:{
			system("pause");
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
			system("pause");

			//FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 204, 0)));
			EndPaint(hwnd, &ps);
			system("pause");
			
		}
		return 0;
		*/
		case WM_DRAWITEM:{
			DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT*)lParam;
			PCI_ID = (int)GetMenu(dis->hwndItem);
			CPPar *Par = PCtrl.getPar((int)PCI_ID);
			if (Par == NULL){/*Deu Ruim*/}
			Par->ExpPar->Draw(dis);
			/*
			DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT*)lParam;
			TCITEM tie;
			char NEixo[50];
			tie.mask = TCIF_TEXT;
			tie.pszText = NEixo;
			tie.cchTextMax = sizeof(NEixo) * sizeof(char);
			TabCtrl_GetItem(dis->hwndItem, dis->itemID, &tie);
			RECT rttemp;
			FillRect(dis->hDC,&dis->rcItem,HB_Normal);
			rttemp = dis->rcItem;
			rttemp.bottom -=19;  
			FillRect(dis->hDC,&rttemp,HB_Red);
			SetTextColor(dis->hDC, RGB(0,0,0));
			SetBkMode(dis->hDC, TRANSPARENT);
			//DrawCaption(  dis->hwndItem,  dis->hDC,  &dis->rcItem,  DC_SMALLCAP);
			//DrawEdge( dis->hDC, &dis->rcItem,(dis->itemState & ODS_SELECTED ? EDGE_BUMP : EDGE_ETCHED ),BF_MONO);
			DrawEdge( dis->hDC, &dis->rcItem,(dis->itemState & ODS_SELECTED ? EDGE_RAISED : EDGE_RAISED ),0);
			DrawText( dis->hDC,tie.pszText,_tcslen(tie.pszText),  &dis->rcItem,  DT_VCENTER|DT_SINGLELINE|DT_CENTER);//Preenche o Texto
			*/
			
			/*
			DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT*)lParam;
			RECT rc,rc2;
			LPCWSTR rcContent;
			TCHAR szButtonText[255];
			HRESULT hr;
			size_t cch;
			HTHEME hTheme = NULL;
			hTheme = OpenThemeData(dis->hwndItem, L"Button");
			int iState = dis->itemState ;
		
			GetWindowRect(dis->hwndItem, &rc);
			GetWindowText(dis->hwndItem, szButtonText,(sizeof(szButtonText) / sizeof(szButtonText[0])+1));
			DrawThemeBackground(hTheme, dis->hDC, 2, iState, &dis->rcItem, 0);
			DrawThemeText(hTheme, dis->hDC, 1, iState,L"Texto", cch,DT_CENTER | DT_VCENTER | DT_SINGLELINE,0, &dis->rcItem);
			*/
			
			/*
			hr = StringCchLength(szButtonText,(sizeof(szButtonText) / sizeof(szButtonText[0])), &cch);
			
			if (SUCCEEDED(hr)){
				hr = GetThemeBackgroundContentRect(hTheme, dis->hDC, 1,iState, &rc, &rc2);
			}
		
			if (SUCCEEDED(hr)){
				hr = DrawThemeText(hTheme, dis->hDC, 1, iState,L"Texto", cch,DT_CENTER | DT_VCENTER | DT_SINGLELINE,0, &rc2);
				//DrawThemeText     (theme  ,hdc     ,TVP_TREEITEM,TREIS_NORMAL,L"Ala ma kota",11,DT_VCENTER | DT_LEFT,0,&rect);
			}
			*/

			
			/*
			RECT rttemp;
			DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT*)lParam;
			rttemp = dis->rcItem;
			rttemp.left +=2;  
			rttemp.top +=2;
			rttemp.bottom -=2;  
			rttemp.right -=2;			
			if ( MainTimer01.GetBotState() ){
				FillRect (dis->hDC,&dis->rcItem,HB_Yellow);//Preenche o fundo do retangulo
				FillRect (dis->hDC,&rttemp,HB_Red);//Preenche o fundo do retangulo
				SetBkColor(dis->hDC, RGB(255, 0, 0));								//Preenche o fundo do texto
			}
			else{
				FillRect (dis->hDC,&dis->rcItem,HB_Yellow);//Preenche o fundo do retangulo
				FillRect (dis->hDC,&rttemp,HB_Normal);//Preenche o fundo do retangulo
				SetBkColor(dis->hDC, RGB(240,240,240));								//Preenche o fundo do texto

			}
			
			char Texto[128];													//Captura o texto
			std::string str;													//
			GetWindowText(dis->hwndItem,Texto,128);								//
			str+= Texto;														//
			SetTextColor(dis->hDC,RGB(0,0,0));									//Define a cor do Texto
			RECT rtmove;
			rtmove = dis->rcItem;
			rtmove.left -=5;  
			rtmove.top -=5;
			
			int numero = 0;
			
			DrawEdge(dis->hDC, &dis->rcItem,(dis->itemState & ODS_SELECTED ? EDGE_BUMP : EDGE_ETCHED ), 0);
			//DrawEdge(dis->hDC, &dis->rcItem,(dis->itemState & EDGE_RAISED ? EDGE_SUNKEN : EDGE_ETCHED ), BF_RECT);
			DrawText( dis->hDC,str.c_str(),str.size(),(dis->itemState & ODS_SELECTED ? (&dis->rcItem) : (&rtmove) ),  DT_VCENTER|DT_SINGLELINE|DT_CENTER);//Preenche o Texto
			//DrawText( dis->hDC,str.c_str(),str.size(),  &dis->rcItem,  DT_VCENTER|DT_SINGLELINE|DT_CENTER);//Preenche o Texto
			//DrawEdge(  dis->hDC,   &dis->rcItem, EDGE_ETCHED,  BF_MONO|BF_RECT );		//Desenha o botão não pressionado
			//DrawEdge(  dis->hDC,   &dis->rcItem, EDGE_SUNKEN,   BF_ADJUST);		//Desenha o botão pressionado
			RECT rtfocus;
			rtfocus = dis->rcItem;
			rtfocus.left +=10;  
			rtfocus.top +=10;
			rtfocus.bottom -=10;  
			rtfocus.right -=10;
			if ( dis->itemState & ODS_FOCUS ) DrawFocusRect( dis->hDC, &rtfocus);							//Desenha o retangulo de foco
			*/
		}
		return 0;
		case WM_COMMAND:{
			if (!Initializing){
				//por enquanto filtrando as codigos dos edit´s
				PCI_ID = wParam & 0x0000FFFF;
				PCI_CMD= ((wParam>>16) & 0x0000FFFF);
				CPPar *Par = PCtrl.getPar((int)PCI_ID);
				if ( Par == NULL ){printf("Item de interface:%d\n",PCI_ID);}
				switch(PCI_ID){
					//Essa é a faixa de tratamento padrões Posijet
					case 10000 ... 15000:{
						switch(Par->getTipo()){
							case PCIBUTOP:
							case PCIBUTTON:{
								PCtrl.SendToAxis(Par);
								HWND cl_hwnd = (HWND)GetFocus();
								//printf("%d :Button(Index:%d):Nao implementado\n",count,PCI_ID);
								//printf("%d :Comando:%04x \n\n",count,PCI_CMD);
							}
							break;
							case PCILEDIT:
							case PCILEDITL:
							case PCILEDITH:{
								switch(PCI_CMD){
									case EN_CHANGE:{
										Par->Color = WARNCOLOR;
										HWND cl_hwnd = (HWND)lParam; 
										InvalidateRect(cl_hwnd, NULL, NULL);
									}
									break;
									default:
									break;
								}
							}
							break;
							case PCITVBIT:
							case PCITVBYTE:{								
								switch(PCI_CMD){
									case EN_SETFOCUS:{
										PCtrl.SetTVByteToBit(Par);
									}
									break;
									case EN_CHANGE:{
										HWND hwndFocus;
										HWND cl_hwnd = (HWND)lParam; 
										hwndFocus = GetFocus();
										//if ( cl_hwnd != hwndFocus ){
										//}
										//else{
										//	Par->Color = WARNCOLOR;
										//}
										InvalidateRect(cl_hwnd, NULL, NULL);
									}
									break;
									default:
									break;
								}
							}
							break;
							case PCISTATUSC:{
								HWND cl_hwnd = (HWND)lParam; 
								InvalidateRect(cl_hwnd, NULL, NULL);
							}
							break;
							case PCILCOMBOBOX:{
								switch(PCI_CMD){
									case 1:{
										Par->Color = WARNCOLOR;
										HWND cl_hwnd = (HWND)lParam; 
										InvalidateRect(cl_hwnd, NULL, NULL);
									}
									break;
									default:
									break;
								}
							}
							break;
							case PCIBUTTONCMACHINESTATUS:
							case PCIBUTTONC:{
								if ( strcmp(Par->Nome,"Iniciar")==0){
								}
								if ( strcmp(Par->Nome,"Parar")==0){
								}
								if ( strcmp(Par->Nome,"Pausar")==0){
								}
								if ( strcmp(Par->Nome,"Manual")==0){
								}
								CPMPar* MPar = PCtrl.PMainList[0].getMPar(Par->getValor());
								
								for (int i=0;i<MPar->CParList.size();i++){
									if ( ( MPar->CParList[i].NPage == 0) && (strcmp (MPar->CParList[i].Menu,"0x00")==0) ){
										switch( PCtrl.GetCommand(MPar->CParList[i].Par) ){
											case CMD_SALVAUSER:{
												//CLog::Log.Add("SALVAUSER\r\n");
												Save(hwnd,"User","All\0*.*\0Posijet\0*.apf\0");
											}
											break;
											case CMD_SALVACONFIG:{
												//CLog::Log.Add("SALVACONFIG\r\n");
												Save(hwnd,"Config","All\0*.*\0Posijet\0*.acf\0");												
											}
											break;
											case CMD_SENDALL:{
												PCtrl.CommAll();
											}
											break;
											default:{
												CLog::Log.Add("Comando interno invalido:%s\r\n",MPar->CParList[i].Par);
											}
											break;
										}
									}
									else{
										if ( ( MPar->CParList[i].NPage == 0) && (strcmp (MPar->CParList[i].Menu,"PROGRAM")==0) ){
											
											char szPath[260];
											std::string Path;
											GetModuleFileName(NULL, szPath,260 );
											Path = szPath;
											Path.erase(Path.find_last_of('\\')+1);	
											STARTUPINFOA si;
											PROCESS_INFORMATION pi;
											// set the size of the structures
											ZeroMemory(&si, sizeof(si));
											si.cb = sizeof(si);
											ZeroMemory(&pi, sizeof(pi));
											Path+='\\';
											Path+=MPar->CParList[i].Par;
											//system(Path.c_str());
											CreateProcessA(
											Path.c_str(),
											NULL,
											NULL,
											NULL,
											false,
											CREATE_NEW_CONSOLE,
											NULL,
											NULL,
											&si,
											&pi
											);
											
										}
										else{
											CPPar *ParN	= PCtrl.getPar(MPar->CParList[i].NPage,MPar->CParList[i].Menu,MPar->CParList[i].Par);
											if ( ParN == NULL){
												CLog::Log.Add("Menu: %s invalido,Linha:%d de:%d\r\n",MPar->Valor,i,MPar->CParList.size());
											}
											else{
												PCtrl.SendToAxis(ParN);
											}
										}											
									}
								}
								printf("%d :ButtonC:(Index:%d)\n",count,PCI_ID);
								printf("%d :Comando:%04x \n\n",count,PCI_CMD);
							}
							break;
							case PCILISTVIEWC:{
								char tmp[50];
								GetWindowText(GetFocus(),tmp,50);
								if(strcmp("Limpar ultimo",tmp)==0){
									PCtrl.DelLastWarn();
									//CLog::Log.DelLastWarn();
								}
								if(strcmp("Limpar todos",tmp)==0){
									PCtrl.DelAllWarn();
									//CLog::Log.DelAllWarn();
								}
								printf("%d :ListViewC:(Index:%d):Nao implementado\n",count,PCI_ID);
								printf("%s\n",tmp);
								printf("%d :Comando:%04x \n\n",count,PCI_CMD);														
							}
							break;
							case PCITESTEVERIFICACAO:{
							}
							break;
							default:{
								printf("%d :Sem funcao(Index:%d):Nao implementado\n",count,PCI_ID);
								printf("%d :Comando:%04x \n\n",count,PCI_CMD);
							}
							break;
						}
					}
					break;
					//Enter Press
					case 0x1:{
						PCI_ID = (int)GetMenu(GetFocus());
						Par = PCtrl.getPar((int)PCI_ID);	
						if ( Par == NULL ){printf("Nao recebe enter:%d\n",PCI_ID);}
						else{
							switch(Par->getTipo()){
								case PCILEDIT:
								case PCILEDITL:
								case PCILEDITH:
								case PCILCOMBOBOX:{
									PCtrl.SetHWNDToPar(Par);
									PCtrl.SendToAxis(Par);
									HWND cl_hwnd = (HWND)GetFocus();
									InvalidateRect(cl_hwnd, NULL, NULL);
								}
								break;
								case PCITVBIT:
								case PCITVBYTE:	
								case PCITESTEVERIFICACAO:{
									PCtrl.SetHWNDToPar(Par);
									PCtrl.SendToAxis(Par);
									SetFocus(MainWindow);
								}
								break;
								default:{
									printf("%d :Sem funcao(Index:%d):Nao implementado\n",count,PCI_ID);
								}
								break;
							}
							count++;
						}
					}
					break;
					case IDM_ARQUIVO_NOVO_APF:{
						NewFile(hwnd,"User");
					}
					break;
					case IDM_ARQUIVO_NOVO_ACF:{
						int Result;
						Result = MessageBox(
							NULL,
							(LPCSTR)"     Tem certeza que deseja criar nova configuracao?\n \n \"Configuracoes definem a mecanica do equipamento\"",
							(LPCSTR)"Configuracao",
							MB_YESNO | MB_ICONQUESTION
						);
						if (Result == IDYES){
							NewFile(hwnd,"Config");
						}
					}
					break;
					case IDM_ARQUIVO_ABRIR_APF:{
						OpenFile(hwnd,"User","All\0*.*\0Posijet\0*.apf\0");
					}
					break;
					case IDM_ARQUIVO_ABRIR_ACF:{
						int Result;
						Result = MessageBox(
							NULL,
							(LPCSTR)"     Tem certeza que deseja abrir outra configuracao?\n \n \"Configuracoes definem a mecanica do equipamento\"",
							(LPCSTR)"Configuracao",
							MB_YESNO | MB_ICONQUESTION
						);
						if (Result == IDYES){
							OpenFile(hwnd,"Config","All\0*.*\0Posijet\0*.acf\0");
						}
					}
					break;
					case IDM_ARQUIVO_SALVAR_APF:{
						Save(hwnd,"User","All\0*.*\0Posijet\0*.apf\0");
					}
					break;
					case IDM_ARQUIVO_SALVAR_ACF:{
						Save(hwnd,"Config","All\0*.*\0Posijet\0*.acf\0");
					}
					break;
					case IDM_ARQUIVO_SALVARCOMO_APF:{
						SaveAs(hwnd,"User","All\0*.*\0Posijet\0*.apf\0");
					}
					break;
					case IDM_ARQUIVO_SALVARCOMO_ACF:{
						SaveAs(hwnd,"Config","All\0*.*\0Posijet\0*.acf\0");
					}
					break;
					case IDM_ARQUIVO_SAIR:{
						PostQuitMessage(0);
					}
					break;				
					case IDM_TESTE:{
						Teste(hwnd);
					}
					break;
					default:{
						printf("%d : Index menu:%d comando:%x \n",count,PCI_ID,PCI_CMD);
					}
					break;
				}
				
			}
		}
		return 0;
		case WM_HSCROLL:{
			SCROLLINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cbSize = sizeof(si);
			HWND cl_hwnd = (HWND)lParam; 
			switch(LOWORD(wParam)) {
				case SB_THUMBTRACK:
					// Initialize SCROLLINFO structure
					// Call GetScrollInfo to get current tracking 
					//    position in si.nTrackPos
					//printf("Posicao:%x\n",lParam);
					si.fMask = SIF_TRACKPOS;
					if (!GetScrollInfo(cl_hwnd, SB_CTL, &si) ){
						break;
					}
					printf("Track:%d\n",si.nTrackPos);
				break;
				case SB_THUMBPOSITION:{
					//si.fMask = SIF_TRACKPOS;
					//si.nPos = HIWORD(wParam);
					printf("Pos:%d\n",HIWORD(wParam));
					SetScrollPos(cl_hwnd,SB_CTL,HIWORD(wParam),TRUE);
					//SetScrollInfo(cl_hwnd,SB_CTL,&si,TRUE);					
				}
				break;
			}
			
		}
		return 0;
		//WM_CTLCOLORMSGBOX (0x0132)
		//WM_CTLCOLOREDIT (0x0133)
		//WM_CTLCOLORLISTBOX (0x0134)
		//WM_CTLCOLORBTN (0x0135)
		//WM_CTLCOLORDLG (0x0136)
		//WM_CTLCOLORSCROLLBAR (0x0137)
		//WM_CTLCOLORSTATIC (0x0138)
		case WM_CTLCOLORSTATIC:{
			HDC hdc = (HDC)wParam;
			HWND cl_hwnd = (HWND)lParam; 
			PCI_ID = GetDlgCtrlID(cl_hwnd);
			COLORREF crBk = RGB(0,0,0);
			CPPar *Par = PCtrl.getPar((int)PCI_ID);
			if ( Par == NULL ){/*printf("Nao trabalha cor:%d\n",PCI_ID);*/}
			else{
				switch(Par->getTipo()){
					case PCISTATUSC:{
						switch(PCtrl.GetStatus()){
							case LOG_OK:{
								SetWindowText(CLog::Log.StatusC,"Pronto.");
								crBk = RGB(70,255,70);
							}
							break;
							case LOG_WAIT:{
								SetWindowText(CLog::Log.StatusC,"Aguarde carregando...");
								crBk = RGB(255,215,0);
							}
							break;
							case LOG_ERROR:{
								SetWindowText(CLog::Log.StatusC,"Erro:Verifique painel de avisos!");
								crBk = RGB(255,70,70);
							}
							break;
							case LOG_WARN:{
								SetWindowText(CLog::Log.StatusC,"Erro:Verifique painel de avisos!");
								crBk = RGB(255,100,40);
							}
							break;
							default:{
							}
							break;
						}
						SetDCBrushColor(hdc,crBk);
						SetBkColor(hdc, crBk); // Set to red
						lRet = (LRESULT) GetStockObject(DC_BRUSH); // return a DC brush.	
						return lRet;
					}
					default:{
						return DefWindowProc(hwnd, uMsg, wParam, lParam);
					}
					break;
				}				
			}				
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		/*
		case WM_CTLCOLORSTATIC:{
			HWND cl_hwnd = (HWND)lParam; 
			PCI_ID = GetDlgCtrlID(cl_hwnd);
			CPPar *Par = PCtrl.getPar((int)PCI_ID);
			HWND hwnd_backup = hwnd;
			UINT uMsg_backup = uMsg;
			WPARAM wParam_backup = wParam;
			LPARAM lParam_backup = lParam;
			return DefWindowProc(hwnd_backup, uMsg_backup, wParam_backup, lParam_backup);
			switch(Par->getTipo()){
				case PCICOMBUFSENDBAR:{
					printf("Desenha:%s\n",Par->Nome);
				}
				break;
				default:{
					return DefWindowProc(hwnd_backup, uMsg_backup, wParam_backup, lParam_backup);		
				}
				break;
			}
		}
		return 0;
		*/
		case WM_CTLCOLOREDIT:{
			HDC hdc = (HDC)wParam;
			COLORREF crBk;
			HWND cl_hwnd = (HWND)lParam; 
			PCI_ID = GetDlgCtrlID(cl_hwnd);
			CPPar *Par = PCtrl.getPar((int)PCI_ID);
			if ( Par == NULL ){/*printf("Nao trabalha cor:%d\n",PCI_ID);*/}
			else{
				switch(Par->Color){
					case WHITECOLOR:{
						crBk = RGB(0,0,255);
					}
					break;
					case WARNCOLOR:{
						crBk = RGB(255,215,0);
					}
					break;
					case OKCOLOR:{
						crBk = RGB(255,255,255);
					}
					break;
					case WRONGCOLOR:{
						crBk = RGB(255,0,0);
					}
					break;
					case GREYCOLOR:{
						crBk = RGB(128,128,128);
					}
					case TESTVERCOLOR:{
						crBk = RGB(0,191,255);
						//crBk = RGB(255,215,0);
					}
					break;
					default:{
						crBk = RGB(255,255,255);
					}
					break;
				}
				switch(Par->getTipo()){
					case PCILCOMBOBOX:
					case PCILEDITH:
					case PCILEDITL:
					case PCITVBIT:
					case PCITVBYTE:
					case PCILEDIT:{
						SetBkColor(hdc, crBk); // Set to red
						SetDCBrushColor(hdc, crBk);
						SetBkMode( hdc, TRANSPARENT );
						lRet = (LRESULT) GetStockObject(DC_BRUSH); // return a DC brush.	
						//printf("Color:%d\n",Par->Color);
					}
					break;
					case PCISTATUSC:{
						crBk = RGB(255,215,0);
						//crBk = RGB(0,255,0);
						SetBkColor(hdc, crBk); // Set to red
						SetDCBrushColor(hdc, crBk);
						SetBkMode( hdc, TRANSPARENT );
						lRet = (LRESULT) GetStockObject(DC_BRUSH); // return a DC brush.	
					}
					case PCITESTEVERIFICACAO:{
					}
					break;
					default:{
						printf("%d :Sem funcao(Index:%d):Nao implementado\n",count,PCI_ID);
					}
					break;
				}
				count++;
			}					
		}
		return lRet;
		case WM_NOTIFY:{
			switch (((LPNMHDR)lParam)->code){
				case TCN_SELCHANGING:{
					PCI.UShowCtrl(PCtrl.GivePage(TabCtrl_GetCurSel(PCI.HTab)));
					PCtrl.ClearCommPage();
				}
				break;
				case TCN_SELCHANGE:{
					CPEPage* Page = PCtrl.GivePage(TabCtrl_GetCurSel(PCI.HTab));
					PCI.ShowCtrl(Page);
					PCtrl.SetCommPage(Page);
				} 
				break;
				default:{
				}
				break;
			}
			count++;
		}
		return 0;
		//Para animações
		case WM_APP+0:{
			/*
			for(int i=0;i<PCI.UpAnHWNDList.size();i++){
				PCI_ID = (int)GetMenu(PCI.UpAnHWNDList[i]);
				CPPar *Par = PCtrl.getPar((int)PCI_ID);
				if (Par == NULL){}
				Par->ExpPar->Draw(hwnd,PCI.UpAnHWNDList[i],MainTimer01.GetBotState());
			}
			UpdateWindow(hwnd);
			*/
		}
		return 0;
		//Atualiza Log;
		case WM_APP+1:{
			CPErro *Erro = (CPErro*)wParam;
			std::string Men;
			Men += Erro->Men;
			Men += " ";
			Men += Erro->Comments;
			CLog::Log.InsertWarn(Erro->Origem,Erro->Cod,Men.c_str());
		}
		return 0;		
		case WM_APP+2:{
			CPEixo *Eixo = (CPEixo*)wParam;
			std::string str;
			char thisbuffer[25];
			str += itoa(Eixo->Buffer,thisbuffer,10);
			str += " / ";
			str += itoa(Eixo->Send,thisbuffer,10);
			SetWindowText(Eixo->HBarLabel,str.c_str());
			int Send = Eixo->Send * 100;
			int Buffer = Eixo->Buffer;
			int Bar = 0;
			if (Buffer == 0){
				Bar = 100;
			}
			else{
				Bar = Send/Buffer;
			}
			SetWindowText(Eixo->HBarLabel,str.c_str());
			SendMessage(Eixo->HBarComSStatus,PBM_SETPOS,(WPARAM)Bar,(LPARAM)0);
			UpdateWindow(Eixo->HBarLabel);
		}
		return 0;		
		case WM_APP+3:{
			std::string str;
			char thisbuffer[25];
			str += itoa(PCtrl.Buffer,thisbuffer,10);
			str += " / ";
			str += itoa(PCtrl.Send,thisbuffer,10);
			SetWindowText(CLog::Log.HBarLabel,str.c_str());
			int Send_ = PCtrl.Send * 100;
			int Buffer_ = PCtrl.Buffer;
			int Bar = 0;
			if (Buffer_ == 0){
				Bar = 100;
			}
			else{
				Bar = Send_/Buffer_;
			}
			SetWindowText(CLog::Log.HBarLabel,str.c_str());
			SendMessage(CLog::Log.HBarComSStatus,PBM_SETPOS,(WPARAM)Bar,(LPARAM)0);
			UpdateWindow(CLog::Log.HBarLabel);
		}
		return 0;
		//Atualiza Status
		case WM_APP+4:{	
			//printf("Aqui@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			//switch(PCtrl.GetStatus()){
			//	case LOG_OK:{
			//		PCtrl.ResetError();
			//	}
			//	break;
			//	case LOG_WAIT:{
			//		//PCtrl.SetError();
			//	}
			//	break;
			//	case LOG_ERROR:{
			//		PCtrl.SetError();
			//	}
			//	break;
			//	case LOG_WARN:{
			//		//PCtrl.SetError();
			//	}
			//	break;
			//	default:{
			//	}
			//	break;
			//}
			InvalidateRect(CLog::Log.StatusC, NULL, NULL);
		}
		return 0;
		case WM_APP+5:{	
			CPPar *Par = (CPPar*)wParam;
			PCtrl.SetParToHWND(Par);
		}
		return 0;
		//Configura CommPage
		case WM_APP+6:{	
			PCtrl.ClearCommPage();
			CPEPage* Page = PCtrl.GivePage(TabCtrl_GetCurSel(PCI.HTab));
			PCI.ShowCtrl(Page);
			PCtrl.SetCommPage(Page);
		}
		return 0;
		case WM_CLOSE:{
			OnEnd();
			//printf("Finalizou\n");
			PostQuitMessage(0);
		}
		case WM_DESTROY:
			//PostQuitMessage(0);
		return 0;
		case 0x400:{
		}
		return 0;
	}
	PCI_ID = wParam & 0x0000FFFF;
	PCI_CMD= ((wParam>>16) & 0x0000FFFF);
	//printf("%d : Mensagem uMsg->%X ,Index menu:%d ,comando:%x\n\n",count,uMsg,PCI_ID,PCI_CMD);
	count++;
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//------------------------------------------------------------------------------
//Proc Monitor
FILE* FileHandle;
char temp=0;

LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
switch (uMsg){
	case WM_CREATE:{
		BM1 = CreateWindow( 
			WC_BUTTON,				// name of window class 
			"Avanca",			// title-bar string 
			WS_CHILD | WS_VISIBLE, 	// top-level window 
			10,10,75,25,			// x,y,w,h
			hwnd,			// no owner window 
			(HMENU)1,					// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL					// no window-creation data 
		);
		LM1 = CreateWindow( 
			WC_STATIC,				// name of window class 
			"",			// title-bar string 
			WS_CHILD | WS_VISIBLE, 	// top-level window 
			10,25+20,100,25,			// x,y,w,h
			hwnd,			// no owner window 
			NULL,					// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL					// no window-creation data 
		);
		LM2 = CreateWindow( 
			WC_STATIC,				// name of window class 
			"Mouse:(X,Y)",			// title-bar string 
			WS_CHILD | WS_VISIBLE, 	// top-level window 
			10,25+20+30,200,25,			// x,y,w,h
			hwnd,			// no owner window 
			NULL,					// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL					// no window-creation data 
		);
		LM3 = CreateWindow( 
			WC_STATIC,				// name of window class 
			"Leitura",			// title-bar string 
			WS_CHILD | WS_VISIBLE, 	// top-level window 
			10,25+20+55,200,25,			// x,y,w,h
			hwnd,			// no owner window 
			NULL,					// use class menu 
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL					// no window-creation data 
		);
		
		
	}
	return 0;
	case WM_COMMAND:{
		switch(wParam){
			case 1:{
			}
			default:{
			}
			break;
		}
	}
    return 0;
	case WM_CLOSE:{
		printf("Aqui passou\n");
		DestroyWindow(hwnd);
	}
	return 0;
	case WM_DESTROY:{
		CloseHandle(hMonitor);
		PostQuitMessage(0);
	}
    return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

long int Ponteiro,PonteiroOld;
int oldXMouseMain,oldYMouseMain;
//Thread Monitor
DWORD WINAPI fMonitor(){
	while (true){
//Mouse
		if ((XMouseMain != oldXMouseMain)|(YMouseMain != oldYMouseMain)){
			oss2.str("");
			oss2.clear();
			oss2 << "Mouse:( ";
			oss2 << XMouseMain;
			oss2 << " , ";
			oss2 << YMouseMain;
			oss2 << " )";
			SetWindowText(LM2, oss2.str().c_str() );
			oldXMouseMain = XMouseMain;
			oldYMouseMain = YMouseMain;
		}
	}
}

void MMenus(HWND hwnd) {
	HMENU hMenubar,hMenuFile,hMenuConfig,hMenuManager;
	hMenubar = CreateMenu();
	hMenuFile = CreateMenu();
	hMenuManager = CreateMenu();
	hMenuConfig = CreateMenu();
		

	AppendMenu(hMenuFile, MF_STRING, IDM_ARQUIVO_NOVO_APF, "Novo");
	AppendMenu(hMenuFile, MF_STRING, IDM_ARQUIVO_ABRIR_APF, "Abrir...");
	AppendMenu(hMenuFile, MF_STRING, IDM_ARQUIVO_SALVAR_APF, "Salvar...");
	AppendMenu(hMenuFile, MF_STRING, IDM_ARQUIVO_SALVARCOMO_APF, "Salvar como...");
	AppendMenu(hMenuFile, MF_SEPARATOR, 0, NULL);	
	AppendMenu(hMenuFile, MF_STRING, IDM_ARQUIVO_SAIR, "Sair");
	
	AppendMenu(hMenuConfig, MF_GRAYED, 0, "");
	AppendMenu(hMenuConfig, MF_SEPARATOR, 0, NULL);	
	AppendMenu(hMenuConfig, MF_STRING, IDM_ARQUIVO_NOVO_ACF, "Novo");
	AppendMenu(hMenuConfig, MF_STRING, IDM_ARQUIVO_ABRIR_ACF, "Abrir...");
	AppendMenu(hMenuConfig, MF_STRING, IDM_ARQUIVO_SALVAR_ACF, "Salvar...");
	AppendMenu(hMenuConfig, MF_STRING, IDM_ARQUIVO_SALVARCOMO_ACF, "Salvar como...");
	//ModifyMenu(hMenuConfig,IDM_ARQUIVO_NOVO_ACF, MF_ENABLED, IDM_ARQUIVO_NOVO_ACF, "Novo");
	
	
//	CPMPar* MPar = PCtrl.PMainList[0].getMPar(Par->getValor());
	
//	if 
	
	AppendMenu(hMenuManager, MF_POPUP, (UINT_PTR)hMenuConfig, "Configuracao");
	
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenuFile, "Arquivo");	
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenuManager, "Gerenciamento");	
	SetMenu(hwnd, hMenubar);
}

void OpenFile(HWND hwnd,char* AxisType,char *Filter){
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HANDLE hf;              // file handle
	
    char szPath[260];
	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="EFiles";
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = Filter;
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = Path.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	// Display the Open dialog box. 
	if (GetOpenFileName(&ofn)==TRUE) {
		if (PCtrl.Load_AxisFile(ofn.lpstrFile,AxisType)){
			PCtrl.SetAParToHWND();
			CLog::Log.SetCurrentFile(ofn.lpstrFile,AxisType);
			InvalidateRect(hwnd, NULL, NULL);
			PCtrl.CommAll();//Envia todos parametros para as placas
		}
	}
	//Salva qual foi o arquivo aberto por ultimo.
	CLog::Log.OnEnd();
}

void Save(HWND hwnd,char* AxisType,char *Filter){
	if (CLog::Log.FileOk(AxisType)){
		PCtrl.SetAHWNDToPar();
		//PCtrl.CommAll();//Envia todos parametros para as placas
		PCtrl.Save_AxisFile(CLog::Log.GetCurrentFile(AxisType),AxisType);
		InvalidateRect(hwnd, NULL, NULL);
	}
	else {
		SaveAs(hwnd,AxisType,Filter);
	}
}

void SaveAs(HWND hwnd,char* AxisType,char *Filter){
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HANDLE hf;              // file handle
	
    char szPath[260];
	std::string Path;
	GetModuleFileName(NULL, szPath,260 );
	Path = szPath;
	Path.erase(Path.find_last_of('\\')+1);	
	Path+="EFiles";
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = Filter;
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = Path.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	/*
	TCHAR szFolder[MAX_PATH] = _T("c:\\temp");
	dlg.m_ofn.lpstrInitialDir = szFolder;
	*/
	// Display the Open dialog box. 
	if (GetSaveFileName(&ofn)==TRUE) {
		std::string str;
		str += ofn.lpstrFile;
		//Procura a extensão apos a ultima "\" se não encontrar prossegue se não acha e deleta
		if ( (str.find(GetFileExt(AxisType),str.find_last_of('\\')+1)) != -1 ){
			str.erase(str.find(GetFileExt(AxisType),str.find_last_of('\\')+1));
		}
		str += GetFileExt(AxisType);
		PCtrl.SetAHWNDToPar();
		//PCtrl.CommAll();//Envia todos parametros para as placas
		PCtrl.Save_AxisFile(str.c_str(),AxisType);

		CLog::Log.SetCurrentFile(str.c_str(),AxisType);
		InvalidateRect(hwnd, NULL, NULL);
	}
}

void NewFile(HWND hwnd,char* AxisType){
/*	
	for (int i=0;i<PCtrl.PEixoList.size();i++){
		if (strcmp(PCtrl.PEixoList[i].Tipo,AxisType)==0){
			PCtrl.PEixoList[i] = Default_Ctrl.PEixoList[i];
		}
	}
	PCtrl.SetAParToHWND();
	CLog::Log.SetCurrentFile("",AxisType);
*/
}


char* GetFileExt(const char* AxisType ){
	if (strcmp(AxisType,"User")==0){
		return ".apf";
	}
	if (strcmp(AxisType,"Config")==0){
		return ".acf";
	}
	return NULL;
}

void Teste(HWND hwnd){
}