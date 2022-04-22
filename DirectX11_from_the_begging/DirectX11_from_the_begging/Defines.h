//------------------------------------------------------------------//
//	Contents	:	Defines.h
//					�萔�̒�`�p
//	Author		:	Ryuga Sakakibara
//					HAL���É�
//	LastUpdate	:	2022/04/22
//	Since		:	2022/04/22
//------------------------------------------------------------------//
#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>

//	�L���v�V������
constexpr auto APP_TITLE = ("�ۑ�T���v��");

// ��ʃT�C�Y
constexpr auto  SCREEN_WIDTH = (1280);
constexpr auto SCREEN_HEIGHT = (720);

// ���\�[�X�p�X
template <typename T>
constexpr auto ASSET(T path) { return "Asset/"path; }

// �ʐݒ�	���Ȃ�̌ʐݒ肩�킩���(�׋��s��)
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