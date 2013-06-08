// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c



#include "functions.h"





static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("BinaryEditor");
HINSTANCE hInstansemain;
//HINSTANCE hRTFLib;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS  ;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = (LPCSTR)IDR_MENU1; 
	
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInstansemain = hInstance; // Store instance handle in our global variable	
	// NULL: not used in this application
	//::hInst = hInst;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 200,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);
	
	MSG msg;

	//hRTFLib = LoadLibrary("RICHED32.DLL");
	HACCEL  ghAccelTable = LoadAcceleratorsW(hInstance,MAKEINTRESOURCEW(IDR_ACCELERATOR1));
	while(GetMessage(&msg,NULL,0,0))
	{		
		if (ghAccelTable)
		{
			if (TranslateAccelerator (hWnd, ghAccelTable, &msg))
				continue;
		}

		if (!IsDialogMessage (hWnd, &msg))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		
	}


	DestroyAcceleratorTable (ghAccelTable);
	return (int) msg.wParam;

	
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	
	
	switch(message)
	{
		
	
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_40002:
			f_OPENFILE(hWnd,message,wParam,lParam);
			break;
		case ID_40006:
			MessageBox(NULL,_T("BinaryEditor\nПрограмма позволяет редактировать\nбинарные файлы\n\nРазработанно: Шакиров Артемий\n2013 год"),_T("О программе"),NULL);
			f_ABOUT(hWnd,message,wParam,lParam);			
			break;
		case ID_40003:
			f_SAVEFILE(hWnd,message,wParam,lParam);
			break;
		case ID_40004:
			f_SAVEFILEAS(hWnd,message,wParam,lParam);
		case ID_40005:
			SendMessage(hWnd,WM_CLOSE,NULL,NULL);
		}
		break;
	case WM_PAINT:
		f_PAINT(hWnd,message,wParam,lParam);
		break;
	case WM_DESTROY:
		//FreeLibrary(hRTFLib);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
         f_CREATE(hWnd,message,wParam,lParam,hInstansemain);

         break;  
		}
	case WM_SIZE:
        f_SIZE(hWnd,message,wParam,lParam);
        break;
	case WM_VSCROLL:
		f_VSCROLL(hWnd,message,wParam,lParam);
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDBLCLK:
		f_LBUTTONDBCLK(hWnd,message,wParam,lParam);
		break;

	default:
		return DefWindowProc(hWnd,message,wParam,lParam);	
	}
	return 0;
}

