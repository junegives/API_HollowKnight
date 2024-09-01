#include "pch.h"
#include "Player.h"
#include "Projectile.h"
#include "ScrollMgr.h"
#include "Monster.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "HitBox.h"
#include "Scene.h"
#include "UIMgr.h"
#include "Effect.h"
#include "Skill.h"
#include "CameraMgr.h"
#include "Geo.h"
#include "FireBall.h"
#include "Item.h"

extern HWND g_hWnd;
CPlayer* CPlayer::m_pInstance = nullptr;

CPlayer::CPlayer()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::PLAYER;
		m_ePreState = EPlayerState::ENUM_END;
		m_eCurState = EPlayerState::IDLE;
		m_eRender = ERenderID::GAMEOBJECT;
	}

	// 위치, 크기 관리
	{
		m_tPosition = { 300.f, 400.f };
		m_tSize = { 60.f,125.f };
		m_bLeft = false;
	}

	// UI 관리
	{
		m_iHP = MAXHP;
		m_iSoul = MAXSOUL;
		m_iGeo = 0;
	}

	// 행동 관리
	{
		m_fSpeed = 5.f;
		m_fJumpSpeed = 10.f;
		m_fDashSpeed = 30.f;
		m_fFallSpeed = 15.f;
		m_fDashSpeed = 20.f;
		m_isInvincible = false;
		m_iMaxInvincibleTime = 65 * 2;
		m_iFocusTime = 0;
	}
}

CPlayer::~CPlayer()
{
	Release();
}

/***************
	순수 가상 함수
***************/
void CPlayer::Initialize()
{
	m_isInitialized = true;
	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize(m_tSize);
		dynamic_cast<CHitBox*>(m_cHitBox)->SetOwner(EObjectType::PLAYER);
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 9;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();

		m_pFrameKey = L"PlayerIDLE_L";

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerIDLE_L.bmp", L"PlayerIDLE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerIDLE_R.bmp", L"PlayerIDLE_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFALL_L.bmp", L"PlayerFALL_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFALL_R.bmp", L"PlayerFALL_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/BlackPlayerIDLE_L.bmp", L"BlackPlayerIDLE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/BlackPlayerIDLE_R.bmp", L"BlackPlayerIDLE_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASH_L.bmp", L"PlayerSLASH_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASH_R.bmp", L"PlayerSLASH_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASHUP_L.bmp", L"PlayerSLASHUP_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASHUP_R.bmp", L"PlayerSLASHUP_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASHDOWN_L.bmp", L"PlayerSLASHDOWN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSLASHDOWN_R.bmp", L"PlayerSLASHDOWN_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSHOOT_L.bmp", L"PlayerSHOOT_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSHOOT_R.bmp", L"PlayerSHOOT_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerAIRBORN_L.bmp", L"PlayerAIRBORN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerAIRBORN_R.bmp", L"PlayerAIRBORN_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDOUBLEJUMP_L.bmp", L"PlayerDOUBLEJUMP_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDOUBLEJUMP_R.bmp", L"PlayerDOUBLEJUMP_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDOUBLEJUMPWING_L.bmp", L"PlayerDOUBLEJUMPWING_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDOUBLEJUMPWING_R.bmp", L"PlayerDOUBLEJUMPWING_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDASH_L.bmp", L"PlayerDASH_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDASH_R.bmp", L"PlayerDASH_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSHADOWDASH_L.bmp", L"PlayerSHADOWDASH_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSHADOWDASH_R.bmp", L"PlayerSHADOWDASH_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSSTART_L.bmp", L"PlayerFOCUSSTART_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSSTART_R.bmp", L"PlayerFOCUSSTART_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUS_L.bmp", L"PlayerFOCUS_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUS_R.bmp", L"PlayerFOCUS_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSGET_L.bmp", L"PlayerFOCUSGET_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSGET_R.bmp", L"PlayerFOCUSGET_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSEND_L.bmp", L"PlayerFOCUSEND_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerFOCUSEND_R.bmp", L"PlayerFOCUSEND_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerRUN_L.bmp", L"PlayerRUN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerRUN_R.bmp", L"PlayerRUN_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/BlackPlayerRUN_L.bmp", L"BlackPlayerRUN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/BlackPlayerRUN_R.bmp", L"BlackPlayerRUN_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerWALLJUMP_L.bmp", L"PlayerWALLJUMP_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerWALLJUMP_R.bmp", L"PlayerWALLJUMP_R");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerWALLSLIDE_L.bmp", L"PlayerWALLSLIDE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerWALLSLIDE_R.bmp", L"PlayerWALLSLIDE_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSTUN_L.bmp", L"PlayerSTUN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerSTUN_R.bmp", L"PlayerSTUN_R");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerDEAD.bmp", L"PlayerDEAD");

		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerCHALLENGE_L.bmp", L"PlayerCHALLENGE_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Player/PlayerCHALLENGE_R.bmp", L"PlayerCHALLENGE_R");
	}

	// 이펙트 관리
	{
		m_pHitCrack = new CEffect;
		m_pHitCrack->Initialize();

		m_pFocusEffect = new CEffect;
		m_pFocusEffect->setFrameKey(L"FocusEffect", 12, 70);
		m_pFocusEffect->Initialize();
	}

	// 스킬 관리
	{
		//m_pSlash = new CSkill;
		//m_pSlash->Initialize();
		//m_pSlash->setFrameKey(L"EffectSlash_L", 0, 200);
		//m_pSlash->SetVisible(false);
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSlash);

		//m_pFireBall = new CSkill;
		//m_pFireBall->Initialize();
		//m_pFireBall->setFrameKey(L"FireShoot_L", 0, 200);
		//m_pFireBall->SetVisible(false);
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pFireBall);
	}

	CCreature::Initialize();

	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.
}

