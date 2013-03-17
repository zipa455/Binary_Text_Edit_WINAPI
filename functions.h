#define FUNCTIONS
#ifdef FUNCTIONS

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "resource.h"

#include <CommCtrl.h> 
#pragma comment(lib,"ComCtl32.Lib")

#include <RICHEDIT.h>
//#pragma comment(lib,"RICHED.DLL")



void f_PAINT	(HWND , UINT , UINT , LONG );
void f_CREATE	(HWND , UINT , UINT , LONG ,HINSTANCE);
void f_SIZE		(HWND , UINT , UINT , LONG );
void f_OPENFILE	(HWND , UINT , UINT , LONG );
void f_ABOUT	(HWND , UINT , UINT , LONG );

#endif