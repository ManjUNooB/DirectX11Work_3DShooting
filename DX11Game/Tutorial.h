//=============================================================================
//
// チュートリアル画面クラス定義 [Tutorial.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Scene.h"

// クラス定義
class CTutorial : public CScene
{
private:
	bool m_bStart;
	ID3D11ShaderResourceView* m_pTexTutorial;
	ID3D11ShaderResourceView* m_pTexStart;
	ID3D11ShaderResourceView* m_pTexBG;
	int m_nTimer;

public:
	CTutorial();
	virtual ~CTutorial();

	virtual bool Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
};