int CPlayer::Update()
{
	m_cHitBox->SetPosition(m_tPosition);

	//std::cout << (int)m_eCurState << std::endl;

	if (m_onGravity)
		m_tPosition = m_tPosition - m_tVel;

	m_onGravity = true;
	m_isChangeScene = false;

	if (m_iEffectTime < 10)
	{
		++m_iEffectTime;
	}
	else m_showEffect = false;

	if (m_eCurState != EPlayerState::FOCUS && m_eCurState != EPlayerState::FOCUSGET)
		m_showFocusEffect = false;

	// 블락상태 아닐 때만 움직일 수 있음
	if(!m_bBlockAll && !m_bBlockKeyInput)
		KeyInput();
	MotionChange();
	return CCreature::Update();
}

void CPlayer::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);

	if (m_showEffect)
		m_pHitCrack->LateUpdate();

	if (m_showFocusEffect)
		m_pFocusEffect->LateUpdate();

	switch (m_eCurState)
	{
	case EPlayerState::IDLE:
		if (isDash) m_eCurState = EPlayerState::DASH;
		else if (isClimb) m_eCurState = EPlayerState::CLIMB;
		else if (isFall) m_eCurState = EPlayerState::FALL;
		else if (isJump) m_eCurState = EPlayerState::JUMP;
		else if (isDoubleJump) m_eCurState = EPlayerState::DOUBLEJUMP;
		m_iPressingSTime = 0;
		break;

	case EPlayerState::FALL:
		if (isIdle) m_eCurState = EPlayerState::IDLE;
		if (isClimb) m_eCurState = EPlayerState::CLIMB;
		m_fJumpTime = 0.f;
		m_iPressingSTime = 0;
		PlayerFall();
		break;

	case EPlayerState::JUMP:
		if (isClimb) m_eCurState = EPlayerState::CLIMB;
		else if (isFall) m_eCurState = EPlayerState::FALL;
		PlayerJump();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::DOUBLEJUMP:
		if (isClimb) m_eCurState = EPlayerState::CLIMB;
		else if (isFall) m_eCurState = EPlayerState::FALL;
		PlayerDoubleJump();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::MOVE:
		PlayerMove();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::DASH:
		PlayerDash();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::CLIMB:
		if (!m_canWallJump)
		{
			m_eCurState = EPlayerState::FALL;
			break;
		}
		CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
		if (isClimb) m_eCurState = EPlayerState::CLIMB;
		else if (isFall) m_eCurState = EPlayerState::FALL;
		PlayerClimb();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::WALLJUMP:
		CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
		if (isFall) m_eCurState = EPlayerState::FALL;
		PlayerWallJump();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::SLASH:
	case EPlayerState::SLASH_UP:
	case EPlayerState::SLASH_DOWN:
		PlayerSlash();
		m_iPressingSTime = 0;

		break;

	case EPlayerState::SHOOT:
		PlayerShoot();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::STUN:
		PlayerStun();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::FOCUSSTART:
		PlayerFocusStart();
		break;

	case EPlayerState::FOCUS:
		PlayerFocus();
		break;

	case EPlayerState::FOCUSGET:
		PlayerFocusGet();
		break;

	case EPlayerState::FOCUSEND:
		PlayerFocusEnd();
		break;

	case EPlayerState::FIGHTREADY:
		PlayerReady();
		m_iPressingSTime = 0;
		break;

	case EPlayerState::DEAD:
		PlayerDead();
		m_iPressingSTime = 0;
		break;

	default:
		break;
	}


	if (!m_bBlockMotionChange)
		__super::Move_Frame();
}

void CPlayer::Render(HDC _hDC)
{
	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		m_tFrame.iMotion,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값

	if (m_showEffect)
		m_pHitCrack->Render(_hDC);

	if (m_showFocusEffect)
		m_pFocusEffect->Render(_hDC);

	CCreature::Render(_hDC);
}

void CPlayer::Release()
{
	SAFE_DELETE(m_pHitCrack);
	SAFE_DELETE(m_pFocusEffect);
	SAFE_DELETE(m_cHitBox);
	CSoundMgr::Get_Instance()->StopAll();
	CCreature::Release();
}

