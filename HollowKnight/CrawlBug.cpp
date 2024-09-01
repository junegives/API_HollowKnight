#include "pch.h"
#include "CrawlBug.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SoundMgr.h"
#include "CameraMgr.h"
#include "Geo.h"
#include "Player.h"
#include "Tile.h"

void CCrawlBug::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlBug.bmp", L"CrawlBug");

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({70.f, 70.f});
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	{
		m_fSpeed = 3.f;
		m_bDead = false;
		m_iHP = 5;
		m_iMaxInvincibleTime = 20;
		m_iInvincibleTime = 0;
	}

	// 이미지 관리
	{
		m_pFrameKey = L"CrawlBug";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount64();
	}

	__super::Initialize();
}

int CCrawlBug::Update()
{
	//MotionChange();
	__super::Update();

	if (500.f >= CPlayer::GetInstance()->GetPosition().Distance(m_tPosition))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"M_Crawlid.wav", EChannelID::MONSTER, g_fVolume);
	}

	if (m_isInvincible)
	{
		if (m_iInvincibleTime > 18)
		{
			m_isInvincible = false;
			m_iInvincibleTime = 0;
		}
		m_iInvincibleTime++;
	}

	return (m_eCurState == EMonsterState::DEAD);
}

void CCrawlBug::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);
	__super::LateUpdate();
}

