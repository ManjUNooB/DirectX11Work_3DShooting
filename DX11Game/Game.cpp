//=============================================================================
//
// ゲーム クラス実装 [Game.cpp]
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

// コンストラクタ
CGame::CGame() : CScene()
{
	m_id = SCENE_GAME;

	m_pPlayer = nullptr;
	m_nBound = 0;
}

// デストラクタ
CGame::~CGame()
{
}

// 初期化
bool CGame::Init()
{
	m_bResult = false;

	// オブジェクト生成
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

	// 全オブジェクト初期化
	if (FAILED(CGameObj::InitAll(m_pObj))) {
		return false;
	}

	m_camera.SetPlayer(m_pPlayer);
	for (int i = 0; i < _countof(pEnemy); ++i) {
		XMFLOAT4X4& mW = pEnemy[i]->GetWorld();
		mW._41 = pEnemy[i]->GetRadius() * 10.0f * (i + 0.5f - _countof(pEnemy) * 0.5f);
		mW._43 = m_pPlayer->GetRadius() * 15.0f;
	}

	// BGM再生開始
	CSound::Play(BGM_GAME);

	return true;
}

// 終了処理
void CGame::Fin()
{
	// BGM再生停止
	CSound::Stop(BGM_GAME);

	// 全オブジェクト終了処理
	CGameObj::FinAll(m_pObj);
}

// 更新
void CGame::Update()
{
	// 境界球/境界ボックス表示切替
	if (CInput::GetKeyTrigger(VK_B)) {
		CGameObj* pObj = Find();
		m_nBound = (m_nBound + 1) % 3;
		switch (m_nBound) {
		case 0:	// 境界表示無し
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
		case 1:	// 境界球
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
		case 2:	// 境界ボックス
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

	// 全キャラ更新
	CGameObj::UpdateAll(m_pObj);

	if (!m_bResult) {
		if (CInput::GetKeyRelease(VK_BACK) ||
			CInput::GetKeyRelease(VK_DELETE)) {
			m_bResult = true;
			CFade::Out(SCENE_TITLE);
		}
	}

	// デバッグ表示
	CDebugProc::Print("*** ｷｮｳｶｲ ﾋｮｳｼﾞ ***\n");
	CDebugProc::Print("None/Sphere/AABB:[B]\n");
	CDebugProc::Print("***ﾀｲﾄﾙﾆﾓﾄﾞﾙ***\n");
	CDebugProc::Print("BackSpace/Delete\n");
	CDebugProc::Print("\n");

	
}

// 描画
void CGame::Draw()
{
	// 全キャラ描画
	CGameObj::DrawAll(m_pObj);
}
