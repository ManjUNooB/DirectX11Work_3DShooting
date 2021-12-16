// �ǔ��~�T�C�� [Missile.cpp]
#include "Missile.h"
#include "Scene.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Game.h"
#include "Fade.h"

// �萔
namespace {
	const float g_fSpeed = 50.0f;
	const float g_fRotateSpeed = 1.0f;	// �P��:�x
	const int g_nMaxLife = 600;
}

//�O���[�o��
int g_BreakCount = 0;

// �R���X�g���N�^
CMissile::CMissile(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_MISSILE);

	m_pTarget = nullptr;
}

// �f�X�g���N�^
CMissile::~CMissile()
{
}

// ������
HRESULT CMissile::Init()
{
	SetModel(MODEL_MISSILE);

	m_nLife = g_nMaxLife;

	return CModel::Init();
}

// �X�V
void CMissile::Update()
{
	// �����G�t�F�N�g�X�V
	if (m_pExp) {
		if (m_uExpTimer) {
			--m_uExpTimer;
			if (!m_uExpTimer) {
				Fin();
				delete this;
				return;
			}
		}
		m_pExp->Update();
	}

	if (!m_uExpTimer) {
		--m_nLife;
		if (m_nLife <= 0) {
			StartExplosion();
			return;
		}
	}

	// �^�[�Q�b�g���L��?
	if (!m_pTarget || !m_pTarget->GetVisible()) {
		CEnemy* pEnemy = (CEnemy*)m_pScene->Find(GOT_ENEMY);
		m_pTarget = nullptr;
		float fDist = FLT_MAX;
		while (pEnemy) {
			if (pEnemy->GetVisible()) {
				XMFLOAT3& vPos = pEnemy->GetPos();
				float dx = vPos.x - m_vPos.x;
				float dy = vPos.y - m_vPos.y;
				float dz = vPos.z - m_vPos.z;
				float dist = dx * dx + dy * dy + dz * dz;
				if (!m_pTarget) {
					fDist = dist;
					m_pTarget = pEnemy;
				} else {
					if (fDist > dist) {
						fDist = dist;
						m_pTarget = pEnemy;
					}
				}
			}
			pEnemy = (CEnemy*)m_pScene->Find(GOT_ENEMY, pEnemy);
		}
		if (!m_pTarget) {
			if (!m_uExpTimer)
				StartExplosion();
			return;
		}
	}
	// �^�[�Q�b�g�ւ̃x�N�g�����擾
	XMFLOAT3& vTargetPos = m_pTarget->GetPos();
	XMFLOAT3 vTarget;
	vTarget.x = vTargetPos.x - m_vPos.x;
	vTarget.y = vTargetPos.y - m_vPos.y;
	vTarget.z = vTargetPos.z - m_vPos.z;
	// ���[���h�ϊ��s��擾
	XMFLOAT4X4 mW = GetWorld();
	// ���f�����W���擾
	XMFLOAT3 vX = XMFLOAT3(mW._11, mW._12, mW._13);
	XMFLOAT3 vY = XMFLOAT3(mW._21, mW._22, mW._23);
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);
	// ���W�擾�A�N���A
	m_vPos = XMFLOAT3(mW._41, mW._42, mW._43);
	mW._41 = mW._42 = mW._43 = 0.0f;

	// �^�[�Q�b�g���㉺���E�ǂ��炩
	XMMATRIX mR = XMMatrixIdentity();
	XMVECTOR axisX = XMLoadFloat3(&vX);
	XMVECTOR axisY = XMLoadFloat3(&vY);
	float fRight = vX.x * vTarget.x + vX.y * vTarget.y + vX.z * vTarget.z;	// ����
	if (fRight > 0.0f)		// �E
		mR = XMMatrixRotationAxis(axisY, XMConvertToRadians(g_fRotateSpeed));
	else if (fRight < 0.0f)	// ��
		mR = XMMatrixRotationAxis(axisY, XMConvertToRadians(-g_fRotateSpeed));
	float fUp = vY.x * vTarget.x + vY.y * vTarget.y + vY.z * vTarget.z;		// ����
	if (fUp > 0.0f)			// ��
		mR *= XMMatrixRotationAxis(axisX, XMConvertToRadians(-g_fRotateSpeed));
	else if (fUp < 0.0f)	// ��
		mR *= XMMatrixRotationAxis(axisX, XMConvertToRadians(g_fRotateSpeed));

	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// �O�i
	m_vPos.x += vZ.x * g_fSpeed;
	m_vPos.y += vZ.y * g_fSpeed;
	m_vPos.z += vZ.z * g_fSpeed;

	// ���[���h�ϊ��s��ɔ��f
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// �Փ˔���
	if (!m_uExpTimer) {
		if (m_pTarget) {
			switch (((CGame*)m_pScene)->GetBound()) {
			case 2:	// ���E�{�b�N�X
				if (CollisionAABB(m_pTarget)) {
					m_pTarget->StartExplosion();
					StartExplosion();
				}
				break;
			case 1:	// ���E��
			default:
				if (CollisionBS(m_pTarget)) {
					m_pTarget->StartExplosion();
					StartExplosion();
					g_BreakCount++;
					if (g_BreakCount > 5)
					{
						CFade::Out(SCENE_RESULT);
					}
				}
				break;
			}
		}
	}
}

// ����
int CMissile::Fire(XMFLOAT4X4* pWorld, CEnemy* pEnemy)
{
	CScene* pScene = CScene::GetCurrent();
	if (!pScene)
		return -1;
	CMissile* pMissile = new CMissile(pScene);
	pMissile->SetWorld(*pWorld);
	pMissile->Init();
	pMissile->m_pTarget = pEnemy;
	switch (((CGame*)pScene)->GetBound()) {
	case 0:	// ���E�\������
		break;
	case 1:	// ���E��
		pMissile->SetBSphereVisible();
		break;
	case 2:	// ���E�{�b�N�X
		pMissile->SetBBoxVisible();
		break;
	}
	return 1;
}
