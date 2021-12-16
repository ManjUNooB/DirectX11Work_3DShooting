// �G�@ [Enemy.h]
#pragma once
#include "Model.h"

class CPlayer;
class CEnemy : public CModel
{
private:
	CPlayer* m_pPlayer;

public:
	CEnemy(CScene* pScene);		// �R���X�g���N�^
	virtual ~CEnemy();			// �f�X�g���N�^

	virtual HRESULT Init();		// ������
	virtual void Fin();			// �I������
	virtual void Update();		// �X�V

	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
};
