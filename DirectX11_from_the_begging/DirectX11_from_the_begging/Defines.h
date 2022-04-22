//------------------------------------------------------------------//
//	Contents	:	Defines.h
//					定数の定義用
//	Author		:	Ryuga Sakakibara
//					HAL名古屋
//	LastUpdate	:	2022/04/22
//	Since		:	2022/04/22
//------------------------------------------------------------------//
#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>

//	キャプション名
constexpr auto APP_TITLE = ("課題サンプル");

// 画面サイズ
constexpr auto  SCREEN_WIDTH = (1280);
constexpr auto SCREEN_HEIGHT = (720);

// リソースパス
template <typename T>
constexpr auto ASSET(T path) { return "Asset/"path; }

// 個別設定	↓なんの個別設定かわからん(勉強不足)
#define USER_MYNOTE 1
#define USER_DESKTOP 0
#define USER_WORKPC 0

#if USER_MYNOTE0
#define USE_DIRECTXTEX 1
#define USE_FBXSDK 1
#else	//	not USER_MYNOTE0
#define USE_DIRECTXTEX 1\0
#define USE_FBXSDK 0
#endif
#define USE_EFFEKSEER 0

#endif	//__DEFINES_H__