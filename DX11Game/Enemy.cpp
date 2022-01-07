// �G�@ [Enemy.cpp]
#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include "Game.h"


// �萔
namespace {
	const float g_fSpeed = 10.0f;
	const float g_fRollSpeed = 10.0f;//�P��:�x
	const float g_fPitchSpeed = 5.0f;//�P��:�x
}

// �R���X�g���N�^
CEnemy::CEnemy(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_ENEMY);

	m_pPlayer = nullptr;
}

// �f�X�g���N�^
CEnemy::~CEnemy()
{
}

// ������
HRESULT CEnemy::Init()
{
	SetModel(MODEL_ENEMY);
	SetRadius(500.0f);
	XMFLOAT4X4 mW;
	XMStoreFloat4x4(&mW, XMMatrixRotationY(XMConvertToRadians(180.0f)));
	SetWorld(mW);

	return CModel::Init();
}

// �I������
void CEnemy::Fin()
{
	CModel::Fin();
}

// �X�V
void CEnemy::Update()
{
	// ���[���h�ϊ��s��擾
	XMFLOAT4X4 mW = GetWorld();
	// ���f�����W���擾
	XMFLOAT3 vX = XMFLOAT3(mW._11, mW._12, mW._13);
	XMFLOAT3 vY = XMFLOAT3(mW._21, mW._22, mW._23);
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);
	// ���W�擾�A�N���A
	m_vPos = XMFLOAT3(mW._41, mW._42, mW._43);
	mW._41 = mW._42 = mW._43 = 0.0f;

	// �s�b�`
	XMMATRIX mR = XMMatrixIdentity();
	if (0) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(g_fPitchSpeed));
	}
	if (1) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(-g_fPitchSpeed));
	}
	// ���[��
	if (0) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(g_fRollSpeed)));
	}
	if (0) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(-g_fRollSpeed)));
	}
	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// �O�i
	//if (CInput::GetKeyPress(VK_LCONTROL))
	
		m_vPos.x += vZ.x * g_fSpeed;
		m_vPos.y += vZ.y * g_fSpeed;
		m_vPos.z += vZ.z * g_fSpeed;
		
		if (m_vPos.z > 10000)
			m_vPos.z -= vZ.z * g_fSpeed;
	

	// ���[���h�ϊ��s��ɔ��f
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// �Փ˔���
	if (m_pPlayer) {
		int nBound = ((CGame*)m_pScene)->GetBound();
		if (nBound == 1) {
			if (CollisionBS(m_pPlayer)) {
				m_pPlayer->StartExplosion();
				StartExplosion();
			}
		} else {
			if (CollisionAABB(m_pPlayer)) {
				m_pPlayer->StartExplosion();
				StartExplosion();
			}
		}
	}

	CModel::Update();
}
