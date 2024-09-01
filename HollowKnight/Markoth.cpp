#include "pch.h"
#include "Markoth.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraMgr.h"
#include "Tile.h"
#include "SoundMgr.h"
#include "Arena.h"
#include "Effect.h"
#include "Shield.h"
#include "MarkBall.h"
#include "Player.h"
#include "Skill.h"

CMarkoth::CMarkoth()
{
}

CMarkoth::~CMarkoth()
{
}

void CMarkoth::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.

	// 이미지 추가
	{
		// MOVE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkMOVE.bmp", L"MarkMOVE");

		// ROTATE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkROTATE.bmp", L"MarkROTATE");

		// SHIELD
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkSHIELD.bmp", L"MarkSHIELD");

		// SWORD
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkSWORD.bmp", L"MarkSWORD");

		// APPEAR EFFECT
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkAPPEAR.bmp", L"MarkAPPEAR");
	}

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize(m_tSize - 20.f);
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// 행동 관리
	{
		m_onGravity = false;
		m_fSpeed = 10.f;
		m_bDead = false;
		m_iHP = 15;
		m_eCurState = EMonsterState::IDLE;
	}

	// 이미지 관리
	{
		m_pFrameKey = L"MarkMOVE";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount64();
	}

	// 위치 관리
	{
		m_tSize = { 280.f, 420.f };
		m_tOriginSize = m_tSize;
		m_tPosition = { 950.f, 600.f };
		m_tOriginPosition = m_tPosition;
	}

	// 이펙트 관리
	{
		m_pAppearEffect = new CEffect;
		m_pAppearEffect->SetPosition(m_tOriginPosition);
		m_pAppearEffect->SetSize({ 353.f, 322.f });
		m_pAppearEffect->setFrameKey(L"MarkAPPEAR", 4, 100);
		m_pAppearEffect->Initialize();
	}

	// 회전볼 관리
	{
		vDir[0] = { 0, -1 };
		vDir[1] = { 1, -1 };
		vDir[2] = { 1, 0 };
		vDir[3] = { 1, 1 };
		vDir[4] = { 0, 1 };
		vDir[5] = { -1, 1 };
		vDir[6] = { -1, 0 };
		vDir[7] = { -1, -1 };
	}

	CBoss::Initialize();

	m_eRender = ERenderID::DEBUG_UI;
}

int CMarkoth::Update()
{
	m_iPlayTime++;

	if (m_bStartMove && m_iPlayTime % 1000 == 0)
	{
		m_eCurState = EMonsterState::ROTATE;
	}

	if (m_iHP < 5)
		m_iAttackTerm = 100;

	else if (m_iHP < 20)
	{
		m_iAttackTerm = 150;
	}

	if (m_showEffect)
	{
		if (m_iEffectTime < 20)
		{
			++m_iEffectTime;
		}
		else
		{
			m_showEffect = false;
			m_iEffectTime = 0;
		}
	}

	if (m_isShowAppearEffect)
	{
		if (m_iEffectTime < 20)
		{
			++m_iEffectTime;
		}
		else
		{
			m_isShowAppearEffect = false;
			m_iEffectTime = 0;
		}
	}

	if (m_eCurState == EMonsterState::MOVE)
	{
		if (m_iShootTime > m_iAttackTerm)
		{
			MarkSHOOT();
			m_iShootTime = 0;
		}

		else
		{
			m_iShootTime++;
		}
	}
	
	//std::for_each(m_pSwordList.begin(), m_pSwordList.end(), [](auto& _pSword) {
	//	_pSword->Update();
	//	});

	MotionChange();

	CBoss::Update();
	return (int32)EObjectState::NODEAD;
}

void CMarkoth::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);
	m_bBlockMotionChange = false;

	if (m_isShowAppearEffect)
		m_pAppearEffect->LateUpdate();

	if (m_showEffect)
		m_pHitCrack->LateUpdate();

	//std::for_each(m_pSwordList.begin(), m_pSwordList.end(), [](auto& _pSword) {
	//	_pSword->LateUpdate();
	//	});

	switch (m_eCurState)
	{
	case EMonsterState::IDLE:
		m_isVisible = false;
		m_cHitBox->SetCanCollision(false);
		break;

	case EMonsterState::APPEAR:
		m_isVisible = true;
		m_cHitBox->SetCanCollision(false);
		MarkAPPEAR();
		break;

	case EMonsterState::SPAWN:
		m_isVisible = true;
		m_cHitBox->SetCanCollision(true);
		MarkSPAWN();
		break;

	case EMonsterState::MOVE:
		m_isVisible = true;
		m_cHitBox->SetCanCollision(true);
		MarkMOVE();
		break;

	case EMonsterState::ROTATE:
		m_isVisible = true;
		m_cHitBox->SetCanCollision(true);
		MarkROTATE();
		break;

	case EMonsterState::DEAD:
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
			m_bBlockMotionChange = true;
		m_isVisible = true;
		m_cHitBox->SetCanCollision(false);
		MarkDEAD();
		break;

	default:
		break;
	}


	if (!m_bBlockMotionChange)
		__super::Move_Frame();

	CBoss::LateUpdate();
}

