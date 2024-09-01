#include "pch.h"
#include "MantisLord.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ScrollMgr.h"
#include "CameraMgr.h"
#include "Tile.h"
#include "SoundMgr.h"
#include "MantisTown.h"
#include "Boomerang.h"
#include "Geo.h"
#include "Player.h"
#include "Skill.h"

CMantisLord::CMantisLord()
{
}

CMantisLord::~CMantisLord()
{
}

void CMantisLord::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.

	// 이미지 추가
	{
		// IDLE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordIDLE.bmp", L"LordIDLE");

		// STAND
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSTAND.bmp", L"LordSTAND");

		// GESTURE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordGESTURE1.bmp", L"LordGESTURE1");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordGESTURE2.bmp", L"LordGESTURE2");

		// LEAVE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordLEAVE.bmp", L"LordLEAVE");

		// DASH
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASHBeforeL.bmp", L"LordDASHBEFORE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASHBeforeR.bmp", L"LordDASHBEFORE_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASH_L.bmp", L"LordDASH_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASH_R.bmp", L"LordDASH_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASHAfterL.bmp", L"LordDASHAFTER_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDASHAfterR.bmp", L"LordDASHAFTER_R");
		
		// WALL (THROW)
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOTBEFORE_L.bmp", L"LordSHOOTBEFORE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOTBEFORE_R.bmp", L"LordSHOOTBEFORE_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOT_L.bmp", L"LordSHOOT_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOT_R.bmp", L"LordSHOOT_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOTAFTER_L.bmp", L"LordSHOOTAFTER_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSHOOTAFTER_R.bmp", L"LordSHOOTAFTER_R");
		
		// SMASH
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSMASHBEFORE.bmp", L"LordSMASHBEFORE");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSMASH.bmp", L"LordSMASH");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSMASHAFTER.bmp", L"LordSMASHAFTER");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSMASHLEAVE.bmp", L"LordSMASHLEAVE");

		// DEAD
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordDEAD.bmp", L"LordDEAD");
		// SIT
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordSIT.bmp", L"LordSIT");

		// BOW
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordBOW.bmp", L"LordBOW");
	}

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize(m_tSize);
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 행동 관리
	{
		m_onGravity = false;
		m_fSpeed = 10.f;
		m_bDead = false;
		m_iHP = 5;
		m_eCurState = EMonsterState::IDLE;
		m_bLeft = true;
		m_bPreLeft = true;
	}

	// 이미지 관리
	{
		m_pFrameKey = L"LordIDLE";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200;
		m_tFrame.dwTime = GetTickCount64();
	}

	// 위치 관리
	{
		m_tOriginSize = m_tSize;
		m_tOriginPosition = m_tPosition;
	}

	CBoss::Initialize();
}

int CMantisLord::Update()
{
	MotionChange();

	CBoss::Update();
	return (int32)EObjectState::NODEAD;
}

void CMantisLord::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);
	m_bBlockMotionChange = false;

	switch (m_eCurState)
	{
	case EMonsterState::IDLE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordIdle();
		m_cHitBox->SetCanCollision(false);
		break;

	case EMonsterState::STAND:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordStand();
		break;

	case EMonsterState::LEAVE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordLeave();
		break;

	case EMonsterState::NOTVISIBLE:
		m_bBlockMotionChange = true;
		LordNotVisible();
		break;

	case EMonsterState::SIT:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordSit();
		m_cHitBox->SetCanCollision(false);
		break;

	case EMonsterState::DASH_BEFORE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordDashBEFORE();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::DASH:
		m_bBlockMotionChange = false;
		LordDash();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::DASH_AFTER:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordDashAFTER();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SLASH_BEFORE:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordSmashBEFORE();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SLASH:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordSmash();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SLASH_AFTER:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordSmashAFTER();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::WALL_TOP:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordWallTOP();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::WALL_BOTTOM:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordWallBOTTOM();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SHOOT_TOP:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordThrowTOP();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SHOOT_BOTTOM:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordThrowBOTTOM();
		m_cHitBox->SetCanCollision(true);
		break;

	case EMonsterState::SHOOT_AFTER:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordThrowAFTER();
		m_cHitBox->SetCanCollision(false);
		break;

	case EMonsterState::DAMAGED:
		break;

	case EMonsterState::DEAD:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		LordDead();
		m_cHitBox->SetCanCollision(false);
		break;

	case EMonsterState::NOTHING:
		m_bBlockMotionChange = true;
		m_cHitBox->SetCanCollision(false);
		break;

	default:
		break;
	}


	if (!m_bBlockMotionChange)
		__super::Move_Frame();

	CBoss::LateUpdate();
}

