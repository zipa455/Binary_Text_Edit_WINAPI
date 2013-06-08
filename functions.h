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

static HWND hWnd;
static HWND hStatusWindow;   //StatusBar
static HWND hEdit1;			  //Edit1
static HWND hEdit2;			  //Edit2
static HWND hButton1;

static int x;
static int y;

static char File[102400] = {0};  //100 KB

void f_PAINT	(HWND , UINT , UINT , LONG );
void f_CREATE	(HWND , UINT , UINT , LONG ,HINSTANCE);
void f_SIZE		(HWND , UINT , UINT , LONG );
void f_OPENFILE	(HWND , UINT , UINT , LONG );
void f_ABOUT	(HWND , UINT , UINT , LONG );
void f_VSCROLL	(HWND , UINT , UINT , LONG );
void f_EDIT1	(HWND , UINT , UINT , LONG );
void f_EDIT2	(HWND , UINT , UINT , LONG );
void f_LBUTTONDBCLK	(HWND , UINT , UINT , LONG );
void f_SAVEFILE(HWND , UINT , UINT , LONG );
void f_SAVEFILEAS(HWND , UINT , UINT , LONG );

void OnEnter(HWND);

#endif