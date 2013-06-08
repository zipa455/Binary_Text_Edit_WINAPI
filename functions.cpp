#include "functions.h"


RECT rect = {50,50,50,50};
	PAINTSTRUCT ps;
		HDC hdc;
	int cx;
    int pParts[5];
    
	RECT rect2 = {0};
	HBRUSH brush = CreateSolidBrush(RGB(255,0,0));
	TCHAR FileName[1024] = {0};
	
	 int xy = 0;

	char text[] = "a";
	//char File[102400] = {0};  //100 KB
	int FileLength = 0;
	wchar_t FileW[102400] = {0};
	wchar_t text_t[] = L"ab";

	int maxrows;
	int currows;

void f_PAINT(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	hdc = BeginPaint(hWnd, &ps);
		
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		//FileW [0] = 0x31;
		

	int i = 0;
	int j = 0;
	int k =0;
	int m = 0;
	SIZE sz;
	GetTextExtentPoint32(hdc,_T("FF  "),4,&sz);
	GetClientRect(hWnd,&rect2);	

	maxrows = rect2.bottom / 40;	

	int jm = (rect2.right - 10) / 20 ;
	if(FileLength!=0)
	{
		SetScrollRange(hWnd, SB_VERT, 0, FileLength /2 / jm, true);

		sprintf(text,"%d * %d, %d",jm, maxrows, currows);
		SetWindowText(hWnd, _T(text));
		for(int i = 0; i<maxrows;i++)
		{
			for(j=0; j < jm  ; j++)
			{
				if(i*jm + j + currows*jm > FileLength) goto exloop;
				sprintf(text, "%02X" , File[(i*jm + j  + currows*jm)]);			
			

				TextOut(hdc, 10+(20*j), (i*40)+10, (LPCSTR)text, 2);			
					
			}			
		
		}	
exloop:;
		for(int i = 0; i<maxrows;i++)
		{
			for(j=0; j < jm; j++)
			{
				if(i*jm + j + currows*jm > FileLength) goto exloop2;						
				sprintf(text, "%c " , File[(i*jm + j  + currows*jm)]);
			
					
				TextOut(hdc, 15+(20*j), (i*40)+25, (LPCSTR)text, 2);
				
			}			
		}	
exloop2:;

		
		//SelectObject(hdc,brush);
		//Ellipse(hdc,50,50,150,150);
	}


		EndPaint(hWnd, &ps);
}

void f_VSCROLL(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	switch(LOWORD(wParam))
	{
	case SB_LINEDOWN:
		currows++;
		break;
	case SB_LINEUP:
		currows--;
		break;
	case SB_THUMBTRACK:
		currows = HIWORD(wParam);
		break;
	}
	
	SetScrollPos(hWnd, SB_VERT, currows, true);
	InvalidateRect(hWnd, NULL, true);
	UpdateWindow(hWnd);
	SendMessage(hWnd, WM_PAINT, wParam, lParam);
}

void f_LBUTTONDBCLK(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	GetClientRect(hWnd,&rect2);
	//int x,y;
	x = (LOWORD(lParam)-10) / 20;
	y = (HIWORD(lParam)-10) / 40;
	xy == 1;
	sprintf(text,"%dx%d",x,y);
	SetWindowText(hWnd, _T(text));
	//MessageBox(NULL,_T(text),NULL,NULL);
	int jm = (rect2.right - 10) / 20 ;
	MoveWindow(hEdit1,x*20+10,y*40+10,20,40,true);
	ShowWindow(hEdit1,SW_SHOW);
	sprintf(text,"%c",File[y*jm+x]);
	SetWindowText(hEdit1,_T(text));
	SetFocus(hEdit1);
	SendMessage(hWnd, WM_PAINT, wParam, lParam);

}