void CPlayer::KeyInput()
{
	if (!m_bBlockChange)
	{
		if (CKeyMgr::GetInstance()->Key_Down('C')) {
			// 어떤 경우든 대시 가능
			m_eCurState = EPlayerState::DASH;
		}

		// 근접 공격 (일회성)
		if (CKeyMgr::GetInstance()->Key_Down('X'))
		{
			if (CKeyMgr::GetInstance()->Key_Pressing(VK_UP))
			{
				m_eCurState = EPlayerState::SLASH_UP;
			}

			else if (CKeyMgr::GetInstance()->Key_Pressing(VK_DOWN))
			{
				if (EPlayerState::JUMP == m_eCurState || EPlayerState::DOUBLEJUMP == m_eCurState)
				{
					//CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword2.wav", EChannelID::SKILL, g_fVolume);
					m_eCurState = EPlayerState::SLASH_DOWN;
				}

				else m_eCurState = EPlayerState::SLASH;
				//CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword3.wav", EChannelID::SKILL, g_fVolume);
			}

			else m_eCurState = EPlayerState::SLASH;
			//CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword4.wav", EChannelID::SKILL, g_fVolume);
		}

		// 투사체 공격
		if (CKeyMgr::GetInstance()->Key_Down('A'))
		{
			if (!useSoul(100)) m_eCurState = EPlayerState::IDLE;
			else
			{
				m_eCurState = EPlayerState::SHOOT;
				//CUIMgr::GetInstance()->useSoul();
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down('S'))
		{
			m_eCurState = EPlayerState::FOCUSSTART;
		}

		// 체력 회복
		if (CKeyMgr::GetInstance()->isStayKeyDown('S'))
		{
			// 영혼 소모
			if (!useSoul(2)) m_eCurState = EPlayerState::IDLE;

			else
			{
				if (m_iPressingSTime < 2)
				{
					m_eCurState = EPlayerState::FOCUSSTART;
				}

				else if (m_isFocusStartEnd)
				{
					m_eCurState = EPlayerState::FOCUS;
				}

				else if (m_isFocusEnd)
				{
					m_eCurState = EPlayerState::FOCUSGET;
				}
				else if (m_isFocusGetEnd)
				{
					m_eCurState = EPlayerState::FOCUS;
					m_iPressingSTime = 1;
				}

				++m_iPressingSTime;
			}
		}

		/*if (CKeyMgr::GetInstance()->isOnceKeyUp('S'))
			m_eCurState = EPlayerState::FOCUSEND;*/

		if (CKeyMgr::GetInstance()->Key_Down('Z')) {
			isIdle = false;
			isClimb = false;
			isFall = false;
			// 이미 더블점프까지 한 경우
			if (isDoubleJump)
				return;
			// 대쉬 중일 때는 점프 불가능
			/*if (EPlayerState::DASH == m_eCurState)
				return;*/
				// 점프 중일 때는 더블 점프 실행
			else if (isJump)
			{
				m_eCurState = EPlayerState::DOUBLEJUMP;
				return;
			}
			// 벽타기 중이었을 때는 반대 방향으로 점프
			else if (EPlayerState::CLIMB == m_eCurState)
			{
				m_eCurState = EPlayerState::WALLJUMP;
				//CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerJump.wav", EChannelID::MOVEMENT, g_fVolume);
			}
			// 더블점프중이 아니면 점프로 상태 변경
			else if (!isJump)
			{
				m_eCurState = EPlayerState::JUMP;
				//CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerJump.wav", EChannelID::MOVEMENT, g_fVolume);
			}
		}
	}

	if (CKeyMgr::GetInstance()->Key_Pressing(VK_RIGHT)) {

		if (EPlayerState::DASH == m_eCurState)
			return;

		if (EPlayerState::STUN == m_eCurState)
			return;

		// 점프/더블점프/추락/근접공격 중일 때는 스테이트는 유지하고 이동만 진행한다.
		else if (EPlayerState::JUMP == m_eCurState ||
			EPlayerState::DOUBLEJUMP == m_eCurState ||
			EPlayerState::FALL == m_eCurState ||
			EPlayerState::SLASH == m_eCurState ||
			EPlayerState::SLASH_UP == m_eCurState ||
			EPlayerState::SLASH_DOWN == m_eCurState ||
			EPlayerState::WALLJUMP == m_eCurState)
		{
			m_bLeft = false;
			m_tPosition.m_fX += m_fSpeed;
			return;
		}
		// 벽타기 중일때는 반대로 이동한 경우만 이동을 진행한다.
		else if (EPlayerState::CLIMB == m_eCurState)
		{
			if (m_bLeft)
			{
				isClimb = false;
				m_bLeft = false;
				isFall = true;
				//m_eCurState = EPlayerState::FALL;
				m_tPosition.m_fX += m_fSpeed;
			}
			return;
		}

		// 그 외에는
		if (m_isInvincible)
			m_pFrameKey = L"BlackPlayerRUN_R";
		else
			m_pFrameKey = L"PlayerRUN_R";
		m_tPosition.m_fX += m_fSpeed;
		m_bLeft = false;
		isFall = false;
		m_eCurState = EPlayerState::MOVE;
		CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerStep.wav", EChannelID::MOVEMENT, g_fVolume);
	}

	if (CKeyMgr::GetInstance()->Key_Pressing(VK_LEFT)) {
		if (EPlayerState::DASH == m_eCurState)
			return;

		if (EPlayerState::STUN == m_eCurState)
			return;

		// 점프/더블점프/추락/근접공격 중일 때는 스테이트는 유지하고 이동만 진행한다.
		else if (EPlayerState::JUMP == m_eCurState ||
			EPlayerState::DOUBLEJUMP == m_eCurState ||
			EPlayerState::FALL == m_eCurState ||
			EPlayerState::SLASH == m_eCurState ||
			EPlayerState::SLASH_UP == m_eCurState ||
			EPlayerState::SLASH_DOWN == m_eCurState ||
			EPlayerState::WALLJUMP == m_eCurState)
		{
			m_bLeft = true;
			m_tPosition.m_fX -= m_fSpeed;
			return;
		}
		// 벽타기 중일때는 반대로 이동한 경우만 이동을 진행한다.
		else if (EPlayerState::CLIMB == m_eCurState)
		{
			if (!m_bLeft)
			{
				isClimb = false;
				m_bLeft = true;
				isFall = true;
				//m_eCurState = EPlayerState::FALL;
				m_tPosition.m_fX -= m_fSpeed;
			}
			return;
		}

		if (m_isInvincible)
			m_pFrameKey = L"BlackPlayerRUN_L";
		else
			m_pFrameKey = L"PlayerRUN_L";
		m_tPosition.m_fX -= m_fSpeed;
		m_bLeft = true;
		isFall = false;
		m_eCurState = EPlayerState::MOVE;
		CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerStep.wav", EChannelID::MOVEMENT, g_fVolume);
	}
}

void CPlayer::MotionChange()
{
	m_ePreState;
	m_eCurState;

	if (m_ePreState != m_eCurState || m_preInvincible != m_isInvincible)
	{
		switch (m_eCurState)
		{
		case EPlayerState::IDLE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);

			if (m_isInvincible)
			{
				if (m_bLeft) m_pFrameKey = L"BlackPlayerIDLE_L";
				else m_pFrameKey = L"BlackPlayerIDLE_R";
				m_tFrame.iFrameEnd = 16;
			}
			else
			{
				if (m_bLeft) m_pFrameKey = L"PlayerIDLE_L";
				else m_pFrameKey = L"PlayerIDLE_R";
				m_tFrame.iFrameEnd = 8;
			}
			m_tSize = { 60.f,125.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::MOVE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);

			m_tSize = { 86.f,130.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::JUMP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerJump.wav", EChannelID::MOVEMENT, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerAIRBORN_L";
			else m_pFrameKey = L"PlayerAIRBORN_R";
			m_tSize = { 100.f ,142.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::DOUBLEJUMP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerWing.wav", EChannelID::MOVEMENT, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerDOUBLEJUMP_L";
			else m_pFrameKey = L"PlayerDOUBLEJUMP_R";
			m_tSize = { 137.f ,150.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::FALL:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);

			if (m_bLeft) m_pFrameKey = L"PlayerFALL_L";
			else m_pFrameKey = L"PlayerFALL_R";
			m_tSize = { 91.f, 135.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::DASH:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerDash.wav", EChannelID::SKILL, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerDASH_L";
			else m_pFrameKey = L"PlayerDASH_R";
			m_tSize = { 230.f, 117.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

	/*	case EPlayerState::SHADOWDASH:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerDash.wav", EChannelID::SKILL, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerDASH_L";
			else m_pFrameKey = L"PlayerDASH_R";
			m_tSize = { 294.f,139.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;*/

		case EPlayerState::CLIMB:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);

			if (m_bLeft) m_pFrameKey = L"PlayerWALLSLIDE_L";
			else m_pFrameKey = L"PlayerWALLSLIDE_R";
			m_tSize = { 80.f , 132.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::WALLJUMP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);

			if (m_bLeft) m_pFrameKey = L"PlayerWALLJUMP_L";
			else m_pFrameKey = L"PlayerWALLJUMP_R";
			m_tSize = { 118.f , 142.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::SLASH:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword1.wav", EChannelID::SKILL, g_fVolume);
			m_tSize = { 109.f , 128.f };

			m_pSlash = new CSkill;

			if (m_bLeft)
			{
				m_pFrameKey = L"PlayerSLASH_L";

				m_pSlash->SetSize({ 157.f, 114.f });
				m_pSlash->setFrameKey(L"EffectSlash_L", 5, 50);
				dynamic_cast<CSkill*>(m_pSlash)->SetDirection(EDirection::LEFT);
			}
			else
			{
				m_pFrameKey = L"PlayerSLASH_R";

				m_pSlash->SetSize({ 157.f, 114.f });
				m_pSlash->setFrameKey(L"EffectSlash_R", 5, 50);
				dynamic_cast<CSkill*>(m_pSlash)->SetDirection(EDirection::RIGHT);
			}
			m_pSlash->SetVisible(true);
			m_pSlash->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSlash);


			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::SLASH_UP:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword2.wav", EChannelID::SKILL, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerSLASHUP_L";
			else m_pFrameKey = L"PlayerSLASHUP_R";
			m_tSize = { 116.f , 131.f };

			m_pSlash = new CSkill;

			m_pSlash->SetSize({ 170.f, 189.f });
			m_pSlash->setFrameKey(L"EffectUpSlash", 5, 50);
			m_pSlash->SetVisible(true);
			dynamic_cast<CSkill*>(m_pSlash)->SetDirection(EDirection::UP);
			m_pSlash->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSlash);

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::SLASH_DOWN:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerSword3.wav", EChannelID::SKILL, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerSLASHDOWN_L";
			else m_pFrameKey = L"PlayerSLASHDOWN_R";
			m_tSize = { 142.f , 130.f };

			m_pSlash = new CSkill;

			m_pSlash->SetSize({ 183.f, 210.f });
			m_pSlash->setFrameKey(L"EffectDownSlash", 5, 50);
			m_pSlash->SetVisible(true);
			dynamic_cast<CSkill*>(m_pSlash)->SetDirection(EDirection::DOWN);
			m_pSlash->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSlash);

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;


		case EPlayerState::SHOOT:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerFireball.wav", EChannelID::SKILL, g_fVolume);

			m_pFireBall = new CFireBall;

			if (m_bLeft)
			{
				m_pFrameKey = L"PlayerSHOOT_L";
				m_pFireBall->setFrameKey(L"FireShoot_L", 3, 50);
				dynamic_cast<CFireBall*>(m_pFireBall)->SetDirection(EDirection::LEFT);
			}
			else
			{
				m_pFrameKey = L"PlayerSHOOT_R";
				m_pFireBall->setFrameKey(L"FireShoot_R", 3, 50);
				dynamic_cast<CFireBall*>(m_pFireBall)->SetDirection(EDirection::RIGHT);
			}
			m_pFireBall->SetSize({266.f, 116.f});
			m_pFireBall->SetPosition(m_tPosition);
			m_pFireBall->SetVisible(true);
			m_pFireBall->Initialize();
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pFireBall);

			m_tSize = { 110.f , 132.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EPlayerState::STUN:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerDamage.wav", EChannelID::MOVEMENT, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"PlayerSTUN_L";
			else m_pFrameKey = L"PlayerSTUN_R";
			m_tSize = { 96.f, 126.f };

			m_pHitCrack->SetPosition(m_tPosition);
			m_pHitCrack->SetSize({ 699.f, 140.f });
			m_pHitCrack->setFrameKey(L"HitCrack", 2, 70);
			m_showEffect = true;
			m_iEffectTime = 0;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::DEAD:
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerDead.wav", EChannelID::MOVEMENT, g_fVolume);

			m_pFrameKey = L"PlayerDEAD";
			m_tSize = { 116.f, 131.f };

			m_pHitCrack->SetPosition(m_tPosition);
			m_pHitCrack->SetSize({ 308.f, 270.f });
			m_pHitCrack->setFrameKey(L"DeathEffect", 5, 70);
			m_showEffect = true;
			m_iEffectTime = 0;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;

			//case EPlayerState::DAMAGED:

			//	m_tFrame.iFrameStart = 0;
			//	m_tFrame.iFrameEnd = 3;
			//	m_tFrame.iMotion = 4;
			//	m_tFrame.dwSpeed = 200;
			//	m_tFrame.dwTime = GetTickCount();

			//	break;

		case EPlayerState::FOCUSSTART:

			if (m_bLeft) m_pFrameKey = L"PlayerFOCUSSTART_L";
			else m_pFrameKey = L"PlayerFOCUSSTART_R";
			m_tSize = { 74.f, 126.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EPlayerState::FOCUS:

			if (m_bLeft) m_pFrameKey = L"PlayerFOCUS_L";
			else m_pFrameKey = L"PlayerFOCUS_R";
			m_tSize = { 74.f, 126.f };

			m_pFocusEffect->SetPosition(m_tPosition);
			m_pFocusEffect->SetSize({ 91.f, 182.f });
			m_showFocusEffect = true;
			m_iFocusEffectTime = 0;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EPlayerState::FOCUSGET:

			if (m_bLeft) m_pFrameKey = L"PlayerFOCUSGET_L";
			else m_pFrameKey = L"PlayerFOCUSGET_R";
			m_tSize = { 102.f, 123.f };
			m_showFocusEffect = true;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			increaseHP(1);

			break;

		case EPlayerState::FOCUSEND:

			if (m_bLeft) m_pFrameKey = L"PlayerFOCUSEND_L";
			else m_pFrameKey = L"PlayerFOCUSEND_R";
			m_tSize = { 71.f, 126.f };
			
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EPlayerState::FIGHTREADY:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::SKILL);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MOVEMENT);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BGM);
			
			if (m_bLeft) m_pFrameKey = L"PlayerCHALLENGE_L";
			else m_pFrameKey = L"PlayerCHALLENGE_R";
			m_tSize = { 123.f, 129.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();

			break;

		}

		m_ePreState = m_eCurState;
		m_preInvincible = m_isInvincible;
	}
}

