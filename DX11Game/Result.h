//=============================================================================
//
// リザルト画面クラス定義 [Result.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Scene.h"

// クラス定義
class CResult : public CScene
{
private:
	bool m_bStart;
	ID3D11ShaderResourceView* m_pTexResult;
	ID3D11ShaderResourceView* m_pTexStart;
	ID3D11ShaderResourceView* m_pTexBG;
	int m_nTimer;

public:
	CResult();
	virtual ~CResult();

	virtual bool Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
};
