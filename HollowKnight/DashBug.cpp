#include "pch.h"
#include "DashBug.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Tile.h"
#include "CameraMgr.h"
#include "Geo.h"
#include "Skill.h"
#include "Player.h"

void CDashBug::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugIDLE_L.bmp", L"DashBugIDLE_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugIDLE_R.bmp", L"DashBugIDLE_R");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugRUN_L.bmp", L"DashBugRUN_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugRUN_R.bmp", L"DashBugRUN_R");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugDEAD_L.bmp", L"DashBugDEAD_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/DashBugDEAD_R.bmp", L"DashBugDEAD_R");

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 100.f, 100.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 행동 관리
	{
		m_fSpeed = 4.f;
		m_bDead = false;
		m_iHP = 7;
		m_iMaxInvincibleTime = 20;
		m_iInvincibleTime = 0;
		m_eCurState = EMonsterState::MOVE;
		m_bLeft = true;
		m_bPreLeft = true;
	}

	// 이미지 관리
	{
		m_tSize = { 150.f, 150.f };
		m_pFrameKey = L"DashBugIDLE_L";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount64();
	}

	__super::Initialize();
}

int CDashBug::Update()
{
	if (isOnGravity())
		m_tPosition = m_tPosition - m_tVel;

	if (500.f >= CPlayer::GetInstance()->GetPosition().Distance(m_tPosition))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"M_DashBugRun.wav", EChannelID::MONSTER, g_fVolume);
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

	MotionChange();
	__super::Update();

	return (m_eCurState == EMonsterState::DEAD);
}

void CDashBug::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);

	switch (m_eCurState)
	{
	case EMonsterState::IDLE:
		MonsterIdle();
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

void CDashBug::Render(HDC _hdc)
{
	float	fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float	fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	float renderX = m_tPosition.m_fX - m_tSize.m_fX / 2 + (long)fScrollX;
	float renderY = m_tPosition.m_fY - m_tSize.m_fY / 2 + (long)fScrollY;

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

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

void CDashBug::Release()
{
	SAFE_DELETE(m_cHitBox);
	__super::Release();
}

void CDashBug::MotionChange()
{
	m_ePreState;
	m_eCurState;

	if (m_ePreState != m_eCurState || m_bPreLeft != m_bLeft)
	{
		switch (m_eCurState)
		{
		case EMonsterState::IDLE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			if (m_bLeft) m_pFrameKey = L"DashBugIDLE_L";
			else m_pFrameKey = L"DashBugIDLE_R";

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::MOVE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			if (m_bLeft) m_pFrameKey = L"DashBugRUN_L";
			else m_pFrameKey = L"DashBugRUN_R";

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
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

void CDashBug::OnCollided(CObject* _pObject)
{
}

void CDashBug::OnCollided(CObject* _pObject, EDirection _eDirection)
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
				m_tPosition.m_fY = _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::DOWN:
				break;


			case EDirection::LEFT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX - _pObject->GetSize().m_fX / 2 - m_cHitBox->GetSize().m_fX / 2;
				m_eCurState = EMonsterState::IDLE;
				break;

			case EDirection::RIGHT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX + _pObject->GetSize().m_fX / 2 + m_cHitBox->GetSize().m_fX / 2;
				m_eCurState = EMonsterState::IDLE;
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

		int damage = 1;

		if (dynamic_cast<CSkill*>(_pObject)->isFireBall())
		{
			damage = 3;
		}

		if (!m_isKnockBack)

			// 데미지만 입은 경우
			if (setDamage(damage))
			{
				CPlayer::GetInstance()->gainSoul(10);
				m_tFrame.iMotion = 1;
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
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
				CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTEREFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDead.wav", EChannelID::MONSTEREFFECT, g_fVolume);

				// 뒤로 많이 밀려나면서 중력받으면서
				// 다잉 모션
				m_eCurState = EMonsterState::DEAD;
				m_onGravity = true;

				// 히트박스 제거
				//dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);

				// 지오 생성
				CSoundMgr::Get_Instance()->StopSound(EChannelID::GEO);
				CSoundMgr::Get_Instance()->PlaySound(L"G_GeoRock1.wav", EChannelID::GEO, g_fVolume);

				CObject* pGeo1 = new CGeo(5);
				CObject* pGeo2 = new CGeo(5);
				CObject* pGeo3 = new CGeo(5);
				CObject* pGeo4 = new CGeo(5);
				CObject* pGeo5 = new CGeo(5);

				pGeo1->SetPosition(m_tPosition - 50.f);
				pGeo2->SetPosition(m_tPosition - 30.f);
				pGeo3->SetPosition(m_tPosition);
				pGeo4->SetPosition(m_tPosition + 30.f);
				pGeo5->SetPosition(m_tPosition + 40.f);

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