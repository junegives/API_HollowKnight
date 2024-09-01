#include "pch.h"
#include "CrossRoad.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "Monster.h"
#include "Crawlid.h"
#include "DashBug.h"
#include "CameraMgr.h"
#include "FrontBG.h"
#include "Scene.h"
#include "SceneMgr.h"

void CCrossRoad::Initialize()
{
	// 크기 관리
	{
		m_iWidth = 13000;
		m_iHeight = 2737;
	}

	// 매니저 관리
	{
		CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/CrossRoad.dat");
		CScene::Initialize();
		CPlayer::GetInstance()->SetPosition({ 100, 2000 });
		//CPlayer::GetInstance()->SetPosition({2700, 1800});
		CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());
		CCameraMgr::GetInstance()->SetMaxX(12000);
		CCameraMgr::GetInstance()->SetMinX(1000);
		CCameraMgr::GetInstance()->SetMaxY(700);
		CCameraMgr::GetInstance()->SetMinY(2200);
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Crossroads1.wav", g_fVolume);
	}

	// 배경이미지 앞쪽
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"CrossRoad_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// 몬스터
	{
		// 몬스터 1 : 기어다니는 벌레
		CMonster* pCrawlid = new CCrawlid;
		pCrawlid->SetPosition({ 3300, 2300 });
		pCrawlid->SetSize({ 151.f, 107.f });
		pCrawlid->Initialize();
		AddObject(pCrawlid);

		// 몬스터 2 : 대쉬 벌레
		CMonster* pDashBug = new CDashBug;
		pDashBug->SetPosition({ 6000, 2200 });
		pDashBug->SetSize({ 150.f, 150.f });
		pDashBug->Initialize();
		AddObject(pDashBug);
	}
	// 몬스터 3 : 날아다니는 파리 (단순 따라옴)
	// 몬스터 4 : 플레이어 방향으로 총알 쏘는 파리 (적정 거리 유지)

	// 올라가기 텍스트
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/ClimbText.bmp", L"ClimbText");
		m_pTextKey1 = L"ClimbText";
		m_isShowText1 = false;
		m_canClimb = false;
		m_vTextPosition1 = { 3720.f, 1650 };
		m_vTextSize1 = { 199.f, 164.f };
	}

	// 조사하기 텍스트
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/SurveyText.bmp", L"SurveyText");
		m_pTextKey2 = L"SurveyText";
		m_isShowText2 = false;
		m_canSurvey = false;
		m_vTextPosition2 = { 9960.f, 1500 };
		m_vTextSize2 = { 247.f, 193.f };
	}

	// 들어가기 텍스트
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/EnterText.bmp", L"EnterText");
		m_pTextKey3 = L"EnterText";
		m_isShowText3 = false;
		m_canEnter = false;
		m_vTextPosition3 = { 9985.f, 1500 };
		m_vTextSize3 = { 211.f, 146.f };
	}

	// 키가 필요합니당
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/DoorText.bmp", L"DoorText");
		m_pTextKey4 = L"DoorText";
		m_isShowNeedKey = false;
		m_vTextPosition4 = { 350.f, 150.f };
		m_vTextSize4 = { 1220.f, 478.f };
	}
}

int CCrossRoad::Update()
{
	float fLocation = CPlayer::GetInstance()->GetPosition().m_fX;
	float fLocationY = CPlayer::GetInstance()->GetPosition().m_fY;

	if (fLocation > 3760 && fLocation < 3860 && fLocationY > 1600)
	{
		m_canClimb = true;
		m_isShowText1 = true;
	}
	else
	{
		m_canClimb = false;
		m_isShowText1 = false;
	}

	if (fLocation > 10000 && fLocation < 10200 && !m_isOpen)
	{
		m_canSurvey = true;
		m_isShowText2 = true;
	}
	else
	{
		m_canSurvey = false;
		m_isShowText2 = false;
	}

	if (fLocation > 10000 && fLocation < 10200 && m_isOpen)
	{
		m_canEnter = true;
		m_isShowText3 = true;
	}
	else
	{
		m_canEnter = false;
		m_isShowText3 = false;
	}

	if (m_isShowNeedKey)
	{
		m_iShowTime++;
		// 키가 필요합니다 보여주기 끝나는 시간
		if (m_iShowTime > 300)
		{
			m_isShowNeedKey = false;
			m_iShowTime = 0;
			CPlayer::GetInstance()->setBlockKeyInput(false);
		}
	}

	Climb();
	Survey();
	Enter();

	if (m_bSceneChanged) return 0;
	return CScene::Update();
}