void CMantisLord::Render(HDC _hdc)
{
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
		RGB(255, 0, 255));	// 제거하고자 하는 색상값

	CBoss::Render(_hdc);

	m_tFrame.iMotion = 0;
}


void CMantisLord::Release()
{
	SAFE_DELETE(m_cHitBox);
	__super::Release();
}

void CMantisLord::MotionChange() 

{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case EMonsterState::IDLE:
			// 죽었으면 BOW로, 아니면 IDLE
			// BOW던 IDLE이던 한 번만 moveframe 돌고 m_bBlockMotionChange로 막아버리기
			m_cHitBox->SetCanCollision(false);
			m_tPosition = m_tOriginPosition;

			// BOW
			if (dynamic_cast<CMantisTown*>(SCENE->GetCurrentScene())->GetBossComplete())
			{
				m_tSize = { 116.f, 478.f };

				m_pFrameKey = L"LordBOW";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount64();
			}

			// IDLE
			else
			{
				m_tSize = m_tOriginSize;

				m_pFrameKey = L"LordIDLE";
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();

				m_cHitBox->SetCanCollision(false);
			}
			break;

		case EMonsterState::STAND:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSSEFFECT);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			m_pFrameKey = L"LordSTAND";
			m_tSize = { 102.f, 472.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			m_cHitBox->SetCanCollision(false);
			break;

		case EMonsterState::LEAVE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::BOSS, g_fVolume);
			m_pFrameKey = L"LordLEAVE";
			m_tSize = { 214.f, 564.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 20;
			m_tFrame.dwTime = GetTickCount64();

			m_cHitBox->SetCanCollision(false);
			break;

		case EMonsterState::NOTVISIBLE:
			m_tSize = { 0.f, 0.f };
			m_cHitBox->SetCanCollision(false);
			break;

		case EMonsterState::DASH_BEFORE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDashBefore.wav", EChannelID::BOSS, g_fVolume);
			// 0, 1 랜덤값 받아서 좌우 정하기
			if(m_isSolo)
				m_isLeft = rand() % 2;
			if (m_isLeft)
			{
				m_pFrameKey = L"LordDASHBEFORE_L";
				m_tPosition = { 2300.f, 2300.f };
			}
			else
			{
				m_pFrameKey = L"LordDASHBEFORE_R";
				m_tPosition = { 1300.f, 2300.f };
			}
			m_tSize = { 531.f, 557.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::DASH:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDash.wav", EChannelID::BOSS, g_fVolume);
			if (m_isLeft)
			{
				m_pFrameKey = L"LordDASH_L";
			}
			else
			{
				m_pFrameKey = L"LordDASH_R";
			}
			m_tPosition.m_fY += 160.f;
			m_tSize = { 584.f, 188.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::DASH_AFTER:

			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			if (m_isLeft)
			{
				m_pFrameKey = L"LordDASHAFTER_L";
			}
			else
			{
				m_pFrameKey = L"LordDASHAFTER_R";
			}
			m_tPosition.m_fY -= 200.f;
			m_tSize = { 598.f, 557.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SLASH_BEFORE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordArrive.wav", EChannelID::BOSS, g_fVolume);
			// 랜덤 위치 정하기
			if (m_isSolo) m_tPosition.m_fX = CPlayer::GetInstance()->GetPosition().m_fX;
			else
			{
				if (m_isLeft) m_tPosition.m_fX = CPlayer::GetInstance()->GetPosition().m_fX - 100;
				else m_tPosition.m_fX = CPlayer::GetInstance()->GetPosition().m_fX + 100;
			}
			//m_tPosition.m_fX = rand() % 600 + 1300;
			m_tPosition.m_fY = 1800.f;

			m_pFrameKey = L"LordSMASHBEFORE";

			m_tSize = { 766.f, 643.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SLASH:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordSmash.wav", EChannelID::BOSS, g_fVolume);
			m_tPosition.m_fX += 50.f;
			m_pFrameKey = L"LordSMASH";
			m_tSize = { 121.f, 627.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SLASH_AFTER:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordSmashImpact.wav", EChannelID::BOSS, g_fVolume);
			m_pFrameKey = L"LordSMASHAFTER";
			m_tSize = { 554.f, 523.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::WALL_TOP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDashBefore.wav", EChannelID::BOSS, g_fVolume);
			// 0, 1 랜덤값 받아서 좌우 정하기
			if (m_isSolo)
				m_isLeft = rand() % 2;
			if (m_isLeft)
			{
				m_pFrameKey = L"LordSHOOTBEFORE_L";
				m_tPosition = { 1300.f, 2200.f };
			}
			else
			{
				m_pFrameKey = L"LordSHOOTBEFORE_R";
				m_tPosition = { 2400.f, 2200.f };
			}
			m_tSize = { 610.f, 790.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::WALL_BOTTOM:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDashBefore.wav", EChannelID::BOSS, g_fVolume);
			// 0, 1 랜덤값 받아서 좌우 정하기
			if (m_isSolo)
				m_isLeft = rand() % 2;
			if (m_isLeft)
			{
				m_pFrameKey = L"LordSHOOTBEFORE_L";
				m_tPosition = { 1300.f, 2350.f };
			}
			else
			{
				m_pFrameKey = L"LordSHOOTBEFORE_R";
				m_tPosition = { 2400.f, 2350.f };
			}
			m_tSize = { 610.f, 790.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SHOOT_TOP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			if (m_isLeft)
			{
				m_pFrameKey = L"LordSHOOT_L";
			}
			else
			{
				m_pFrameKey = L"LordSHOOT_R";
			}
			m_tSize = { 610.f, 790.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SHOOT_BOTTOM:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordWallAttack.wav", EChannelID::BOSS, g_fVolume);
			if (m_isLeft)
			{
				m_pFrameKey = L"LordSHOOT_L";
			}
			else
			{
				m_pFrameKey = L"LordSHOOT_R";
			}
			m_tSize = { 610.f, 790.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SHOOT_AFTER:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordLeave.wav", EChannelID::BOSS, g_fVolume);
			if (m_isLeft)
			{
				m_pFrameKey = L"LordSHOOTAFTER_L";
			}
			else
			{
				m_pFrameKey = L"LordSHOOTAFTER_R";
			}
			m_tSize = { 610.f, 790.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::DEAD:
			
			m_pFrameKey = L"LordDEAD";
			m_tSize = { 520.f, 600.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::SIT:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordArrive.wav", EChannelID::BOSS, g_fVolume);
			m_pFrameKey = L"LordSIT";

			m_tPosition = { m_tOriginPosition.m_fX, m_tOriginPosition.m_fY - 100.f };
			m_tSize = { 125.f, 580.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::NOTHING:
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

void CMantisLord::LordIdle()
{
}

void CMantisLord::LordStand()
{
	m_eCurState = EMonsterState::STAND;
}

void CMantisLord::LordLeave()
{
	// Leave time 두고 점점 위로 가게
	m_eCurState = EMonsterState::LEAVE;

	if (m_iLeaveTime < 10)
	{
		m_tPosition.m_fY -= 2 * m_fSpeed;
		m_tPosition.m_fX += m_fSpeed;
		++m_iLeaveTime;
	}
	else
	{
		m_iLeaveTime = 0;
		m_eCurState = EMonsterState::NOTVISIBLE;
	}
}

void CMantisLord::LordDashBEFORE()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 400.f, 200.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 400.f, 200.f });
	}

	if (m_iDashBeforeTime < 80)
	{
		++m_iDashBeforeTime;
	}
	else
	{
		m_iDashBeforeTime = 0;
		m_eCurState = EMonsterState::DASH;
	}
}

void CMantisLord::LordDash()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 50.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 450.f, 200.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 50.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 450.f, 300.f });
	}

	if (m_iDashTime < 15)
	{

		if (m_isLeft)
			m_tPosition.m_fX -= 7 * m_fSpeed;
		else
			m_tPosition.m_fX += 7 * m_fSpeed;

		++m_iDashTime;
	}
	else
	{
		m_iDashTime = 0;
		m_eCurState = EMonsterState::DASH_AFTER;
	}
}

void CMantisLord::LordDashAFTER()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 200.f });
		m_cHitBox->SetSize({ 400.f, 350.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 200.f });
		m_cHitBox->SetSize({ 400.f, 350.f });
	}

	if (m_bBlockMotionChange)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::BOSS, g_fVolume);
		m_eCurState = EMonsterState::NOTVISIBLE;
	}
}

