// �v���C���[ [Player.cpp]
#include "Player.h"
#include "Input.h"
#include "Missile.h"
#include "DebugProc.h"

// �萔
namespace {
	const float g_fSpeed = 10.0f;
	const float g_fRollSpeed = 4.0f;//�P��:�x
	const float g_fPitchSpeed = 2.0f;//�P��:�x
}

// �R���X�g���N�^
CPlayer::CPlayer(CScene* pScene) : CModel(pScene)
{
	SetID(GOT_PLAYER);
}

// �f�X�g���N�^
CPlayer::~CPlayer()
{
}

// ������
HRESULT CPlayer::Init()
{
	SetModel(MODEL_PLAYER);
	

	return CModel::Init();
}

// �I������
void CPlayer::Fin()
{
	CModel::Fin();
}

// �X�V
void CPlayer::Update()
{
	// ���[���h�ϊ��s��擾
	XMFLOAT4X4 mW = GetWorld();
	// ���f�����W���擾
	XMFLOAT3 vX = XMFLOAT3(mW._11, mW._12, mW._13);
	XMFLOAT3 vY = XMFLOAT3(mW._21, mW._22, mW._23);
	XMFLOAT3 vZ = XMFLOAT3(mW._31, mW._32, mW._33);
	// ���W�擾�A�N���A
	m_vPos = XMFLOAT3(mW._41, mW._42, mW._43);
	mW._41 = mW._42 = mW._43 = 0.0f;

	// �s�b�`
	XMMATRIX mR = XMMatrixIdentity();
	if (CInput::GetKeyPress(VK_W) || CInput::GetKeyPress(VK_UP)) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(g_fPitchSpeed));
	}
	if (CInput::GetKeyPress(VK_S) || CInput::GetKeyPress(VK_DOWN)) {
		mR = XMMatrixRotationAxis(XMLoadFloat3(&vX), XMConvertToRadians(-g_fPitchSpeed));
	}
	// ���[��
	if (CInput::GetKeyPress(VK_A) || CInput::GetKeyPress(VK_LEFT)) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(g_fRollSpeed)));
	}
	if (CInput::GetKeyPress(VK_D) || CInput::GetKeyPress(VK_RIGHT)) {
		mR = XMMatrixMultiply(mR, XMMatrixRotationAxis(XMLoadFloat3(&vZ), XMConvertToRadians(-g_fRollSpeed)));
	}
	XMStoreFloat4x4(&mW, XMMatrixMultiply(XMLoadFloat4x4(&mW), mR));

	// �O�i
	if (CInput::GetKeyPress(VK_LCONTROL)) {
		m_vPos.x += vZ.x * g_fSpeed;
		m_vPos.y += vZ.y * g_fSpeed;
		m_vPos.z += vZ.z * g_fSpeed;
	}

	// ���[���h�ϊ��s��ɔ��f
	mW._41 = m_vPos.x;
	mW._42 = m_vPos.y;
	mW._43 = m_vPos.z;
	SetWorld(mW);

	// �ǔ��~�T�C������
	if (CInput::GetKeyTrigger(VK_SPACE)) {
		CMissile::Fire(&mW);
	}

	CModel::Update();

	// �f�o�b�O�\��
	CDebugProc::Print("*** ��ڲ԰ ***\n");
	CDebugProc::Print("Pitch:[W][S]\n");
	CDebugProc::Print("Forward[LShift]\n");
	CDebugProc::Print("Roll:[A][D]\n");
	CDebugProc::Print("Guided Missile:[M]\n");
	CDebugProc::Print("\n");
}