void CPlayer::PlayerJump()
{
	isJump = true;
	m_bBlockChange = false;
	if (m_fJumpTime < 40.f)
	{
		m_tPosition.m_fY -= m_fJumpSpeed;
		m_fJumpTime += 1.f;
	}
	else
	{
		m_fJumpTime = 0.f;
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerDoubleJump()
{
	m_bBlockChange = false;
	isDoubleJump = true;

	if (m_fDoubleJumpTime < 20.f)
	{
		SetOnGravity(false);
		m_tPosition.m_fY -= m_fJumpSpeed;
		m_fDoubleJumpTime += 1.f;
	}
	else
	{
		SetOnGravity(true);
		m_fDoubleJumpTime = 0.f;
		//isFall = true;
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerMove()
{
	m_bBlockChange = false;
	m_eCurState = EPlayerState::IDLE;
}

void CPlayer::PlayerDash()
{
	float fTemp = m_fDashSpeed;

	if (m_bLeft) fTemp = -1 * m_fDashSpeed;

	if (m_fDashTime < 15.f)
	{
		m_cHitBox->SetPosition({ m_tPosition.m_fX + 1.5f * fTemp, m_tPosition.m_fY });
		m_cHitBox->SetSize({ 60.f, 125.f });

		SetOnGravity(false);
		m_bBlockChange = true;
		m_tPosition.m_fX += fTemp;
		m_fDashTime += 1.f;
	}
	else
	{
		SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY });
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 60.f, 125.f});

		m_bBlockChange = false;
		SetOnGravity(true);
		m_fDashTime = 0.f;
		isClimb = false;
		//isFall = true;
		//isDash = false;
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerShoot()
{
	if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
	{
		SetOnGravity(false);
		m_bBlockChange = true;
		// 투사체 객체 생성


	}
	else
	{
		m_bBlockChange = false;
		SetOnGravity(true);
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerStun()
{
	if (m_fStunTime < 50.f)
	{
		SetOnGravity(false);
		m_bBlockChange = true;
		m_fStunTime += 1.f;
	}
	else
	{
		m_bBlockChange = false;
		SetOnGravity(true);
		m_fStunTime = 0.f;
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerReady()
{
	m_eCurState = EPlayerState::FIGHTREADY;
	SetOnGravity(true);

	if (m_iBlockTime < 600)
	{
		m_bBlockChange = true;
		m_iBlockTime += 1;

		if (m_iBlockTime == 50)
			CSoundMgr::Get_Instance()->PlaySound(L"E_PlayerChallenge.wav", EChannelID::MOVEMENT, g_fVolume);

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;

		if (m_iBlockTime == 150)
		{
			CSoundMgr::Get_Instance()->StopAll();
			CSceneMgr::GetInstance()->GetCurrentScene()->StartBoss();
		}
	}
	else
	{
		m_bBlockMotionChange = false;
		m_bBlockChange = false;
		m_bBlockAll = false;
		m_iBlockTime = 0.f;
		m_eCurState = EPlayerState::IDLE;
	}
}

void CPlayer::PlayerFocusStart()
{
	if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
	{
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 60.f, 125.f });

		SetOnGravity(true);
		m_bBlockChange = true;
	}

	else
	{
		m_isFocusStartEnd = true;
		m_eCurState = EPlayerState::FALL;
		SetOnGravity(true);
		m_bBlockChange = false;
	}
}

void CPlayer::PlayerFocus()
{
	//m_cHitBox->SetPosition(m_tPosition);
	//m_cHitBox->SetSize({ 60.f, 125.f });

	//SetOnGravity(true);
	//m_bBlockChange = false;
	//m_fFocusTime += 1.f;

	if (m_iFocusTime < 30)
	{
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 60.f, 125.f });

		SetOnGravity(true);
		m_bBlockChange = false;
		m_iFocusTime += 1;
	}

	else
	{
		m_isFocusEnd = true;
		m_isFocusStartEnd = false;
		m_eCurState = EPlayerState::FALL;
		m_iFocusTime = 0;
		SetOnGravity(true);
		m_bBlockChange = false;
	}

	if (m_iFocusTime % 10 == 0 && m_iFocusTime != 0)
	{
		//CUIMgr::GetInstance()->useSoul();
	}
}

void CPlayer::PlayerFocusGet()
{
	//m_cHitBox->SetPosition(m_tPosition);
	//m_cHitBox->SetSize({ 60.f, 125.f });

	//SetOnGravity(true);
	//m_bBlockChange = true;

	if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
	{
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 60.f, 125.f });

		SetOnGravity(true);
		m_bBlockChange = true;
	}

	else
	{
		m_isFocusGetEnd = true;
		m_isFocusEnd = false;
		m_eCurState = EPlayerState::FALL;
		SetOnGravity(true);
		m_bBlockChange = false;
	}
}

