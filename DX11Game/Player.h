// �v���C���[ [Player.h]
#pragma once
#include "Model.h"

class CPlayer : public CModel
{
public:
	CPlayer(CScene* pScene); // �R���X�g���N�^
	virtual ~CPlayer();		 // �f�X�g���N�^

	virtual HRESULT Init();	 // ������
	virtual void Fin();		 // �I������
	virtual void Update();	 // �X�V
};
