//=============================================================================
//
// ���f�� �N���X��` [Model.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "GameObj.h"
#include "AssimpModel.h"

enum EModel {
	MODEL_SKY = 0,		// �X�J�C �h�[��
	MODEL_PLAYER,		// �v���C���[ ���f��
	MODEL_ENEMY,		// �G���f��
	MODEL_MISSILE,		// �~�T�C��

	MAX_MODEL
};

class CExplosion;
class CModel : public CGameObj
{
private:
	static CAssimpModel* m_pModels[MAX_MODEL];
	CAssimpModel* m_pModel;

protected:
	CExplosion* m_pExp;	// �����G�t�F�N�g
	UINT m_uExpTimer;	// �������^�C�}�[

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
