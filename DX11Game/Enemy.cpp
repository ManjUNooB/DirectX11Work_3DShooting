// 敵機 [Enemy.cpp]
#include "Enemy.h"
#include "Input.h"
#include "Player.h"
#include "Game.h"


// 定数
namespace {
	const float g_fSpeed = 10.0f;
	const float g_fRollSpeed = 10.0f;//単位:度
	const float g_fPitchSpeed = 5.0f;//単位:度
}

// コンストラクタ
CEnemy::CEnemy(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_ENEMY);

	m_pPlayer = nullptr;
}

// デストラクタ
CEnemy::~CEnemy()
{
}

// 初期化
HRESULT CEnemy::Init()
{
	SetModel(MODEL_ENEMY);
	SetRadius(500.0f);
	XMFLOAT4X4 mW;
	XMStoreFloat4x4(&mW, XMMatrixRotationY(XMConvertToRadians(180.0f)));
	SetWorld(mW);

	return CModel::Init();
}

// 終了処理
void CEnemy::Fin()
{
	CModel::Fin();
}

// 更新
void CEnemy::Update()
{
	// ワールド変換行列取得
	XMFLOAT4X4 mW = GetWorld();
	// モデル座標軸取得
	XMFLOAT3 vX = XMFLOAT3(mW._11, mW._12, mW._13);
	XMFLOAT3 vY = XMFLOAT3(mW._21, mW._22, mW._23);
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);
	// 座標取得、クリア
	m_vPos = XMFLOAT3(mW._41, mW._42, mW._43);
	mW._41 = mW._42 = mW._43 = 0.0f;

	// ピッチ
	XMMATRIX mR = XMMatrixIdentity();
	if (0) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(g_fPitchSpeed));
	}
	if (1) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(-g_fPitchSpeed));
	}
	// ロール
	if (0) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(g_fRollSpeed)));
	}
	if (0) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(-g_fRollSpeed)));
	}
	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// 前進
	//if (CInput::GetKeyPress(VK_LCONTROL))
	
		m_vPos.x += vZ.x * g_fSpeed;
		m_vPos.y += vZ.y * g_fSpeed;
		m_vPos.z += vZ.z * g_fSpeed;
		
		if (m_vPos.z > 10000)
			m_vPos.z -= vZ.z * g_fSpeed;
	

	// ワールド変換行列に反映
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// 衝突判定
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