void CCrawlBug::Render(HDC _hdc)
{

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CCameraMgr::GetInstance()->GetRenderPos(m_tPosition);

	GdiTransparentBlt(_hdc,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		m_tFrame.iMotion * (int)m_tSize.m_fY,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값

	__super::Render(_hdc);

	m_tFrame.iMotion = 0;
}

void CCrawlBug::Release()
{
	SAFE_DELETE(m_cHitBox);
	__super::Release();
}

void CCrawlBug::MotionChange()
{
}

void CCrawlBug::OnCollided(CObject* _pObject)
{
}

void CCrawlBug::OnCollided(CObject* _pObject, EDirection _eDirection)
{
	switch (_pObject->GetObjectType())
	{
	case EObjectType::TILE:

		switch (dynamic_cast<CTile*>(_pObject)->GetTileType())
		{
		case ETileType::GROUND:
		case ETileType::WALL:
			switch (_eDirection)
			{
			case EDirection::UP:
				m_onGravity = false;
				m_fDt = 0.f;
				m_tVel = { 0.f, 0.f };
				m_tPosition.m_fY = _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::DOWN:
				break;

			case EDirection::LEFT:
			case EDirection::RIGHT:
				m_bPreLeft = m_bLeft;
				m_bLeft = !m_bLeft;
				break;
			}
			break;

		case ETileType::OBSTACLE:
			break;
		}
		break;

	case EObjectType::SKILL:

		if (m_bDelayTime) return;

		m_iDelayTime = 0;
		m_bDelayTime = true;

		if (!m_isKnockBack)

			// 데미지만 입은 경우
			if (setDamage(1))
			{
				CPlayer::GetInstance()->gainSoul(10);
				// 데미지 이펙트 생성
				m_pHitCrack->SetPosition(m_tPosition);
				m_pHitCrack->SetSize({ 699.f, 140.f });
				m_pHitCrack->setFrameKey(L"HitCrack", 2, 70);
				m_showEffect = true;
				m_iEffectTime = 0;
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTEREFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDamage.wav", EChannelID::MONSTEREFFECT, g_fVolume);

				// 넉백
				SetKnockBack(true, _eDirection);
			}

			// 죽은 경우
			else
			{
				CPlayer::GetInstance()->gainSoul(10);
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTEREFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDead.wav", EChannelID::MONSTEREFFECT, g_fVolume);
				// 뒤로 많이 밀려나면서 중력받으면서
				// 다잉 모션
				m_eCurState = EMonsterState::DEAD;
				
				// 히트박스 제거
				//dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);
				
				// 지오 생성
				CSoundMgr::Get_Instance()->StopSound(EChannelID::GEO);
				CSoundMgr::Get_Instance()->PlaySound(L"G_GeoRock1.wav", EChannelID::GEO, g_fVolume);

				CObject* pGeo1 = new CGeo(1);
				CObject* pGeo2 = new CGeo(1);
				CObject* pGeo3 = new CGeo(1);
				CObject* pGeo4 = new CGeo(1);
				CObject* pGeo5 = new CGeo(5);

				pGeo1->SetPosition(m_tPosition - 50.f);
				pGeo2->SetPosition(m_tPosition);
				pGeo3->SetPosition(m_tPosition);
				pGeo4->SetPosition(m_tPosition);
				pGeo5->SetPosition(m_tPosition);

				pGeo1->Initialize();
				pGeo2->Initialize();
				pGeo3->Initialize();
				pGeo4->Initialize();
				pGeo5->Initialize();

				SCENE->GetCurrentScene()->AddObject(pGeo1);
				SCENE->GetCurrentScene()->AddObject(pGeo2);
				SCENE->GetCurrentScene()->AddObject(pGeo3);
				SCENE->GetCurrentScene()->AddObject(pGeo4);
				SCENE->GetCurrentScene()->AddObject(pGeo5);
			}
		break;
	}
}

//void CPlayer::MotionChange()
//{
//	m_ePreState;
//	m_eCurState;
//
//	if (m_ePreState != m_eCurState)
//	{
//		switch (m_eCurState)
//		{
//		case EPlayerState::IDLE:
//			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
//			if (m_bLeft) m_pFrameKey = L"PlayerIDLE_L";
//			else m_pFrameKey = L"PlayerIDLE_R";
//			m_tSize = { 60.f,125.f };
//
//			m_tFrame.iFrameStart = 0;
//			m_tFrame.iFrameEnd = 8;
//			m_tFrame.iMotion = 0;
//			m_tFrame.dwSpeed = 70;
//			m_tFrame.dwTime = GetTickCount64();
//
//			break;
//
//		//case EPlayerState::MOVE:
//		//	CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
//
//		//	m_tSize = { 86.f,130.f };
//
//		//	m_tFrame.iFrameStart = 0;
//		//	m_tFrame.iFrameEnd = 12;
//		//	m_tFrame.iMotion = 0;
//		//	m_tFrame.dwSpeed = 70;
//		//	m_tFrame.dwTime = GetTickCount64();
//
//		//	break;
//
//		//case EPlayerState::JUMP:
//		//	CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
//		//	CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerJump.wav", EChannelID::MOVEMENT, g_fVolume);
//
//		//	if (m_bLeft) m_pFrameKey = L"PlayerAIRBORN_L";
//		//	else m_pFrameKey = L"PlayerAIRBORN_R";
//		//	m_tSize = { 100.f ,142.f };
//
//		//	m_tFrame.iFrameStart = 0;
//		//	m_tFrame.iFrameEnd = 11;
//		//	m_tFrame.iMotion = 0;
//		//	m_tFrame.dwSpeed = 70;
//		//	m_tFrame.dwTime = GetTickCount64();
//
//		//	break;
//
//		//case EPlayerState::DOUBLEJUMP:
//		//	CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
//		//	CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerWing.wav", EChannelID::MOVEMENT, g_fVolume);
//
//		//	if (m_bLeft) m_pFrameKey = L"PlayerDOUBLEJUMP_L";
//		//	else m_pFrameKey = L"PlayerDOUBLEJUMP_R";
//		//	m_tSize = { 137.f ,150.f };
//
//		//	m_tFrame.iFrameStart = 0;
//		//	m_tFrame.iFrameEnd = 7;
//		//	m_tFrame.iMotion = 0;
//		//	m_tFrame.dwSpeed = 70;
//		//	m_tFrame.dwTime = GetTickCount64();
//
//		//	break;
//
//		//case EPlayerState::FALL:
//		//	CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
//
//		//	if (m_bLeft) m_pFrameKey = L"PlayerFALL_L";
//		//	else m_pFrameKey = L"PlayerFALL_R";
//		//	m_tSize = { 91.f, 135.f };
//
//		//	m_tFrame.iFrameStart = 0;
//		//	m_tFrame.iFrameEnd = 5;
//		//	m_tFrame.iMotion = 0;
//		//	m_tFrame.dwSpeed = 70;
//		//	m_tFrame.dwTime = GetTickCount64();
//
//		//	break;
//
//		//case EPlayerState::DASH:
//		//	CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
//		//	CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerDash.wav", EChannelID::SKILL, g_fVolume);
//
//		//	if (m_bLeft) m_pFrameKey = L"PlayerDASH_L";
//		//	else m_pFrameKey = L"PlayerDASH_R";
//		//	m_tSize = { 192.f, 117.f };
//
//		//	m_tFrame.iFrameStart = 0;
//		//	m_tFrame.iFrameEnd = 10;
//		//	m_tFrame.iMotion = 0;
//		//	m_tFrame.dwSpeed = 70;
//		//	m_tFrame.dwTime = GetTickCount64();
//
//		//	break;
//
//		}
//
//		m_ePreState = m_eCurState;
//	}
//}