#include "pch.h"
#include "MantisYouth.h"
#include "BmpMgr.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SoundMgr.h"
#include "CameraMgr.h"
#include "Geo.h"
#include "Tile.h"
#include "Player.h"

void CMantisYouth::Initialize()
{
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.
	// 이미지 추가
	{
		// IDLE
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthIDLE.bmp", L"MantisYouthIDLE");

		// START
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthSTART.bmp", L"MantisYouthSTART");

		// FLY
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthFLY_L.bmp", L"MantisYouthFLY_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthFLY_R.bmp", L"MantisYouthFLY_R");

		// TURN
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthTURN_L.bmp", L"MantisYouthTURN_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthTURN_R.bmp", L"MantisYouthTURN_R");

		// ATTACK
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthATTACK_L.bmp", L"MantisYouthATTACK_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthATTACK_R.bmp", L"MantisYouthATTACK_R");

		// DEAD
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthDEAD_L.bmp", L"MantisYouthDEAD_L");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Monster/MantisYouth/MantisYouthDEAD_R.bmp", L"MantisYouthDEAD_R");
	}

	// 행동 관리
	{
		m_onGravity = false;
		m_isKnockBack = false;
		m_showEffect = false;
		m_fSpeed = 3.f;
		m_bDead = false;
		m_iHP = 6;
		m_eCurState = EMonsterState::IDLE;
		m_bLeft = false;
		m_iMaxInvincibleTime = 20;
		m_iInvincibleTime = 0;
	}

	// 이미지 관리
	{
		m_tSize = { 300.f, 150.f };
		m_pFrameKey = L"MantisYouthIDLE";
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 70;
		m_tFrame.dwTime = GetTickCount64();
	}

	// 히트박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 50.f });
		m_cHitBox->SetSize({ 250.f, 100.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	__super::Initialize();
}

int CMantisYouth::Update()
{
	MotionChange();
	__super::Update();


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

void CMantisYouth::LateUpdate()
{
	m_cHitBox->SetPosition(m_tPosition);

	if (m_showEffect)
		m_pHitCrack->LateUpdate();

	switch (m_eCurState)
	{
	case EMonsterState::IDLE:
		MonsterIdle();
		break;

	case EMonsterState::STAND:
		MonsterStart();
		break;

	case EMonsterState::FLY:
		MonsterFly();
		break;

	case EMonsterState::TURN:
		MonsterTurn();
		break;

	case EMonsterState::ATTACK:
		MonsterAttack();
		break;

	case EMonsterState::DEAD:
		MonsterDead();
		break;

	default:
		break;
	}

	if (!m_bBlockMotionChange)
		__super::Move_Frame();
}

void CMantisYouth::Render(HDC _hdc)
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

void CMantisYouth::Release()
{
	SAFE_DELETE(m_cHitBox);
	__super::Release();
}

void CMantisYouth::MonsterIdle()
{
	m_cHitBox->SetSize({ 250.f, 70.f });
	m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 20.f });
	if ((m_tPosition - CPlayer::GetInstance()->GetPosition()).Length() < 500.f)
	{
		m_eCurState = EMonsterState::STAND;
	}
	// 일정 거리 이내 플레이어 탐지
}

void CMantisYouth::MonsterStart()
{
	m_cHitBox->SetSize({ 250.f, 120.f });
	m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 30.f });

	// 스타트 모션 끝나면 바로 플라이로
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eCurState = EMonsterState::FLY;
	}
}

void CMantisYouth::MonsterFly()
{
	CSoundMgr::Get_Instance()->PlaySound(L"M_MantisYouthFLY.wav", EChannelID::MONSTER, g_fVolume);
	m_cHitBox->SetSize({ 200.f, 150.f });
	m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 30.f });

	// 플레이어 따라가기
	Vector vToMove = CPlayer::GetInstance()->GetPosition() - m_tPosition;
	vToMove.m_fY -= 150.f;

	// 플레이어의 좌우가 바뀌면 turn으로 (여기서 left도 바꿔줌)
	if (m_bLeft)
	{
		vToMove.m_fX += 100.f;

		// 왼쪽을 보고 있는데, 플레이어가 더 오른쪽으로 이동한 경우
		if (m_tPosition.m_fX < CPlayer::GetInstance()->GetPosition().m_fX)
		{
			m_bLeft = false;
			m_eCurState = EMonsterState::TURN;
		}
	}
	else
	{
		vToMove.m_fX -= 100.f;

		// 오른쪽을 보고 있는데, 플레이어가 더 왼쪽으로 이동한 경우
		if (m_tPosition.m_fX > CPlayer::GetInstance()->GetPosition().m_fX)
		{
			m_bLeft = true;
			m_eCurState = EMonsterState::TURN;
		}
	}

	// 일정 거리 안에 들어오면 attack으로
	if (vToMove.Length() > 70.f)
	{
		++m_iFlyTime;
	}
	else
	{
		m_iFlyTime = 0;
		m_eCurState = EMonsterState::ATTACK;
	}
	
	if (m_iFollowTime < vToMove.Length() / m_fSpeed)
	{
		vToMove.Normalize();
		m_tPosition += vToMove * m_fSpeed;
	}
}