WNDPROC oldEditProc = NULL;
LRESULT CALLBACK newEditProc(HWND , UINT , WPARAM , LPARAM );
LRESULT CALLBACK newEditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		{
			if(VK_RETURN == wParam)
			{
				OnEnter(hWnd);	
				return 0;   // запрет обработки по-умолчанию
			}
			if(VK_ESCAPE == wParam)
			{
				ShowWindow(hEdit,SW_HIDE);
			}
		}
		break;
	case WM_CHAR:		
			{
				sprintf(text,"%c",(TCHAR)wParam);
				SetWindowText(hEdit,_T(text));			
				return 0;  
			}     // запрет обработки по-умолчанию
		break;	
	}
	

	return((LRESULT)CallWindowProc((WNDPROC)oldEditProc,hEdit,msg,wParam,lParam));
}
void f_CREATE(HWND hWnd, UINT message, UINT wParam, LONG lParam,HINSTANCE hInst)
{
			//LoadLibrary("RICHED32.DLL");
			/////////////////////////////////////////////////////////////////////////////////
            // строка состояния
            //////////////////////////////////////////////////////////////////////////////////            
            //hStatusWindow = CreateWindowEx(NULL,STATUSCLASSNAME, _T(""),WS_CHILD | WS_VISIBLE | WS_BORDER | SBARS_SIZEGRIP | CCS_BOTTOM,                                  
            //                     0, 0, 0, 0, hWnd, (HMENU)IDR_MENU2, hInst, NULL);		
			GetClientRect(hWnd,&rect2);
			pParts[0] = 50;
            pParts[1] = 200+100;
            pParts[2] = 200+100+100;
            pParts[3] = 200+100+100+100;
			pParts[4] = rect2.right;			
 
            //SendMessage(hStatusWindow, SB_SETPARTS, 5, (LPARAM)&pParts);
            //TCHAR B1 [] = _T("Блок 1");
            //SendMessage(hStatusWindow,SB_SETTEXT,0, (LPARAM)&B1);
            //SendMessage(hStatusWindow, SB_SETTEXT,1 | SBT_RTLREADING, (LPARAM)B1);
            //SendMessage(hStatusWindow, SB_SETTEXT,2 | SBT_RTLREADING , (LPARAM)B1);
            //SendMessage(hStatusWindow, SB_SETTEXT,3 | SBT_RTLREADING   , (LPARAM)B1); 
            //SendMessage(hStatusWindow, SB_SETTEXT,4 | SBT_NOBORDERS, (LPARAM)B1);


			::hWnd=hWnd;
			/////////////////////////////////////////////////////////////////////////////////
			/// TextBox
			/////////////////////////////////////////////////////////////////////////////////
			hEdit1 =   CreateWindow(TEXT("Edit"), TEXT("dsd"), WS_CHILD | WS_BORDER  /*WS_VISIBLE |*/ | ES_MULTILINE  ,  0, 0,  rect2.right/4*3-5, rect2.bottom, hWnd, NULL, hInst, NULL);
			oldEditProc = (WNDPROC)GetWindowLongPtr(hEdit1,GWLP_WNDPROC);
		    SetWindowLongPtr(hEdit1,GWLP_WNDPROC,(LPARAM)newEditProc);
			//hEdit2 =   CreateWindow(TEXT("Edit"), TEXT("dsd"), WS_CHILD  /*WS_VISIBLE |*/  ,  rect2.right/4*3+5, 0, rect2.right , rect2.bottom, hWnd, (HMENU)IDR_MENU2, hInst, NULL);
			//hButton1 = CreateWindow(TEXT("button"), TEXT("Press me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,10, 10, 80, 30, hWnd, (HMENU)20000, hInst, NULL);
}

/// Изменение размеров главного строка

void f_SIZE(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	
	SendMessage(hStatusWindow, WM_SIZE, 0, 0);
	GetClientRect(hWnd,&rect2);
			pParts[0] = 50;
            pParts[1] = rect2.right-400;
            pParts[2] = rect2.right-300;
			pParts[3] = rect2.right-200;
			pParts[4] = rect2.right;
	//SendMessage(hStatusWindow, SB_SETPARTS, 5, (LPARAM)&pParts);
	MoveWindow(hEdit1,0,0,rect2.right/4*3-5,rect2.bottom,true);
	MoveWindow(hEdit2,rect2.right/4*3+5,0,rect2.right-rect2.right/4*3-5,rect2.bottom,true);
	//sprintf(text,"Size: %d , %d", rect2.right/4*3,rect2.bottom-50);
	SendMessage(hStatusWindow, SB_SETTEXT,4 | SBT_NOBORDERS, (LPARAM)_T(text));
		
}

