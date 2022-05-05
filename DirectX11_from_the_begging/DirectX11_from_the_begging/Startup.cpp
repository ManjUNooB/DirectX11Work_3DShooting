//----------------------------------------------------//
//	Contents	:	Startup.cpp
//					WINAPI関連だったり
//					FPS管理だったり
//	Author		:	Ryuga Sakakibara
//	LastUpdate	:	2022/04/20
//	Since		:	2022/04/20
//----------------------------------------------------//
#include <Windows.h>
#include <cstdio>
#include <crtdbg.h>
#include "Defines.h"
#include "App/main.h"

//	timeGetTime周りの使用
#pragma comment(lib,"winmm.lib")

//--プロトタイプ宣言--
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//	エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	_CrtSetDbgFlag()	//	メモリリーク検知用

	//--変数宣言--//
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;
}