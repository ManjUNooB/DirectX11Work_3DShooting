//------------------------------------------------------------------//
//	Contents	:	main.h
//	Author		:	Ryuga Sakakibara
//					HAL名古屋
//	LastUpdate	:	2022/04/22
//	Since		:	2022/04/22
//------------------------------------------------------------------//
#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>

//--プロトタイプ--//
HRESULT Init(HWND hWnd,UINT width,UINT height);
void Update();
void Draw();
void Uninit();


#endif	//	__MAIN_H__