void CMantisLord::LordSmashBEFORE()
{
	if (m_iSmashBeforeTime < 40)
	{
		++m_iSmashBeforeTime;
		m_cHitBox->SetPosition({ m_tPosition.m_fX +  50.f, m_tPosition.m_fY + 50.f});
		m_cHitBox->SetSize({ 200.f, 400.f});
	}
	else
	{
		m_iSmashBeforeTime = 0;
		m_eCurState = EMonsterState::SLASH;
	}
}

void CMantisLord::LordSmash()
{
	if (m_iSmashTime < 8)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 100.f, 400.f });

		m_tPosition.m_fY += 7 * m_fSpeed;
		++m_iSmashTime;
	}
	else
	{
		m_iSmashTime = 0;
		m_eCurState = EMonsterState::SLASH_AFTER;
	}
}

void CMantisLord::LordSmashAFTER()
{
	m_cHitBox->SetPosition({ m_tPosition.m_fX + 50.f, m_tPosition.m_fY - 30.f });
	m_cHitBox->SetSize({ 100.f, 400.f });

	if (m_bBlockMotionChange)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::BOSS, g_fVolume);
		m_eCurState = EMonsterState::NOTVISIBLE;
	}
}

void CMantisLord::LordWallTOP()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 200.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 100.f, 400.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 200.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 100.f, 400.f });
	}

	if (m_iShootBeforeTime < 40)
	{
		++m_iShootBeforeTime;
	}
	else
	{
		m_iShootBeforeTime = 0;
		m_eCurState = EMonsterState::SHOOT_TOP;
	}
}