/////////////////////////////////////////////////////////////////////////
//  Открытие файла
////////////////////////////////////////////////////////////////////////
OPENFILENAME ofn;
void f_OPENFILE(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{		
	ZeroMemory(&ofn,sizeof(ofn)); // очистим структуру
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = FileName;
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		ofn.nMaxFile = 1024;    
	int i =GetOpenFileName (&ofn) ;
	if( i )	;//MessageBox(NULL,_T(FileName),_T("open"),NULL);
	else {MessageBox(NULL,_T("Ошибка открытия файла"),_T("Ошибка"),NULL); return;}
	
	HANDLE hFile;
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(FileName,
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
	{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
	DWORD dwBytes = 0, BufSize = 0;
	BufSize = GetFileSize(hFile, NULL);
	ReadFile(hFile, File, 10240, &dwBytes, NULL);
	CloseHandle(hFile);
	
	FileLength = dwBytes;
	/*	dwBytes = 0;
		if (INVALID_HANDLE_VALUE == (hFile = 
			CreateFile(FileName,
				GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
		{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
		ReadFile(hFile, FileW, 10240, &dwBytes, NULL);
		CloseHandle(hFile);*/
	
	//UpdateWindow(hWnd);
	SendMessage(hWnd, WM_PAINT, wParam, lParam);
}

void f_SAVEFILEAS(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{		
	ZeroMemory(&ofn,sizeof(ofn)); // очистим структуру
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = FileName;
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		ofn.nMaxFile = 1024;    
	int i =GetSaveFileName(&ofn) ;
	if( i )	;//MessageBox(NULL,_T(FileName),_T("open"),NULL);
	else {MessageBox(NULL,_T("Ошибка открытия файла"),_T("Ошибка"),NULL); return;}
	
	HANDLE hFile;
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(ofn.lpstrFile,
			GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)))
	{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
	DWORD dwBytes = 0, BufSize = 0;
	BufSize = GetFileSize(hFile, NULL);
	WriteFile(hFile, File, FileLength, &dwBytes, NULL);
	CloseHandle(hFile);
	
	FileLength = dwBytes;
	/*	dwBytes = 0;
		if (INVALID_HANDLE_VALUE == (hFile = 
			CreateFile(FileName,
				GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
		{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
		ReadFile(hFile, FileW, 10240, &dwBytes, NULL);
		CloseHandle(hFile);*/
	
	//UpdateWindow(hWnd);
	SendMessage(hWnd, WM_PAINT, wParam, lParam);
}

void f_SAVEFILE(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{		
	/*ZeroMemory(&ofn,sizeof(ofn)); // очистим структуру
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = FileName;
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		ofn.nMaxFile = 1024;    */
	/*int i =GetOpenFileName (&ofn) ;*/
	/*if( i )	;//MessageBox(NULL,_T(FileName),_T("open"),NULL);
	else {MessageBox(NULL,_T("Ошибка открытия файла"),_T("Ошибка"),NULL); return;}*/
	
	HANDLE hFile;
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(FileName,
			GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)))
	{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
	DWORD dwBytes = 0, BufSize = 0;
	BufSize = GetFileSize(hFile, NULL);
	WriteFile(hFile, File, FileLength, &dwBytes, NULL);
	CloseHandle(hFile);
	
	FileLength = dwBytes;
	/*	dwBytes = 0;
		if (INVALID_HANDLE_VALUE == (hFile = 
			CreateFile(FileName,
				GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
		{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
		ReadFile(hFile, FileW, 10240, &dwBytes, NULL);
		CloseHandle(hFile);*/
	
	//UpdateWindow(hWnd);
	SendMessage(hWnd, WM_PAINT, wParam, lParam);
}

void f_ABOUT(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	CHARFORMAT2 cf;  
 
	cf.dwMask = CFM_BACKCOLOR ;//| CFM_COLOR | CFM_ITALIC;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.crBackColor = RGB(0,255,0);
	//cf.crTextColor = RGB(255,255,0);
	cf.dwEffects = CFE_ITALIC;
	//cf.dwReserved = 0;
	
	SendMessage(hEdit1, EM_SETCHARFORMAT,SCF_ALL, (LPARAM)&cf);
	
}

void OnEnter(HWND hWnd)
{
	//if(xy == 1)
	{
		RECT rect;
		char c[5];
		GetClientRect(hWnd,&rect);
		int jm = (rect.right - 10) / 20 ;
		GetWindowText(hEdit1,c,5);
		File[y*jm+x] = c[0];			
		xy = 0;
		ShowWindow(hEdit1,SW_HIDE);
		SendMessage(hWnd, WM_PAINT, NULL, NULL);
	}
	
}