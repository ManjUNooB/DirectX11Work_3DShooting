//------------------------------------------------------------------//
//	Contents	:	main.cpp
//					DirectX�֘A�̍X�V�E������
//					�J�������̐F�X�ȍX�V�E�������E�`��E�I����
//	Author		:	Ryuga Sakakibara
//					HAL���É�
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