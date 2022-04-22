//------------------------------------------------------------------//
//	Contents	:	main.h
//	Author		:	Ryuga Sakakibara
//					HAL���É�
//	LastUpdate	:	2022/04/22
//	Since		:	2022/04/22
//------------------------------------------------------------------//
#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>

//--�v���g�^�C�v--//
HRESULT Init(HWND hWnd,UINT width,UINT height);
void Update();
void Draw();
void Uninit();


#endif	//	__MAIN_H__
