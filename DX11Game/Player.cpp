// プレイヤー [Player.cpp]
#include "Player.h"
#include "Input.h"
#include "Missile.h"
#include "DebugProc.h"

// 定数
namespace {
	const float g_fSpeed = 10.0f;
	const float g_fRollSpeed = 4.0f;//単位:度
	const float g_fPitchSpeed = 2.0f;//単位:度
}

// コンストラクタ
CPlayer::CPlayer(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);
}

// デストラクタ
CPlayer::~CPlayer()
{
}

// 初期化
HRESULT CPlayer::Init()
{
	SetModel(MODEL_PLAYER);
	

	return CModel::Init();
}

// 終了処理
void CPlayer::Fin()
{
	CModel::Fin();
}

// 更新
void CPlayer::Update()
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
	if (CInput::GetKeyPress(VK_W) || CInput::GetKeyPress(VK_UP)) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(g_fPitchSpeed));
	}
	if (CInput::GetKeyPress(VK_S) || CInput::GetKeyPress(VK_DOWN)) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(-g_fPitchSpeed));
	}
	// ロール
	if (CInput::GetKeyPress(VK_A) || CInput::GetKeyPress(VK_LEFT)) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(g_fRollSpeed)));
	}
	if (CInput::GetKeyPress(VK_D) || CInput::GetKeyPress(VK_RIGHT)) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(-g_fRollSpeed)));
	}
	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// 前進
	if (CInput::GetKeyPress(VK_LCONTROL)) {
		m_vPos.x += vZ.x * g_fSpeed;
		m_vPos.y += vZ.y * g_fSpeed;
		m_vPos.z += vZ.z * g_fSpeed;
	}

	// ワールド変換行列に反映
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// 追尾ミサイル発射
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CMissile::Fire(&mW);
	}

	CModel::Update();

	// デバッグ表示
	CDebugProc::Print("*** ﾌﾟﾚｲﾔｰ ***\n");
	CDebugProc::Print("Pitch:[W][S]\n");
	CDebugProc::Print("Forward[LShift]\n");
	CDebugProc::Print("Roll:[A][D]\n");
	CDebugProc::Print("Guided Missile:[M]\n");
	CDebugProc::Print("\n");
}
