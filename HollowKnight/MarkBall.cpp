#include "pch.h"
#include "MarkBall.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "Player.h"

CMarkBall::CMarkBall()
{
}

CMarkBall::~CMarkBall()
{
}

void CMarkBall::Initialize()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::PROJECTILE;
		m_eRender = ERenderID::DEBUG_UI;
	}

	// 히트 박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 70.f, 70.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 행동 관리
	{
		m_fSpeed = 20.f;
		m_iTime = 0;
		m_bDead = false;
	}

	CProjectile::Initialize();
}

int CMarkBall::Update()
{

	// 플레이어 위치 계산해서 회전만
	// 히트박스도 같이 회전
	if (m_iTime == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTERSKILL);
		CSoundMgr::Get_Instance()->PlaySound(L"B_SwordAppear.wav", EChannelID::MONSTERSKILL, g_fVolume);
	}

	else if (m_iTime < 70.f)
	{
		if (m_eProjectileType == EProjectileType::BALL)
		{
			m_vDir = CPlayer::GetInstance()->GetPosition() - m_tPosition;
		}
	}

	else if (m_iTime == 70.f)
	{
		// 소리 넣기
		CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTERSKILL);
		CSoundMgr::Get_Instance()->PlaySound(L"B_SwordShoot.wav", EChannelID::MONSTERSKILL, g_fVolume);
		m_vDir.Normalize();
	}

	// 플레이어 향해서 이동
	else if (m_iTime < 300.f)
	{
		SetPosition({ m_tPosition + m_vDir * 15.f });
	}

	// n초 후 소멸
	else
	{
		m_bDead = true;
	}

	m_cHitBox->SetPosition(m_tPosition);
	++m_iTime;

	return m_bDead;
}

void CMarkBall::LateUpdate()
{
	__super::Move_Frame();
}

void CMarkBall::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값
}

void CMarkBall::Release()
{
	SAFE_DELETE(m_cHitBox);
}

void CMarkBall::OnCollided(CObject* _pObject)
{
}

void CMarkBall::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}