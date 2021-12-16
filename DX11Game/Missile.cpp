// 追尾ミサイル [Missile.cpp]
#include "Missile.h"
#include "Scene.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Game.h"
#include "Fade.h"

// 定数
namespace {
	const float g_fSpeed = 50.0f;
	const float g_fRotateSpeed = 1.0f;	// 単位:度
	const int g_nMaxLife = 600;
}

//グローバル
int g_BreakCount = 0;

// コンストラクタ
CMissile::CMissile(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_MISSILE);

	m_pTarget = nullptr;
}

// デストラクタ
CMissile::~CMissile()
{
}

// 初期化
HRESULT CMissile::Init()
{
	SetModel(MODEL_MISSILE);

	m_nLife = g_nMaxLife;

	return CModel::Init();
}

// 更新
void CMissile::Update()
{
	// 爆発エフェクト更新
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

	// ターゲットが有効?
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
	// ターゲットへのベクトルを取得
	XMFLOAT3& vTargetPos = m_pTarget->GetPos();
	XMFLOAT3 vTarget;
	vTarget.x = vTargetPos.x - m_vPos.x;
	vTarget.y = vTargetPos.y - m_vPos.y;
	vTarget.z = vTargetPos.z - m_vPos.z;
	// ワールド変換行列取得
	XMFLOAT4X4 mW = GetWorld();
	// モデル座標軸取得
	XMFLOAT3 vX = XMFLOAT3(mW._11, mW._12, mW._13);
	XMFLOAT3 vY = XMFLOAT3(mW._21, mW._22, mW._23);
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);
	// 座標取得、クリア
	m_vPos = XMFLOAT3(mW._41, mW._42, mW._43);
	mW._41 = mW._42 = mW._43 = 0.0f;

	// ターゲットが上下左右どちらか
	XMMATRIX mR = XMMatrixIdentity();
	XMVECTOR axisX = XMLoadFloat3(&vX);
	XMVECTOR axisY = XMLoadFloat3(&vY);
	float fRight = vX.x * vTarget.x + vX.y * vTarget.y + vX.z * vTarget.z;	// 内積
	if (fRight > 0.0f)		// 右
		mR = XMMatrixRotationAxis(axisY, XMConvertToRadians(g_fRotateSpeed));
	else if (fRight < 0.0f)	// 左
		mR = XMMatrixRotationAxis(axisY, XMConvertToRadians(-g_fRotateSpeed));
	float fUp = vY.x * vTarget.x + vY.y * vTarget.y + vY.z * vTarget.z;		// 内積
	if (fUp > 0.0f)			// 上
		mR *= XMMatrixRotationAxis(axisX, XMConvertToRadians(-g_fRotateSpeed));
	else if (fUp < 0.0f)	// 下
		mR *= XMMatrixRotationAxis(axisX, XMConvertToRadians(g_fRotateSpeed));

	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// 前進
	m_vPos.x += vZ.x * g_fSpeed;
	m_vPos.y += vZ.y * g_fSpeed;
	m_vPos.z += vZ.z * g_fSpeed;

	// ワールド変換行列に反映
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// 衝突判定
	if (!m_uExpTimer) {
		if (m_pTarget) {
			switch (((CGame*)m_pScene)->GetBound()) {
			case 2:	// 境界ボックス
				if (CollisionAABB(m_pTarget)) {
					m_pTarget->StartExplosion();
					StartExplosion();
				}
				break;
			case 1:	// 境界球
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

// 発射
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
	case 0:	// 境界表示無し
		break;
	case 1:	// 境界球
		pMissile->SetBSphereVisible();
		break;
	case 2:	// 境界ボックス
		pMissile->SetBBoxVisible();
		break;
	}
	return 1;
}