void CMarkoth::Render(HDC _hdc)
{
	if (!m_isVisible) return;

	if (m_showEffect)
		m_pHitCrack->Render(_hdc);

	if (m_isShowAppearEffect)
		m_pAppearEffect->Render(_hdc);

	//std::for_each(m_pSwordList.begin(), m_pSwordList.end(), [_hdc](auto& _pSword) {
	//	_pSword->Render(_hdc);
	//	});

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

	//CBoss::Render(_hdc);

	m_tFrame.iMotion = 0;
}


void CMarkoth::Release()
{
	SAFE_DELETE(m_pAppearEffect);
	SAFE_DELETE(m_cHitBox);
	SAFE_DELETE(m_pHitCrack);

	//std::for_each(m_pSwordList.begin(), m_pSwordList.end(), [](auto& _pSword) {
	//	_pSword->Release();
	//	SAFE_DELETE<CObject*>(_pSword);
	//	});
	//m_pSwordList.clear();

	__super::Release();
}

void CMarkoth::MotionChange()

{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case EMonsterState::IDLE:
			
			m_cHitBox->SetCanCollision(false);

			m_tPosition = { 950.f, 600.f };
			m_tSize = m_tOriginSize;

			m_pFrameKey = L"MarkMOVE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			m_bBlockMotionChange = true;
			break;

		case EMonsterState::APPEAR:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::MONSTER, g_fVolume);

			m_cHitBox->SetCanCollision(false);
			m_tPosition = { 950.f, 600.f };
			m_tSize = m_tOriginSize;

			m_pFrameKey = L"MarkMOVE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			m_bBlockMotionChange = false;
			break;

		case EMonsterState::MOVE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::MONSTER, g_fVolume);

			m_cHitBox->SetCanCollision(true);
			m_tSize = m_tOriginSize;

			m_pFrameKey = L"MarkMOVE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			m_bBlockMotionChange = false;
			break;

		case EMonsterState::SPAWN:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::MONSTER, g_fVolume);

			m_cHitBox->SetCanCollision(false);
			m_tSize = m_tOriginSize;

			m_pFrameKey = L"MarkMOVE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			m_bBlockMotionChange = false;
			break;

		case EMonsterState::ROTATE:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordJumpGround.wav", EChannelID::MONSTER, g_fVolume);

			m_cHitBox->SetCanCollision(false);
			m_tSize = { 448.f, 290.f };

			m_pFrameKey = L"MarkROTATE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			m_bBlockMotionChange = false;
			break;

		case EMonsterState::DEAD:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordArrive.wav", EChannelID::MONSTER, g_fVolume);

			m_pFrameKey = L"MarkDEAD";

			m_tSize = { 298.f, 420.f };
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
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

void CMarkoth::MarkIDLE()
{
}

void CMarkoth::MarkAPPEAR()
{
	m_eCurState = EMonsterState::APPEAR;

	m_isVisible = true;
	m_isShowAppearEffect = true;


	if (m_iAppearTime < 300)
	{
		++m_iAppearTime;
		if (m_iAppearTime > 120) m_isShowAppearEffect = false;
	}

	else
	{
		m_isShowAppearEffect = false;
		m_iAppearTime = 0;
		m_eCurState = EMonsterState::MOVE;
	}

}

void CMarkoth::MarkSPAWN()
{
	m_eCurState = EMonsterState::SPAWN;

	m_isVisible = true;
	m_showEffect = false;

	if (m_iSpawnTime < 500)
	{
		++m_iSpawnTime;
	}
	else
	{
		m_iSpawnTime = 0;
		m_eCurState = EMonsterState::MOVE;
	}
}

void CMarkoth::MarkMOVE()
{
	m_bStartMove = true;

	if (m_iMoveTime % 200 == 0  ||
		m_tPosition.m_fX < 200  ||
		m_tPosition.m_fX > 1700 ||
		m_tPosition.m_fY < 300  ||
		m_tPosition.m_fY > 750)
	{
		// X값 랜덤
		m_fRandValueX = rand() % 5 + 2;
		// Y값 랜덤
		m_fRandValueY = rand() % 5 + 1;

		// 범위 밖으로 나가면 부호 고정
		// 그렇지 않으면 부호 랜덤
		if (m_tPosition.m_fX < 400) m_iRandSignX = 1;
		else if (m_tPosition.m_fX > 1500) m_iRandSignX = -1;
		else m_iRandSignX = rand() % 3 - 1;

		if (m_tPosition.m_fY < 300) m_iRandSignY = 1;
		else if (m_tPosition.m_fY > 750) m_iRandSignY = -1;
		else m_iRandSignY = rand() % 3 - 1;

		// 이동 벡터 설정
		m_tMove = { m_iRandSignX * m_fRandValueX, m_iRandSignY * m_fRandValueY };
		
		m_iMoveTime -= 200;
	}

	// 이동
	m_tPosition += m_tMove;

	// 히트박스 같이 움직이기
	m_cHitBox->SetPosition(m_tPosition);
	m_cHitBox->SetSize({ 180.f, 300.f });

	++m_iMoveTime;
}

