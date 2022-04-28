//------------------------------------------------------------------//
//	Contents	:	main.cpp
//					DirectX関連の更新・初期化
//					カメラ等の色々な更新・初期化・描画・終了等
//	Author		:	Ryuga Sakakibara
//					HAL名古屋
//	LastUpdate	:	2022/04/22
//	Since		:	2022/04/22
//------------------------------------------------------------------//
#include <App/main.h>
#include <Defines.h>

#define ASSERT_FAILED(fn) do {\
hr = fn; \
if (FAILED(hr)) {\
	MessageBox(nullptr, "Init_failed : "#fn, "Error", MB_OK);	\
	return hr;\
}}while(0)


HRESULT Init(HWND hWnd, UINT width, UINT height) {
	HRESULT hr;
	
	return hr;
}

void Update() {

}

void Draw() {

}

void Uninit() {

}