void CPlayer::PlayerFocusEnd()
{
	if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
	{
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 60.f, 125.f });

		SetOnGravity(true);
		m_bBlockChange = true;
	}

	else
	{
		m_bBlockChange = false;
		SetOnGravity(true);
		m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerDead()
{
	m_bBlockTrigger = true;
	m_bBlockAll = true;
	m_bBlockChange = true;
	m_bBlockKeyInput = true;
	m_isInvincible = true;
	SetOnGravity(false);

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bBlockMotionChange = true;
	}

	if (m_fDeadTime < 100.f)
	{
		SetOnGravity(false);
		m_bBlockChange = true;
		m_fDeadTime += 1.f;
		m_bBlockMotionChange = true;
	}

	else if (m_fDeadTime < 150.f)
	{
		SetOnGravity(false);
		m_bBlockChange = true;
		m_bBlockMotionChange = false;
		m_fDeadTime += 1.f;
	}
	else
	{
		CAMERA->FadeOut();
		SetOnGravity(false);
		// 카메라 Fade out하고
		// 맵 다시 Initialize
		// 플레이어 위치만 다시 설정해주기
	}
}

bool CPlayer::AddItem(CObject* _pItem)
{
	if (m_pItemList.size() >= m_iMaxItem) return false;

	m_pItemList.push_back(_pItem);
	CUIMgr::GetInstance()->getItem(_pItem->getFrameKey(), m_pItemList.size() - 1);
	return true;
}

