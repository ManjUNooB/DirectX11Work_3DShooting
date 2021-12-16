//=============================================================================
//
// モデル クラス定義 [Model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "GameObj.h"
#include "AssimpModel.h"

enum EModel {
	MODEL_SKY = 0,		// スカイ ドーム
	MODEL_PLAYER,		// プレイヤー モデル
	MODEL_ENEMY,		// 敵モデル
	MODEL_MISSILE,		// ミサイル

	MAX_MODEL
};

class CExplosion;
class CModel : public CGameObj
{
private:
	static CAssimpModel* m_pModels[MAX_MODEL];
	CAssimpModel* m_pModel;

protected:
	CExplosion* m_pExp;	// 爆発エフェクト
	UINT m_uExpTimer;	// 爆発中タイマー

public:
	CModel(CScene* pScene);
	virtual ~CModel();

	static HRESULT LoadAll();
	static void ReleaseAll();

	virtual HRESULT Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();

	void SetModel(EModel model);
	static CAssimpModel* GetAssimp(EModel model);

	void StartExplosion();
};