void CMarkoth::MarkROTATE()
{
	m_eCurState = EMonsterState::ROTATE;
	++m_iRotateTime;

	if (m_iRotateTime == 50)
	{
		// 생성
		for (int i = 0; i < 8; ++i)
		{
			CObject* m_pSword = new CMarkBall;
			m_pSword->SetSize({ 105.f, 113.f });
			m_pSword->setFrameKey(L"MarkBALL_Y", 7, 70);
			dynamic_cast<CMarkBall*>(m_pSword)->SetProjectileType(EProjectileType::ROTATEBALL);
			m_pSword->Initialize();
			m_pSword->SetPosition(m_tPosition);
			dynamic_cast<CMarkBall*>(m_pSword)->SetDirectioin(vDir[i]);
			CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSword);
		}
	}
	
	else if (m_iRotateTime > 150)
	{
		m_iRotateTime = 0;
		m_eCurState = EMonsterState::MOVE;
	}
}

void CMarkoth::MarkSHOOT()
{
	int iSpawnCase = rand() % 3;

	CObject* m_pSword = new CMarkBall;
	m_pSword->SetSize({ 105.f, 113.f });
	m_pSword->setFrameKey(L"MarkBALL", 7, 70);
	dynamic_cast<CMarkBall*>(m_pSword)->SetProjectileType(EProjectileType::BALL);
	
	m_tSwordMove = CPlayer::GetInstance()->GetPosition();

	switch (iSpawnCase)
	{
	case 0:
		m_pSword->SetPosition({ m_tSwordMove.m_fX - 500.f, m_tSwordMove.m_fY });
		break;

	case 1:
		m_pSword->SetPosition({ m_tSwordMove.m_fX + 500.f, m_tSwordMove.m_fY });
		break;

	case 2:
		m_pSword->SetPosition({ m_tSwordMove.m_fX, m_tSwordMove.m_fY - 500.f });
		break;
	}
	m_pSword->Initialize();
	//m_pSwordList.push_back(m_pSword);
	CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_pSword);
}

void CMarkoth::MarkDEAD()
{
	if (m_iDeadTime < 300)
	{
		++m_iDeadTime;
	}

	else
	{
		dynamic_cast<CArena*>(SCENE->GetCurrentScene())->KillBoss();
		m_iDeadTime = 0;
		m_eCurState = EMonsterState::IDLE;
	}
}

//void CMarkoth::LordNotVisible()
//{
//	m_eCurState = EMonsterState::NOTVISIBLE;
//
//	// 어택 텀 두기
//	if (m_iWaitingTime < m_iAttackTerm)
//	{
//		++m_iWaitingTime;
//	}
//
//	// 텀 끝나면 다음 공격 세팅
//	else
//	{
//		// 개인 공격인지
//		if (m_isSolo)
//		{
//			//m_eCurState = (EMonsterState::WALL_TOP);
//			//m_eCurState = (EMonsterState::WALL_BOTTOM);
//			// 랜덤 돌려서 다음 공격 설정
//			m_eCurState = (EMonsterState)(rand() % 4 + 4);
//		}
//
//		// 합동 공격인지
//		else
//		{
//			// 합동 공격이면 4, 5, 6, 7, 6, 5, 4, 5, 6, 7, ... 순서로 공격
//			m_eCurState = m_eGroupAttack;
//			if (EMonsterState::WALL_BOTTOM == m_eGroupAttack)
//				m_iGroupAttack = -1;
//			else if (EMonsterState::DASH_BEFORE == m_eGroupAttack)
//				m_iGroupAttack = 1;
//			m_eGroupAttack = (EMonsterState)((int)m_eGroupAttack + m_iGroupAttack);
//		}
//
//		m_iWaitingTime = 0;
//	}
//}

void CMarkoth::OnCollided(CObject* _pObject)
{
}

void CMarkoth::OnCollided(CObject* _pObject, EDirection _eDirection)
{
	switch (_pObject->GetObjectType())
	{
	case EObjectType::TILE:
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
		if (setDamage(1))
		{
			CPlayer::GetInstance()->gainSoul(10);
			// 하얗게 처리
			m_tFrame.iMotion = 1;

			m_pHitCrack->SetPosition(m_tPosition);
			m_pHitCrack->SetSize({ 699.f, 140.f });
			m_pHitCrack->setFrameKey(L"HitCrack", 2, 70);
			m_showEffect = true;
			m_iEffectTime = 0;
		}

		// 죽은 경우
		else
		{
			CPlayer::GetInstance()->gainSoul(10);
			// 여기가 부메랑 타격 없게 만드는 타이밍
			SCENE->GetCurrentScene()->SetBlockProjectile();
			// 다잉 모션
			m_eCurState = EMonsterState::DEAD;
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"E_BossDead.wav", EChannelID::MONSTERVOICE, g_fVolume);
			CAMERA->CameraShaking(200);
		}

		break;
	}
}