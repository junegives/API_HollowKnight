#include "pch.h"
#include "Geo.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Effect.h"
#include "SoundMgr.h"

CGeo::CGeo(int _iAmount)
{
	m_iAmount = _iAmount;
}

void CGeo::Initialize()
{
	m_eObjectType = EObjectType::GEO;
	m_eRender = ERenderID::GAMEOBJECT;
	m_fSpeed = 10.f;

	// 금액별 이미지 관리
	{
		if (5 > m_iAmount)
		{
			m_pFrameKey = L"GeoSmallAir";
			m_tSize = { 28.f, 28.f };
			m_tFrame.iFrameEnd = 8;
		}
		else if (10 > m_iAmount)
		{
			m_pFrameKey = L"GeoMediumAir";
			m_tSize = { 42.f, 41.f };
			m_tFrame.iFrameEnd = 7;
		}
		else
		{
			m_pFrameKey = L"GeoBigAir";
			m_tSize = { 44.f, 44.f };
			m_tFrame.iFrameEnd = 7;
		}
	}

	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount64();
	}

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ m_tSize.m_fX - 5.f, m_tSize.m_fY - 5.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 이펙트 관리
	{
		m_pGetEffect = new CEffect;
		m_pGetEffect->SetPosition(m_tPosition);
		m_pGetEffect->SetSize({ 44.f, 105.f });
		m_pGetEffect->setFrameKey(L"GeoGet", 3, 70);
		m_pGetEffect->Initialize();
	}
}

int CGeo::Update()
{
	// 종단속도 지정
	if (m_fDt < 0.05f)
	{
		m_fDt += 0.001f;
		m_tVel = m_tVel + m_tGravity * m_fDt;
	}

	if (isOnGravity())
		m_tPosition = m_tPosition - m_tVel;

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
			//dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);
			return (int32)EObjectState::DEAD;
		}
	}

	return (int32)EObjectState::NODEAD;
}

void CGeo::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);

	if (m_showEffect)
		m_pGetEffect->LateUpdate();

	__super::Move_Frame();
}

void CGeo::Render(HDC _hDC)
{
	if (m_showEffect)
		m_pGetEffect->Render(_hDC);

	if (m_isDeleted) return;

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

void CGeo::Release()
{
	SAFE_DELETE(m_cHitBox);
	SAFE_DELETE(m_pGetEffect);
}

void CGeo::OnCollided(CObject* _pObject)
{
	// 플레이어와 충돌
	switch (_pObject->GetObjectType())
	{
	case EObjectType::PLAYER:
		CSoundMgr::Get_Instance()->PlaySound(L"G_GeoSmallGet2.wav", EChannelID::GEO, g_fVolume);
		m_iAmount = 0;
		m_pGetEffect->SetPosition(m_tPosition);
		m_showEffect = true;
		break;
	}
}

void CGeo::OnCollided(CObject* _pObject, EDirection _eDirection)
{
	switch (_pObject->GetObjectType())
	{
		// 타일과 충돌
	case EObjectType::TILE:

		switch (_eDirection)
		{
			case EDirection::UP:
				m_fDt = 0.f;
				m_tVel = { 0.f, 0.f };
				m_tPosition.m_fY = _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::DOWN:
			case EDirection::LEFT:
			case EDirection::RIGHT:
				break;
		}
	}
}