bool CPlayer::UseItem(int _iItemNum)
{
	int itemNum = _iItemNum;
	std::for_each(m_pItemList.begin(), m_pItemList.end(), [_iItemNum](auto& _objPtr) {

		if (dynamic_cast<CItem*>(_objPtr)->GetItemCode() == _iItemNum)
		{
				_objPtr->Release();
				SAFE_DELETE<CObject*>(_objPtr);
				return true;
		}
	});
	return false;
}

void CPlayer::PlayerRestart()
{
	SCENE->RestartCurrentScene();
	
	switch (SCENE->GetCurSceneType())
	{
	case ESceneType::GAME_START:
		break;
	case ESceneType::DIRTMOUTH:
		break;
	case ESceneType::CROSSROAD:
		break;
	case ESceneType::MANTISTOWN:
		m_tPosition = { 6700.f, 600.f };
		break;
	case ESceneType::OBTAIN:
		break;
	case ESceneType::STORE:
		break;
	case ESceneType::ARENA:
		break;
	case ESceneType::DEFEAT:
		break;
	case ESceneType::VICTORY:
		break;
	default:
		break;
	}

	m_iHP = MAXHP;
	m_iSoul = 0;
	CUIMgr::GetInstance()->setMaxHP();
	CUIMgr::GetInstance()->setEmptySoul();

	m_eCurState = EPlayerState::FALL;

	m_bBlockMotionChange = false;
	m_bBlockChange = false;
	m_bBlockAll = false;
	m_bBlockKeyInput = false;
	SetOnGravity(true);
	m_fDeadTime = 0.f;
	m_bBossFight = false;
}

