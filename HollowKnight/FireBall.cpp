#include "pch.h"
#include "FireBall.h"
#include "BmpMgr.h"
#include "Player.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraMgr.h"
#include "Tile.h"
#include "SoundMgr.h"
#include "Effect.h"

void CFireBall::Initialize()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::SKILL;
		m_eRender = ERenderID::EFFECT;
		m_isFireBall = true;
	}

	// 히트 박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition({m_tPosition.m_fX, m_tPosition.m_fY});
		m_cHitBox->SetSize({ 100.f, 100.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 이펙트 관리
	{
		m_pGetEffect = new CEffect;
		m_pGetEffect->SetPosition(m_tPosition);
		m_pGetEffect->SetSize({ 151.f, 205.f });
		m_pGetEffect->setFrameKey(L"FireBallEffect_R", 6, 70);
		m_pGetEffect->Initialize();
	}
}

int CFireBall::Update()
{
	if (m_showEffect)
	{
		if (m_iEffectTime < 10)
		{
			++m_iEffectTime;
		}
		else
		{
			m_showEffect = false;
			m_iEffectTime = 0;
			return (int32)EObjectState::DEAD;
		}
	}
	
	else
	{
		switch ((int)m_eDir)
		{
		case (int)EDirection::LEFT:
			m_bLeft = true;
			SetPosition({ m_tPosition.m_fX - 30.f, m_tPosition.m_fY });
			m_cHitBox->SetPosition({ m_tPosition.m_fX - 80.f, m_tPosition.m_fY });
			m_pGetEffect->setFrameKey(L"FireBallEffect_L", 6, 70);
			break;

		case (int)EDirection::RIGHT:
			m_bLeft = false;
			SetPosition({ m_tPosition.m_fX + 30.f, m_tPosition.m_fY });
			m_cHitBox->SetPosition({ m_tPosition.m_fX + 80.f, m_tPosition.m_fY });
			m_pGetEffect->setFrameKey(L"FireBallEffect_R", 6, 70);
			break;
		}
	}

	return (int32)EObjectState::NODEAD;
}

void CFireBall::LateUpdate()
{
	if (m_showEffect)
		m_pGetEffect->LateUpdate();

	__super::Move_Frame();
}

void CFireBall::Render(HDC _hDC)
{
	if (m_showEffect)
		m_pGetEffect->Render(_hDC);

	if (!m_isVisible) return;

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

void CFireBall::Release()
{
	SAFE_DELETE(m_pGetEffect);
	SAFE_DELETE(m_cHitBox);
}

void CFireBall::OnCollided(CObject* _pObject)
{
	switch (_pObject->GetObjectType())
	{
	// 벽과 충돌
	case EObjectType::TILE:
		if (dynamic_cast<CTile*>(_pObject)->GetTileType() == ETileType::TRIGGER) return;
		//CSoundMgr::Get_Instance()->PlaySound(L"G_GeoSmallGet2.wav", EChannelID::GEO, g_fVolume);
		m_isVisible = false;
		if(m_bLeft)
			m_pGetEffect->SetPosition({ m_tPosition.m_fX - 60.f, m_tPosition.m_fY });
		else
			m_pGetEffect->SetPosition({ m_tPosition.m_fX + 60.f, m_tPosition.m_fY });
		m_showEffect = true;
		break;
	}
}

void CFireBall::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