void CMantisLord::LordWallBOTTOM()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 200.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 100.f, 400.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 200.f, m_tPosition.m_fY + 100.f });
		m_cHitBox->SetSize({ 100.f, 400.f });
	}
	if (m_iShootBeforeTime < 40)
	{
		++m_iShootBeforeTime;
	}
	else
	{
		m_iShootBeforeTime = 0;
		m_eCurState = EMonsterState::SHOOT_BOTTOM;
	}
}

void CMantisLord::LordThrowTOP()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 150.f, m_tPosition.m_fY + 50.f });
		m_cHitBox->SetSize({ 100.f, 350.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 150.f, m_tPosition.m_fY + 50.f });
		m_cHitBox->SetSize({ 100.f, 350.f });
	}
	if (m_iShootTime < 70)
	{
		if (m_iShootTime == 71)
			CSoundMgr::Get_Instance()->PlaySound(L"E_Mantissword.wav", EChannelID::BOSS, g_fVolume);

		++m_iShootTime;

		if (12 == m_iShootTime)
		{
			m_pBoomerang = new CBoomerang;
			m_pBoomerang->SetPosition({ m_tPosition.m_fX + 30.f, m_tPosition.m_fY + 50.f });
			m_pBoomerang->SetSize({ 299.f, 99.f });
			m_pBoomerang->setFrameKey(L"LordBoomerang", 1, 50);
			if (m_isLeft)
				dynamic_cast<CBoomerang*>(m_pBoomerang)->SetDirection(EDirection::LU);
			else
				dynamic_cast<CBoomerang*>(m_pBoomerang)->SetDirection(EDirection::RU);
			m_pBoomerang->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pBoomerang);
		}
		//else if (4 > m_iShootTime)
		//{
		//	if (m_isLeft)
		//	{
		//		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY });
		//		m_cHitBox->SetSize({ 500.f, 250.f });
		//	}
		//	else
		//	{
		//		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY });
		//		m_cHitBox->SetSize({ 500.f, 250.f });
		//	}
		//}
	}
	else
	{
		m_iShootTime = 0;
		m_eCurState = EMonsterState::SHOOT_AFTER;
	}
}