void CPlayer::PlayerClimb()
{
	isJump = false;
	isDoubleJump = false;
	if (isIdle) m_eCurState = EPlayerState::FALL;
	SetOnGravity(false);
	m_bBlockChange = false;
	m_tPosition.m_fY += m_fSpeed / 2;

	// 플레이어의 절반 이상이 벽 아래로 내려온 경우
	if (m_currentCollided && m_currentCollided->GetPosition().m_fY + m_currentCollided->GetSize().m_fY / 2 < m_tPosition.m_fY)
	{
		isClimb = false;
		isFall = true;
	}
}

void CPlayer::PlayerWallJump()
{
	m_bBlockChange = false;
	isClimb = false;
	isJump = true;

	float fTemp = m_fSpeed;
	if (m_bLeft) fTemp = -1 * m_fSpeed;

	if (m_fWallJumpTime < 20.f)
	{
		m_tPosition.m_fY -= m_fJumpSpeed;
		m_tPosition.m_fX -= fTemp;
		m_fWallJumpTime += 1.f;
	}
	else
	{
		m_fWallJumpTime = 0.f;
		isFall = true;
		//m_eCurState = EPlayerState::FALL;
	}
}

void CPlayer::PlayerFall()
{
	SetOnGravity(true);
	m_bBlockChange = false;
	m_bBlockTrigger = false;
}

void CPlayer::PlayerSlash()
{
	if (m_fSlashTime < 18.f)
	{
		m_fSlashTime += 1.f;
		m_bBlockChange = true;
	}
	else
	{
		m_bBlockChange = false;
		m_fSlashTime = 0.f;
		//isIdle = true;
		m_eCurState = EPlayerState::FALL;
	}
}



void CPlayer::OnCollided(CObject* _pObject)
{
	// 플레이어와 몬스터 충돌
	// loseHP
	// 3초간 무적
	if (m_isInvincible) return;

	switch (_pObject->GetObjectType())
	{
	case EObjectType::MONSTER:

		m_iInvincibleTime = 0;
		m_isInvincible = true;
		if (setDamage(1))
		{
			CUIMgr::GetInstance()->loseHP();
			// 넉백
			// 데미지 프레임으로 변경 후
			// 일시 정지 이후에도 n초동안 깜빡거리기
			m_eCurState = EPlayerState::STUN;

			// 카메라 쉐이킹
			CAMERA->CameraShaking(20);

			// 전체 위치 변경 일시 정지
		}
		else
		{
			// 죽은 경우
			if(m_eCurState != EPlayerState::DEAD)
				CUIMgr::GetInstance()->loseHP();
			m_eCurState = EPlayerState::DEAD;
			m_bBlockTrigger = true;
		}

		break;

	case EObjectType::PROJECTILE:

		m_iInvincibleTime = 0;
		m_isInvincible = true;
		if (setDamage(1))
		{
			CUIMgr::GetInstance()->loseHP();

			// 넉백
			m_eCurState = EPlayerState::STUN;
			// 카메라 쉐이킹
			// 데미지 프레임으로 변경 후
			// 전체 위치 변경 일시 정지
			// 일시 정지 이후에도 n초동안 깜빡거리기
			// 카메라 쉐이킹
			CAMERA->CameraShaking(20);
		}
		else
		{
			// 죽은 경우
			if (m_eCurState != EPlayerState::DEAD)
				CUIMgr::GetInstance()->loseHP();
			m_eCurState = EPlayerState::DEAD;
			m_bBlockTrigger = true;
		}

		break;

	case EObjectType::GEO:
		m_iGeo += dynamic_cast<CGeo*>(_pObject)->GetAmount();
		CUIMgr::GetInstance()->setGeo(m_iGeo);
		break;
	}
}

