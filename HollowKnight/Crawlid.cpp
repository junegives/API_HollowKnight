#include "pch.h"
#include "Crawlid.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Tile.h"
#include "CameraMgr.h"
#include "Geo.h"
#include "Player.h"

void CCrawlid::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidWALK_L.bmp", L"CrawlidWALK_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidWALK_R.bmp", L"CrawlidWALK_R");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidTURN_L.bmp", L"CrawlidTURN_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidTURN_R.bmp", L"CrawlidTURN_R");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidDEAD_L.bmp", L"CrawlidDEAD_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/CrawlidDEAD_R.bmp", L"CrawlidDEAD_R");

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 110.f, 80.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 행동 관리
	{
		m_fSpeed = 2.f;
		m_bDead = false;
		m_iHP = 5;
		m_iMaxInvincibleTime = 20;
		m_iInvincibleTime = 0;
		m_eCurState = EMonsterState::MOVE;
		m_bLeft = true;
		m_bPreLeft = true;
	}

	// 이미지 관리
	{
		m_tSize = { 151.f, 107.f };
		m_pFrameKey = L"CrawlidWALK_L";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount64();
	}

	__super::Initialize();
}

int CCrawlid::Update()
{
	if (isOnGravity())
		m_tPosition = m_tPosition - m_tVel;

	if (500.f >= CPlayer::GetInstance()->GetPosition().Distance(m_tPosition))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"M_Crawlid.wav", EChannelID::MONSTER, g_fVolume);
	}

	MotionChange();
	__super::Update();

	return (m_eCurState == EMonsterState::DEAD);
}

void CCrawlid::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);

	switch (m_eCurState)
	{
	case EMonsterState::IDLE:
		break;

	case EMonsterState::MOVE:
		MonsterMove();
		break;

	case EMonsterState::JUMP:
		//PlayerJump();
		break;

	case EMonsterState::DASH:
		break;

	case EMonsterState::SLASH:
		break;

	case EMonsterState::SHOOT_TOP:
		//PlayerShoot();
		break;

	case EMonsterState::SHOOT_BOTTOM:
		//PlayerShoot();
		break;

	case EMonsterState::DAMAGED:
		break;

	case EMonsterState::STUN:
		//PlayerStun();
		break;

	case EMonsterState::DEAD:
		CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
		break;

	default:
		break;
	}

	__super::LateUpdate();
}

void CCrawlid::Render(HDC _hdc)
{

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

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

void CCrawlid::Release()
{
	SAFE_DELETE(m_cHitBox);
	__super::Release();
}

void CCrawlid::MotionChange()
{
	m_ePreState;
	m_eCurState;

	if (m_ePreState != m_eCurState || m_bPreLeft != m_bLeft)
	{
		switch (m_eCurState)
		{
		case EMonsterState::IDLE:
			break;

		case EMonsterState::MOVE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
			if (m_bLeft) m_pFrameKey = L"CrawlidWALK_L";
			else m_pFrameKey = L"CrawlidWALK_R";
			m_tSize = { 151.f, 107.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::DAMAGED:
			break;

		case EMonsterState::STUN:
			break;

		case EMonsterState::DEAD:
			break;

		case EMonsterState::ENUM_END:
			break;

		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

	m_bPreLeft = m_bLeft;
}

void CCrawlid::OnCollided(CObject* _pObject)
{
}

void CCrawlid::OnCollided(CObject* _pObject, EDirection _eDirection)
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
				m_fDt = 0.f;
				m_tVel = { 0.f, 0.f };
				m_tPosition.m_fY = _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2- m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::DOWN:
				break;


			case EDirection::LEFT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX - _pObject->GetSize().m_fX / 2 - m_cHitBox->GetSize().m_fX / 2;
				m_bPreLeft = m_bLeft;
				m_bLeft = !m_bLeft;
				break;

			case EDirection::RIGHT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX + _pObject->GetSize().m_fX / 2 + m_cHitBox->GetSize().m_fX / 2;
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

		m_iDamageTime = 0;
		m_bDamage = true;

		if (!m_isKnockBack)

			if (setDamage(1))
			{
				CPlayer::GetInstance()->gainSoul(10);
				m_tFrame.iMotion = 1;
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
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTEREFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDead.wav", EChannelID::MONSTEREFFECT, g_fVolume);
				// 뒤로 많이 밀려나면서 중력받으면서
				// 다잉 모션
				m_eCurState = EMonsterState::DEAD;
				m_onGravity = true;

				// 히트박스 제거

				/*if (m_cHitBox)
					dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);*/

				// 지오 생성
				CSoundMgr::Get_Instance()->StopSound(EChannelID::GEO);
				CSoundMgr::Get_Instance()->PlaySound(L"G_GeoRock1.wav", EChannelID::GEO, g_fVolume);

				CObject* pGeo1 = new CGeo(1);
				CObject* pGeo2 = new CGeo(1);
				CObject* pGeo3 = new CGeo(5);
				CObject* pGeo4 = new CGeo(5);
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