#include "pch.h"
#include "MantisTown.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "Monster.h"
#include "MantisYouth.h"
#include "CrawlBug.h"
#include "CameraMgr.h"
#include "MantisLord.h"
#include "Wall.h"
#include "FrontBG.h"

void CMantisTown::Initialize()
{
	// 크기 관리
	{
		m_iWidth = 7000;
		m_iHeight = 2777;
	}

	// 매니저 관리
	{
		CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/MantisTown.dat");
		CScene::Initialize();
		CPlayer::GetInstance()->SetPosition({ 6700, 600 });
		//CPlayer::GetInstance()->SetPosition({2700, 1800});
		CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());
		CCameraMgr::GetInstance()->SetMaxX(6000);
		CCameraMgr::GetInstance()->SetMinX(1000);
		CCameraMgr::GetInstance()->SetMaxY(700);
		CCameraMgr::GetInstance()->SetMinY(2200);
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_GreenPath.wav", g_fVolume);
	}

	// 배경이미지 앞쪽
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"MantisTown_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// 몬스터
	{
		// 몬스터 1 : 육지 사마귀
		// 몬스터 2 : 공중 사마귀
		CMonster* pMantisYouth = new CMantisYouth;
		pMantisYouth->SetPosition({4330, 420});
		pMantisYouth->SetSize({ 270.f, 270.f });
		pMantisYouth->Initialize();
		AddObject(pMantisYouth);

		//// 몬스터 3 : 틱틱
		//CMonster* pCrawlBug = new CCrawlBug;
		//pCrawlBug->SetPosition({ 6300, 600 });
		//pCrawlBug->SetSize({ 250.f, 250.f });
		//pCrawlBug->Initialize();
		//AddObject(pCrawlBug);
	}

	// 오브젝트 관리
	{
		// 양쪽 벽
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/Pillar.bmp", L"Wall");

		pWallLeft = new CWall;
		pWallLeft->setFrameKey(L"Wall", 0, 100);
		pWallLeft->SetPosition({ 1000.f, 500.f });
		pWallLeft->SetSize({ 174.f, 1344.f });
		pWallLeft->Initialize();
		AddObject(pWallLeft);

		pWallRight = new CWall;
		pWallRight->setFrameKey(L"Wall", 0, 100);
		pWallRight->SetPosition({ 2710.f, 500.f });
		pWallRight->SetSize({ 174.f, 1344.f });
		pWallRight->Initialize();
		AddObject(pWallRight);

		// 양쪽 장애물
	}

	// 보스
	{
		// 사마귀 군주 1
		pMantisLord1 = new CMantisLord;
		pMantisLord1->SetPosition({ 1620.f, 2085.f });
		pMantisLord1->SetSize({ 106.f, 334.f });
		pMantisLord1->Initialize();
		AddObject(pMantisLord1);

		// 사마귀 군주 2
		pMantisLord2 = new CMantisLord;
		pMantisLord2->SetPosition({ 1835.f, 2030.f });
		pMantisLord2->SetSize({ 106.f, 334.f });
		pMantisLord2->Initialize();
		AddObject(pMantisLord2);

		// 사마귀 군주 3
		pMantisLord3 = new CMantisLord;
		pMantisLord3->SetPosition({ 2050.f, 2085.f });
		pMantisLord3->SetSize({ 106.f, 334.f });
		pMantisLord3->Initialize();
		AddObject(pMantisLord3);
	}

	if (CPlayer::GetInstance()->GetMantisComplete())
	{
		m_bossComplete = true;
		dynamic_cast<CMantisLord*>(pMantisLord1)->LordBow();
		dynamic_cast<CMantisLord*>(pMantisLord2)->LordBow();
		dynamic_cast<CMantisLord*>(pMantisLord3)->LordBow();
	}
}