void CPlayer::OnCollided(CObject* _pObject, EDirection _eDir)
{
	switch (_pObject->GetObjectType())
	{
		// 플레이어와 타일 충돌
	case EObjectType::TILE:

		switch (dynamic_cast<CTile*>(_pObject)->GetTileType())
		{
		case ETileType::GROUND:
			switch (_eDir)
			{
			case EDirection::LEFT:
				m_isBlockLeft = true;
				isClimb = false;
				break;

			case EDirection::RIGHT:
				m_isBlockRight = true;
				isClimb = false;
				break;

			case EDirection::UP:
				if (EPlayerState::JUMP != m_eCurState)
				{
					m_fDt = 0.f;
					m_tVel = { 0.f, 0.f };
					isIdle = true;
					isFall = false;
					isClimb = false;
					isJump = false;
					isDoubleJump = false;
					m_onGravity = false;
				}
				//SetPosition({ m_tPosition.m_fX, _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_cHitBox->GetSize().m_fY / 2 });
				break;

			case EDirection::DOWN:
				if (EPlayerState::JUMP == m_eCurState || EPlayerState::DOUBLEJUMP == m_eCurState)
				{
					isFall = true;
					//m_eCurState = EPlayerState::FALL;
				}
				break;
			}
			break;

		case ETileType::WALL:
			switch (_eDir)
			{
			case EDirection::LEFT:
				if (!m_canWallJump)
				{
					isClimb = false;
					break;
				}
				m_fDt = 0.f;
				m_tVel = { 0.f, 0.f };
				//m_tPosition.m_fX = _pObject->GetPosition().m_fX + _pObject->GetSize().m_fX / 2 + m_tSize.m_fX / 2;
				isClimb = true;
				isIdle = false;
				m_currentCollided = _pObject;

				break;

			case EDirection::RIGHT:
				if (!m_canWallJump)
				{
					isClimb = false;
					break;
				}
				m_fDt = 0.f;
				m_tVel = { 0.f, 0.f };
				//m_tPosition.m_fX = _pObject->GetPosition().m_fX - (_pObject->GetSize().m_fX / 2 + m_tSize.m_fX / 2);
				isClimb = true;
				isIdle = false;
				m_currentCollided = _pObject;

				break;

			case EDirection::UP:
				if (EPlayerState::JUMP != m_eCurState)
				{
					m_fDt = 0.f;
					m_tVel = { 0.f, 0.f };
					isIdle = true;
					isFall = false;
					isClimb = false;
					isJump = false;
					isDoubleJump = false;
					m_onGravity = false;
				}
				//SetPosition({ m_tPosition.m_fX, _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_tSize.m_fY / 2 });
				break;

			case EDirection::DOWN:
				if (EPlayerState::JUMP == m_eCurState || EPlayerState::DOUBLEJUMP == m_eCurState)
				{
					isFall = true;
					//m_eCurState = EPlayerState::FALL;
				}
				break;
			}
			break;

		case ETileType::OBSTACLE:
			break;

		case ETileType::TRIGGER:
			if (m_bBlockTrigger) return;
			switch ((int)CSceneMgr::GetInstance()->GetCurSceneType())
			{
			case (int)ESceneType::DIRTMOUTH:
				// 상점으로 이동
				if (_pObject->GetPosition().m_fX < 4000)
				{
					//CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::STORE);
					//m_cHitBox->SetPosition(m_tPosition);
					//m_isChangeScene = true;
				}

				// 잊혀진 교차로로 이동
				else
				{
					CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::CROSSROAD);
					m_cHitBox->SetPosition(m_tPosition);
					CPlayer::GetInstance()->SetPosition({ 3800.f, 800.f });
					m_isChangeScene = true;
				}
				break;

			case (int)ESceneType::STORE:

				CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::DIRTMOUTH);
				m_cHitBox->SetPosition(m_tPosition);
				CPlayer::GetInstance()->SetPosition({ 2650.f, 1790.f });
				m_isChangeScene = true;
				
				break;

			case (int)ESceneType::CROSSROAD:
				// 사마귀 마을로 이동
				if (_pObject->GetPosition().m_fX < 1000)
				{
					CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::MANTISTOWN);
					m_cHitBox->SetPosition(m_tPosition);
					SetPosition({6700.f, 800.f});
					SetLeft(true);
					m_isChangeScene = true;
				}

				else if (_pObject->GetPosition().m_fX < 5000)
				{
					//CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::DIRTMOUTH);
					//m_cHitBox->SetPosition(m_tPosition);
					//SetPosition({ 4000.f, 1870.f });
					//m_isChangeScene = true;
				}
				
				else
				{
					//CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::ARENA);
					//m_cHitBox->SetPosition(m_tPosition);
					//m_isChangeScene = true;
				}

				break;

			case (int)ESceneType::MANTISTOWN:
				// 잊혀진 교차로로 이동
				if (_pObject->GetPosition().m_fX > 6000)
				{
					CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::CROSSROAD);
					m_cHitBox->SetPosition(m_tPosition);
					SetPosition({ 100.f, 2100.f });
					SetLeft(false);
					m_isChangeScene = true;
				}
				// 사마귀 군주 전투 시작
				else if (_pObject->GetPosition().m_fX > 1000)
				{
					_pObject->SetIsDead(true);
					// 이미 싸우고 있거나 승리했으면 해당 트리거 무시
					if (m_bBossFight || m_bBossComplete || m_isMantisComplete) break;
					m_bBlockAll = true;
					m_bBossFight = true;
					m_eCurState = EPlayerState::FIGHTREADY;
					m_isChangeScene = false;
				}
				// 벽점프 해금 장소로 이동
				else
				{
					CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::OBTAIN);
					//CScrollMgr::GetInstance()->SetScrollX(100);
					//CScrollMgr::GetInstance()->SetScrollY(2100);
					m_cHitBox->SetPosition(m_tPosition);
					SetPosition({ 2500, 600 });
					SetLeft(true);
					m_isChangeScene = true;
				}

				break;

			case (int)ESceneType::OBTAIN:
				CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::MANTISTOWN);
				m_cHitBox->SetPosition(m_tPosition);
				m_tPosition = {650.f, 2500.f};
				m_isChangeScene = true;

			}
			break;
		}
	}
}