void CMantisYouth::MonsterTurn()
{
	m_cHitBox->SetSize({ 200.f, 150.f });
	m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 30.f });

	// turn 끝나면 바로 fly로
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_eCurState = EMonsterState::FLY;
}

void CMantisYouth::MonsterAttack()
{
	std::cout << "공격중" << std::endl;
	m_cHitBox->SetSize({ 200.f, 100.f });
	m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY});

	if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
	{
		// 8? 프레임 정도에서 공격하는듯
		// 소리 넣어주기
		if (m_tFrame.iFrameStart == 7)
		{
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisYouthATTACK.wav", EChannelID::MONSTER, g_fVolume);
		}

		if (m_tFrame.iFrameStart >= 7)
		{
			m_cHitBox->SetSize({ 300.f, 300.f });
			m_cHitBox->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + 30.f });
		}
	}
	else
	{
		m_eCurState = EMonsterState::FLY;
	}
}

void CMantisYouth::MonsterDead()
{
	CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
}

void CMantisYouth::MotionChange()
{
	m_ePreState;
	m_eCurState;

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case EMonsterState::IDLE:
			m_pFrameKey = L"MantisYouthIDLE";
			m_tSize = { 300.f,150.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EMonsterState::STAND:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTERVOICE);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisYouthSTART.wav", EChannelID::MONSTERVOICE, g_fVolume);
			m_pFrameKey = L"MantisYouthSTART";
			m_tSize = { 270.f, 270.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case EMonsterState::FLY:
			if (m_bLeft) m_pFrameKey = L"MantisYouthFLY_L";
			else m_pFrameKey = L"MantisYouthFLY_R";
			m_tSize = { 270.f, 270.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EMonsterState::ATTACK:

			if (m_bLeft) m_pFrameKey = L"MantisYouthATTACK_L";
			else m_pFrameKey = L"MantisYouthATTACK_R";
			m_tSize = { 300.f, 350.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EMonsterState::TURN:

			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisYouthFLY.wav", EChannelID::MONSTER, g_fVolume);
			if (m_bLeft) m_pFrameKey = L"MantisYouthTURN_L";
			else m_pFrameKey = L"MantisYouthTURN_R";
			m_tSize = { 200.f, 200.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		case EMonsterState::DEAD:
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTERVOICE);
			CSoundMgr::Get_Instance()->PlaySound(L"M_MonsterDEAD.wav", EChannelID::MONSTERVOICE, g_fVolume);

			if (m_bLeft) m_pFrameKey = L"MantisYouthDEAD_L";
			else m_pFrameKey = L"MantisYouthDEAD_R";
			m_tSize = { 184.f, 90.f };

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount64();

			break;

		}

		m_ePreState = m_eCurState;
	}
}


void CMantisYouth::OnCollided(CObject* _pObject)
{
}

void CMantisYouth::OnCollided(CObject* _pObject, EDirection _eDirection)
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
				m_tPosition.m_fY = _pObject->GetPosition().m_fY - _pObject->GetSize().m_fY / 2 - m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::DOWN:
				m_tPosition.m_fY = _pObject->GetPosition().m_fY + _pObject->GetSize().m_fY / 2 + m_cHitBox->GetSize().m_fY / 2;
				break;

			case EDirection::LEFT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX - _pObject->GetSize().m_fX / 2 - m_cHitBox->GetSize().m_fX / 2;
				break;

			case EDirection::RIGHT:
				m_tPosition.m_fX = _pObject->GetPosition().m_fX + _pObject->GetSize().m_fX / 2 + m_cHitBox->GetSize().m_fX / 2;
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
				/*if (m_cHitBox)
					dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);*/

				// 지오 생성
				CSoundMgr::Get_Instance()->StopSound(EChannelID::GEO);
				CSoundMgr::Get_Instance()->PlaySound(L"G_GeoRock1.wav", EChannelID::GEO, g_fVolume);

				CObject* pGeo1 = new CGeo(10);
				CObject* pGeo2 = new CGeo(10);
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