void CMantisLord::LordThrowBOTTOM()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 150.f, m_tPosition.m_fY + 50.f });
		m_cHitBox->SetSize({ 100.f, 350.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 150.f, m_tPosition.m_fY + 50.f });
		m_cHitBox->SetSize({ 100.f, 350.f });
	}
	if (m_iShootTime < 70)
	{
		if (m_iShootTime == 71)
			CSoundMgr::Get_Instance()->PlaySound(L"E_Mantissword.wav", EChannelID::BOSS, g_fVolume);
		++m_iShootTime;

		if (12 == m_iShootTime)
		{
			m_pBoomerang = new CBoomerang;
			m_pBoomerang->SetPosition({ m_tPosition.m_fX + 30.f, m_tPosition.m_fY + 100.f });
			m_pBoomerang->SetSize({ 299.f, 99.f });
			m_pBoomerang->setFrameKey(L"LordBoomerang", 1, 50);
			if (m_isLeft)
				dynamic_cast<CBoomerang*>(m_pBoomerang)->SetDirection(EDirection::LD);
			else
				dynamic_cast<CBoomerang*>(m_pBoomerang)->SetDirection(EDirection::RD);
			m_pBoomerang->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pBoomerang);
		}
	}
	else
	{
		m_iShootTime = 0;
		m_eCurState = EMonsterState::SHOOT_AFTER;
	}
}

void CMantisLord::LordThrowAFTER()
{
	if (m_isLeft)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX - 50.f, m_tPosition.m_fY });
		m_cHitBox->SetSize({ 250.f, 350.f });
	}
	else
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 50.f, m_tPosition.m_fY });
		m_cHitBox->SetSize({ 250.f, 350.f });
	}
	if (m_iShootTime < 20)
	{
		++m_iShootTime;
	}
	else
	{
		m_iShootTime = 0;
		m_eCurState = EMonsterState::NOTVISIBLE;
	}
}

void CMantisLord::LordDead()
{
	if (m_iDeadTime < 200)
	{
		++m_iDeadTime;
	}

	else
	{
		m_iDeadTime = 0;
		m_eCurState = EMonsterState::SIT;
	}
}

void CMantisLord::LordSit()
{
	if (m_iSitTime < 100)
	{
		++m_iSitTime;
	}

	else
	{
		m_iSitTime = 0;
		m_eCurState = EMonsterState::NOTHING;

		// 죽은게 처음 한마리인 경우
		if (m_isSolo)
		{
			dynamic_cast<CMantisTown*>(SCENE->GetCurrentScene())->FirstBossDead();
		}

		// 죽은게 합동공격 보스인 경우
		else
		{
			if (m_iSitTime < 100)
			{
				++m_iSitTime;
			}

			SCENE->GetCurrentScene()->KillBoss();
		}
	}
}

void CMantisLord::LordBow()
{
	m_eCurState = EMonsterState::IDLE;
}

void CMantisLord::LordNotVisible()
{
	m_eCurState = EMonsterState::NOTVISIBLE;

	// 어택 텀 두기
	if (m_iWaitingTime < m_iAttackTerm)
	{
		++m_iWaitingTime;
	}

	// 텀 끝나면 다음 공격 세팅
	else
	{
		// 개인 공격인지
		if (m_isSolo)
		{
			//m_eCurState = (EMonsterState::WALL_TOP);
			//m_eCurState = (EMonsterState::WALL_BOTTOM);
			// 랜덤 돌려서 다음 공격 설정
			m_eCurState = (EMonsterState)(rand() % 4 + 4);
		}

		// 합동 공격인지
		else
		{
			// 합동 공격이면 4, 5, 6, 7, 6, 5, 4, 5, 6, 7, ... 순서로 공격
			m_eCurState = m_eGroupAttack;
			if (EMonsterState::WALL_BOTTOM == m_eGroupAttack)
				m_iGroupAttack = -1;
			else if (EMonsterState::DASH_BEFORE == m_eGroupAttack)
				m_iGroupAttack = 1;
			m_eGroupAttack = (EMonsterState)((int)m_eGroupAttack + m_iGroupAttack);
		}

		m_iWaitingTime = 0;
	}
}

void CMantisLord::OnCollided(CObject* _pObject)
{
}

