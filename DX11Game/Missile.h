// ’Ç”öƒ~ƒTƒCƒ‹ [Missile.h]
#pragma once
#include "Model.h"

class CEnemy;
class CMissile : public CModel
{
private:
	CEnemy* m_pTarget;
	int m_nLife;

public:
	CMissile(CScene* pScene);
	virtual ~CMissile();

	virtual HRESULT Init();
	virtual void Update();

	static int Fire(XMFLOAT4X4* pWorld, CEnemy* pEnemy = nullptr);
};