void CCrossRoad::LateUpdate()
{
	CScene::LateUpdate();
}

void CCrossRoad::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"CrossRoad");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);
	
	if (m_isShowText1)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey1);

		Vector vRenderPos = CAMERA->GetRenderPos(m_vTextPosition1);

		//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
		//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(_hDC,
			vRenderPos.m_fX,
			vRenderPos.m_fY,
			(int)m_vTextSize1.m_fX,
			(int)m_vTextSize1.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize1.m_fX,
			(int)m_vTextSize1.m_fY,
			RGB(255, 0, 0));	// 제거하고자 하는 색상값
	}

	if (m_isShowText2)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey2);

		Vector vRenderPos = CAMERA->GetRenderPos(m_vTextPosition2);

		//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
		//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(_hDC,
			vRenderPos.m_fX,
			vRenderPos.m_fY,
			(int)m_vTextSize2.m_fX,
			(int)m_vTextSize2.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize2.m_fX,
			(int)m_vTextSize2.m_fY,
			RGB(255, 0, 0));	// 제거하고자 하는 색상값
	}

	if (m_isShowText3)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey3);

		Vector vRenderPos = CAMERA->GetRenderPos(m_vTextPosition3);

		//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
		//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(_hDC,
			vRenderPos.m_fX,
			vRenderPos.m_fY,
			(int)m_vTextSize3.m_fX,
			(int)m_vTextSize3.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize3.m_fX,
			(int)m_vTextSize3.m_fY,
			RGB(255, 0, 0));	// 제거하고자 하는 색상값
	}

	if (m_isShowNeedKey)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey4);

		//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
		//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(_hDC,
			m_vTextPosition4.m_fX,
			m_vTextPosition4.m_fY,
			(int)m_vTextSize4.m_fX,
			(int)m_vTextSize4.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize4.m_fX,
			(int)m_vTextSize4.m_fY,
			RGB(255, 0, 0));	// 제거하고자 하는 색상값
	}
}

void CCrossRoad::Release()
{
	CSoundMgr::Get_Instance()->StopSound(EChannelID::BGM);
	CScene::Release();
}

void CCrossRoad::Climb()
{
	// 오를 수 있는 상태
	if (m_canClimb)
	{
		// 윗방향키 누르면 상점 입장
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::DIRTMOUTH);
			CPlayer::GetInstance()->SetPosition({ 4000.f, 1890.f });
			m_bSceneChanged = true;
		}
	}
}

void CCrossRoad::Survey()
{
	// 오를 수 있는 상태
	if (m_canSurvey)
	{
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			// 문 열기
			if (CPlayer::GetInstance()->isHaveKey())
			{
				// 철컥 소리 나고
				CSoundMgr::Get_Instance()->PlaySound(L"E_DoorOpen.wav", EChannelID::BOSSEFFECT, g_fVolume);
				m_isOpen = true;
			}

			// 열쇠 가져오라는 멘트
			else
			{
				CSoundMgr::Get_Instance()->PlaySound(L"K_Success.wav", EChannelID::BOSSEFFECT, g_fVolume);
				m_isShowNeedKey = true;
				// 플레이어 행동 막기
				CPlayer::GetInstance()->setBlockKeyInput(true);
			}
		}
	}
}

void CCrossRoad::Enter()
{
	// 들어갈 수 있는 상태
	if (m_canEnter)
	{
		// 윗방향키 누르면 아레나 입장
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::ARENA);
			CPlayer::GetInstance()->SetPosition({ 150.f, 988.523f });
			m_bSceneChanged = true;
		}
	}
}
