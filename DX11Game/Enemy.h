// 敵機 [Enemy.h]
#pragma once
#include "Model.h"

class CPlayer;
class CEnemy : public CModel
{
private:
	CPlayer* m_pPlayer;

public:
	CEnemy(CScene* pScene);		// コンストラクタ
	virtual ~CEnemy();			// デストラクタ

	virtual HRESULT Init();		// 初期化
	virtual void Fin();			// 終了処理
	virtual void Update();		// 更新

	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
};
