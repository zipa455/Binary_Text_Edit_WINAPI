#include "functions.h"


RECT rect = {50,50,50,50};
	PAINTSTRUCT ps;
		HDC hdc;
	int cx;
    int pParts[5];
    
	RECT rect2 = {0};
	HBRUSH brush = CreateSolidBrush(RGB(255,0,0));
	TCHAR FileName[1024] = {0};
	
	HWND hStatusWindow;   //StatusBar
	HWND hEdit1;			  //Edit1

	char text[] = "a";
	char File[102400] = {0};  //100 KB
	wchar_t FileW[102400] = {0};
	wchar_t text_t[] = L"ab";

void f_PAINT(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	hdc = BeginPaint(hWnd, &ps);
		
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		//FileW [0] = 0x31;
		
		for(int i = 0; i<80;i++)
		{
			sprintf(text, "%02X" , File[i]);
			//sprintf(text_t, "%c " , FileW[i]);
			swprintf(text_t, L"%c " , FileW[i]);
			TextOut(hdc, 10+(20*i), 10, (LPCSTR)text, 2);
			//TextOut(hdc, 10+(20*i), 30, (LPCSTR)text_t, 2);
			TextOutW(hdc, 10+(20*i), 30, (LPCWSTR)text_t, 2);
			
		}
		
		
		//SelectObject(hdc,brush);
		//Ellipse(hdc,50,50,150,150);

		EndPaint(hWnd, &ps);
}

void f_CREATE(HWND hWnd, UINT message, UINT wParam, LONG lParam,HINSTANCE hInst)
{
			LoadLibrary("RICHED32.DLL");
			/////////////////////////////////////////////////////////////////////////////////
            // строка состояния
            //////////////////////////////////////////////////////////////////////////////////            
            hStatusWindow = CreateWindowEx(NULL,STATUSCLASSNAME, _T(""),WS_CHILD | WS_VISIBLE | WS_BORDER | SBARS_SIZEGRIP | CCS_BOTTOM,                                  
                                 0, 0, 0, 0, hWnd, (HMENU)IDR_MENU2, hInst, NULL);		
			GetClientRect(hWnd,&rect2);
			pParts[0] = 50;
            pParts[1] = 200+100;
            pParts[2] = 200+100+100;
            pParts[3] = 200+100+100+100;
			pParts[4] = rect2.right;			
 
            SendMessage(hStatusWindow, SB_SETPARTS, 5, (LPARAM)&pParts);
            TCHAR B1 [] = _T("Блок 1");
            SendMessage(hStatusWindow,SB_SETTEXT,0, (LPARAM)&B1);
            SendMessage(hStatusWindow, SB_SETTEXT,1 | SBT_RTLREADING, (LPARAM)B1);
            SendMessage(hStatusWindow, SB_SETTEXT,2 | SBT_RTLREADING , (LPARAM)B1);
            SendMessage(hStatusWindow, SB_SETTEXT,3 | SBT_RTLREADING   , (LPARAM)B1); 
            SendMessage(hStatusWindow, SB_SETTEXT,4 | SBT_NOBORDERS, (LPARAM)B1);

			/////////////////////////////////////////////////////////////////////////////////
			/// TextBox
			/////////////////////////////////////////////////////////////////////////////////
			hEdit1 =   CreateWindow(TEXT("RichEdit"), TEXT("dsd"), WS_CHILD /*| WS_VISIBLE */| ES_MULTILINE | WS_VSCROLL |LBS_MULTIPLESEL |
				ES_AUTOVSCROLL  ,  0, 0, 0, /*rect2.right, rect2.bottom-50*/0, hWnd, (HMENU)20000, hInst, NULL);
}

/// Изменение размеров главного окна

void f_SIZE(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	
	SendMessage(hStatusWindow, WM_SIZE, 0, 0);
	GetClientRect(hWnd,&rect2);
			pParts[0] = 50;
            pParts[1] = rect2.right-400;
            pParts[2] = rect2.right-300;
			pParts[3] = rect2.right-200;
			pParts[4] = rect2.right;
	SendMessage(hStatusWindow, SB_SETPARTS, 5, (LPARAM)&pParts);
	MoveWindow(hEdit1,0,0,rect2.right,rect2.bottom-50,true);
	sprintf(text,"Size: %d , %d", rect2.right,rect2.bottom);
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
	if( i )	MessageBox(NULL,_T(FileName),_T("open"),NULL);
	else {MessageBox(NULL,_T("ERROR"),_T("open"),NULL); return;}
	
	HANDLE hFile;
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(FileName,
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
	{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
	DWORD dwBytes = 0, BufSize = 0;
	BufSize = GetFileSize(hFile, NULL);
	ReadFile(hFile, File, 10240, &dwBytes, NULL);
	CloseHandle(hFile);
	dwBytes = 0;
	if (INVALID_HANDLE_VALUE == (hFile = 
		CreateFile(FileName,
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)))
	{	MessageBox(NULL,_T("ERROR_OPEN"),NULL,MB_OK); return;	}
	ReadFile(hFile, FileW, 10240, &dwBytes, NULL);
	CloseHandle(hFile);


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