void CMantisLord::OnCollided(CObject* _pObject, EDirection _eDirection)
{
	switch (_pObject->GetObjectType())
	{
	case EObjectType::TILE:

		/*switch (dynamic_cast<CTile*>(_pObject)->GetTileType())
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
			case EDirection::RIGHT:
				m_bPreLeft = m_bLeft;
				m_bLeft = !m_bLeft;
				break;
			}
			break;

		case ETileType::OBSTACLE:
			break;
		}*/
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

		// 타격
		if (setDamage(damage))
		{
			CPlayer::GetInstance()->gainSoul(10);
			// 하얗게 처리
			m_tFrame.iMotion = 1;

			m_pHitCrack->SetPosition(m_tPosition);
			m_pHitCrack->SetSize({ 699.f, 140.f });
			m_pHitCrack->setFrameKey(L"HitCrack", 2, 70);
			m_showEffect = true;
			m_iEffectTime = 0;
			CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDamage.wav", EChannelID::BOSSEFFECT, g_fVolume);
		}

		// 죽은 경우
		else
		{
			CPlayer::GetInstance()->gainSoul(10);
			m_cHitBox->SetCanCollision(false);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSS);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSSEFFECT);
			// 다잉 모션
			m_eCurState = EMonsterState::DEAD;
			int killCnt = dynamic_cast<CMantisTown*>(SCENE->GetCurrentScene())->GetBossKillCount();
			if (killCnt < 1)
			{
				CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSSEFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDead1.wav", EChannelID::BOSSEFFECT, g_fVolume);
			}
			else if (killCnt < 2)
			{
				CSoundMgr::Get_Instance()->StopSound(EChannelID::BOSSEFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDead2.wav", EChannelID::BOSSEFFECT, g_fVolume);
			}
			else
			{
				CSoundMgr::Get_Instance()->StopAll();
				CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordDead3.wav", EChannelID::BOSSEFFECT, g_fVolume);
				// 여기가 부메랑 타격 없게 만드는 타이밍
				SCENE->GetCurrentScene()->SetBlockProjectile();
			}

			// 지오 생성
			CSoundMgr::Get_Instance()->StopSound(EChannelID::GEO);
			CSoundMgr::Get_Instance()->PlaySound(L"G_GeoRock1.wav", EChannelID::GEO, g_fVolume);

			CObject* pGeo1 = new CGeo(10);
			CObject* pGeo2 = new CGeo(10);
			CObject* pGeo3 = new CGeo(10);
			CObject* pGeo4 = new CGeo(10);
			CObject* pGeo5 = new CGeo(10);
			CObject* pGeo6 = new CGeo(10);
			CObject* pGeo7 = new CGeo(5);
			CObject* pGeo8 = new CGeo(5);
			CObject* pGeo9 = new CGeo(5);
			CObject* pGeo10 = new CGeo(1);
			CObject* pGeo11 = new CGeo(1);
			CObject* pGeo12 = new CGeo(1);

			pGeo1->SetPosition(m_tPosition - 100.f);
			pGeo2->SetPosition(m_tPosition - 90.f);
			pGeo3->SetPosition(m_tPosition + 70.f);
			pGeo4->SetPosition(m_tPosition - 10.f);
			pGeo5->SetPosition(m_tPosition - 3.f);
			pGeo6->SetPosition(m_tPosition - 50.f);
			pGeo7->SetPosition(m_tPosition + 30.f);
			pGeo8->SetPosition(m_tPosition + 1.f);
			pGeo9->SetPosition(m_tPosition - 52.f);
			pGeo10->SetPosition(m_tPosition - 29.f);
			pGeo11->SetPosition(m_tPosition + 60.f);
			pGeo12->SetPosition(m_tPosition + 10.f);

			pGeo1->Initialize();
			pGeo2->Initialize();
			pGeo3->Initialize();
			pGeo4->Initialize();
			pGeo5->Initialize();
			pGeo6->Initialize();
			pGeo7->Initialize();
			pGeo8->Initialize();
			pGeo9->Initialize();
			pGeo10->Initialize();
			pGeo11->Initialize();
			pGeo12->Initialize();

			SCENE->GetCurrentScene()->AddObject(pGeo1);
			SCENE->GetCurrentScene()->AddObject(pGeo2);
			SCENE->GetCurrentScene()->AddObject(pGeo3);
			SCENE->GetCurrentScene()->AddObject(pGeo4);
			SCENE->GetCurrentScene()->AddObject(pGeo5);

			SCENE->GetCurrentScene()->AddObject(pGeo6);
			SCENE->GetCurrentScene()->AddObject(pGeo7);
			SCENE->GetCurrentScene()->AddObject(pGeo8);
			SCENE->GetCurrentScene()->AddObject(pGeo9);
			SCENE->GetCurrentScene()->AddObject(pGeo10);

			SCENE->GetCurrentScene()->AddObject(pGeo11);
			SCENE->GetCurrentScene()->AddObject(pGeo12);
		}

		break;
	}
}