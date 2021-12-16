//=============================================================================
//
// �V�[�� �N���X��` [Scene.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once
#include "Camera.h"
#include "Light.h"

// �萔��`
enum EScene {
	SCENE_NONE = 0,		// (�V�[����)
	SCENE_TITLE,		// �^�C�g�����
	SCENE_TUTORIAL,		//�`���[�g���A��
	SCENE_GAME,			// �Q�[�����
	SCENE_RESULT,		//���U���g

	MAX_SCENE
};

// �N���X��`
class CGameObj;
class CScene {
protected:
	EScene m_id;
	CGameObj* m_pObj;

private:
	static CScene* m_pScene;
	static CScene* m_pTop;
	CScene* m_pBack;
	CScene* m_pNext;

	CCamera* m_pCamera;
	CCamera m_camera;
	CLight* m_pLight;
	CLight m_lightOff;

public:
	CScene();
	virtual ~CScene();

	virtual bool Init();
	virtual void Fin();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static bool InitAll();
	static void FinAll();
	static void UpdateAll();
	static void DrawAll();

	static void Change(EScene scene);

	CGameObj* GetObj() { return m_pObj; }
	void SetObj(CGameObj* pObj) { m_pObj = pObj; }
	CGameObj* Find(int id = -1, CGameObj* pStart = nullptr);

	CLight* GetLight() { return m_pLight; }
	void SetLight(CLight* pLight);
	CCamera* GetCamera() { return m_pCamera; }
	void SetCamera(CCamera* pCamera);

	static CScene* GetCurrent() { return m_pScene; }
};