int CMantisTown::Update()
{
	if (m_iBossStartTime > 0)
	{
		m_iBossFightTime = GetTickCount64() - m_iBossStartTime;

		if (!m_isStand && m_iBossFightTime > 1500)
		{
			std::cout << "case 0" << std::endl;
			CSoundMgr::Get_Instance()->PlayBGM(L"BGM_MantisLord.wav", g_fVolume);
			dynamic_cast<CMantisLord*>(pMantisLord1)->LordStand();
			dynamic_cast<CMantisLord*>(pMantisLord2)->LordStand();
			dynamic_cast<CMantisLord*>(pMantisLord3)->LordStand();
			m_isStand = true;
		}
		else if (!m_isWallDown && m_iBossFightTime > 2000)
		{
			std::cout << "case 1" << std::endl;
			dynamic_cast<CWall*>(pWallLeft)->Down();
			dynamic_cast<CWall*>(pWallRight)->Down();
			m_isWallDown = true;
		}
		else if (!m_isShaking && m_iBossFightTime > 3100)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordGateDown.wav", EChannelID::HIT, g_fVolume);
			CAMERA->CameraShaking(100);
			m_isShaking = true;
		}
		else if (!m_isObstacleOpen && m_iBossFightTime > 4200)
		{
			std::cout << "case 2" << std::endl;
			m_isObstacleOpen = true;
		}
		else if (!m_isBossLeave && m_iBossFightTime > 5500)
		{
			std::cout << "case 3" << std::endl;
			TILE tWallLeft(
				pWallLeft->GetPosition().m_fX - pWallLeft->GetSize().m_fX / 2,
				pWallLeft->GetPosition().m_fY - pWallLeft->GetSize().m_fY / 2,
				pWallLeft->GetPosition().m_fX + pWallLeft->GetSize().m_fX / 2,
				pWallLeft->GetPosition().m_fY + pWallLeft->GetSize().m_fY / 2
			);
			tWallLeft.eTileType = ETileType::GROUND;
			tWallLeft.iR = 255;
			tWallLeft.iG = 255;
			tWallLeft.iB = 255;

			pWallLeftTile = new CTile(tWallLeft);
			pWallLeftTile->SetObjectType(EObjectType::TILE);
			pWallLeftTile->Initialize();
			AddObject(pWallLeftTile);

			TILE tWallRight(
				pWallRight->GetPosition().m_fX - pWallRight->GetSize().m_fX / 2,
				pWallRight->GetPosition().m_fY - pWallRight->GetSize().m_fY / 2,
				pWallRight->GetPosition().m_fX + pWallRight->GetSize().m_fX / 2,
				pWallRight->GetPosition().m_fY + pWallRight->GetSize().m_fY / 2
			);
			tWallRight.eTileType = ETileType::GROUND;
			tWallRight.iR = 255;
			tWallRight.iG = 255;
			tWallRight.iB = 255;

			pWallRightTile = new CTile(tWallRight);
			pWallRightTile->SetObjectType(EObjectType::TILE);
			pWallRightTile->Initialize();
			AddObject(pWallRightTile);

			dynamic_cast<CMantisLord*>(pMantisLord2)->SetSoloOrGroup(true, true);
			dynamic_cast<CMantisLord*>(pMantisLord2)->LordLeave();
			m_isBossLeave = true;
		}
	}

	if (m_iBossEndTime > 0)
	{
		m_iBossFightTime = GetTickCount64() - m_iBossEndTime;

		if (!m_isBow && m_iBossFightTime > 1000)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordBow.wav", EChannelID::MONSTERVOICE, g_fVolume);
			m_isBow = true;
		}

		else if (!m_isObstacleClose && m_iBossFightTime > 2000)
		{
			std::cout << "case 1" << std::endl;
			m_isObstacleClose = true;
		}

		else if (!m_isWallUp && m_iBossFightTime > 3000)
		{
			std::cout << "case 2" << std::endl;
			CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordGateOpen.wav", EChannelID::MONSTER, g_fVolume);
			dynamic_cast<CWall*>(pWallLeft)->Up();
			dynamic_cast<CWall*>(pWallRight)->Up();
			DeleteObject(pWallLeftTile);
			DeleteObject(pWallRightTile);
			m_isWallUp = true;
		}
		else if (!m_isCameraReset && m_iBossFightTime > 4000)
		{
			CAMERA->UnLock();
			m_isCameraReset = true;
		}
	}
	return CScene::Update();
}

void CMantisTown::LateUpdate()
{
	CScene::LateUpdate();

}

void CMantisTown::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"MantisTown");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);
}

void CMantisTown::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CScene::Release();
}

void CMantisTown::StartBoss()
{
	CAMERA->SlowMoveToTarget( {1860.f, 2150.f}, 50);
	m_iBossStartTime = GetTickCount64();
}

void CMantisTown::KillBoss()
{
	++m_iBossKillCnt;
	if (3 > m_iBossKillCnt) return;
	
	m_bossComplete = true;
	CPlayer::GetInstance()->SetMantisComplete(true);

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"BGM_BossWin.wav", EChannelID::BGM, g_fVolume);
	dynamic_cast<CMantisLord*>(pMantisLord1)->LordBow();
	dynamic_cast<CMantisLord*>(pMantisLord2)->LordBow();
	dynamic_cast<CMantisLord*>(pMantisLord3)->LordBow();

	m_iBossEndTime = GetTickCount64();
}

void CMantisTown::FirstBossDead()
{
	++m_iBossKillCnt;
	dynamic_cast<CMantisLord*>(pMantisLord1)->SetSoloOrGroup(false, true);
	dynamic_cast<CMantisLord*>(pMantisLord3)->SetSoloOrGroup(false, false);
	dynamic_cast<CMantisLord*>(pMantisLord1)->LordLeave();
	dynamic_cast<CMantisLord*>(pMantisLord3)->LordLeave();
}
