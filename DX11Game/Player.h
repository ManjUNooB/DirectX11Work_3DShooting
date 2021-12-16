// プレイヤー [Player.h]
#pragma once
#include "Model.h"

class CPlayer : public CModel
{
public:
	CPlayer(CScene* pScene); // コンストラクタ
	virtual ~CPlayer();		 // デストラクタ

	virtual HRESULT Init();	 // 初期化
	virtual void Fin();		 // 終了処理
	virtual void Update();	 // 更新
};
