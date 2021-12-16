//=============================================================================
//
// �Q�[�� �N���X���� [Game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "Game.h"
#include "Input.h"
#include "GameObj.h"
#include "Sound.h"
#include "Fade.h"
#include "DebugProc.h"
#include "Enemy.h"

// �R���X�g���N�^
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;

	m_pPlayer = nullptr;
	m_nBound = 0;
}

// �f�X�g���N�^
CGame::~CGame()
{
}

// ������
bool CGame::Init()
{
	m_bResult = false;

	// �I�u�W�F�N�g����
	m_camera.Init();
	m_camera.SetSkyDome(CModel::GetAssimp(MODEL_SKY));
	SetCamera(&m_camera);

	m_light.Init();
	SetLight(&m_light);

	m_pPlayer = new CPlayer(this);

	CEnemy* pEnemy[1];
	for (int i = 0; i < _countof(pEnemy); ++i) {
		pEnemy[i] = new CEnemy(this);
		pEnemy[i]->SetPlayer(m_pPlayer);
	}

	// �S�I�u�W�F�N�g������
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_camera.SetPlayer(m_pPlayer);
	for (int i = 0; i < _countof(pEnemy); ++i) {
		XMFLOAT4X4& mW = pEnemy[i]->GetWorld();
		mW._41 = pEnemy[i]->GetRadius() * 10.0f * (i + 0.5f - _countof(pEnemy) * 0.5f);
		mW._43 = m_pPlayer->GetRadius() * 15.0f;
	}

	// BGM�Đ��J�n
	CSound::Play(BGM_GAME);

	return true;
}

// �I������
void CGame::Fin()
{
	// BGM�Đ���~
	CSound::Stop(BGM_GAME);

	// �S�I�u�W�F�N�g�I������
	CGameObj::FinAll(m_pObj);
}

// �X�V
void CGame::Update()
{
	// ���E��/���E�{�b�N�X�\���ؑ�
	if (CInput::GetKeyTrigger(VK_B)) {
		CGameObj* pObj = Find();
		m_nBound = (m_nBound + 1) % 3;
		switch (m_nBound) {
		case 0:	// ���E�\������
			while (pObj) {
				switch (pObj->GetID()) {
				case GOT_PLAYER:
				case GOT_ENEMY:
				case GOT_MISSILE:
					pObj->SetBBoxVisible(false);
					pObj->SetBSphereVisible(false);
					break;
				}
				pObj = Find(-1, pObj);
			}
			break;
		case 1:	// ���E��
			while (pObj) {
				switch (pObj->GetID()) {
				case GOT_PLAYER:
				case GOT_ENEMY:
				case GOT_MISSILE:
					pObj->SetBSphereVisible();
					break;
				}
				pObj = Find(-1, pObj);
			}
			break;
		case 2:	// ���E�{�b�N�X
			while (pObj) {
				switch (pObj->GetID()) {
				case GOT_PLAYER:
				case GOT_ENEMY:
				case GOT_MISSILE:
					pObj->SetBBoxVisible();
					break;
				}
				pObj = Find(-1, pObj);
			}
			break;
		}
	}

	// �S�L�����X�V
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_BACK) ||
			CInput::GetKeyRelease(VK_DELETE)) {
			m_bResult = true;
			CFade::Out(SCENE_TITLE);
		}
	}

	// �f�o�b�O�\��
	CDebugProc::Print("*** ����� ˮ��� ***\n");
	CDebugProc::Print("None/Sphere/AABB:[B]\n");
	CDebugProc::Print("***���������***\n");
	CDebugProc::Print("BackSpace/Delete\n");
	CDebugProc::Print("\n");

	
}

// �`��
void CGame::Draw()
{
	// �S�L�����`��
	CGameObj::DrawAll(m_pObj);
}
