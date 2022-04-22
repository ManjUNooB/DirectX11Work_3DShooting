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

//--プロトタイプ宣言--//
