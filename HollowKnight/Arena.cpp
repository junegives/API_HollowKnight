#include "pch.h"
#include "Arena.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "CameraMgr.h"
#include "FrontBG.h"
#include "Markoth.h"

void CArena::Initialize()
{
	// 크기 관리
	{
		m_iWidth = 1920;
		m_iHeight = 1080;
		m_iWidth = 2050;
		m_iHeight = 1150;
	}

	// 매니저 관리
	{
		CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/Arena.dat");
		CScene::Initialize();
		CPlayer::GetInstance()->SetPosition({ 150.f, 988.523f });
		CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());
		CCameraMgr::GetInstance()->SetMaxX(1025);
		CCameraMgr::GetInstance()->SetMinX(1025);
		CCameraMgr::GetInstance()->SetMaxY(620);
		CCameraMgr::GetInstance()->SetMinY(620);
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Arena.wav", g_fVolume);
	}

	// 배경이미지 앞쪽
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"Arena_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// 보스
	{
		m_pMarkoth = new CMarkoth;
		m_pMarkoth->SetPosition({ 960.f, 500.f });
		m_pMarkoth->SetSize({ 280.f, 420.f });
		m_pMarkoth->Initialize();
		AddObject(m_pMarkoth);
	}

	// 엔딩 영상
	//{
	//	m_hVideo = MCIWndCreate(g_hWnd,		// 부모 창의 핸들
	//		nullptr,	// 윈도우를 사용하는 인스턴스 핸들(null인 경우 초기화 창의 기본 인스턴스 정보)
	//		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // 모양 옵션(WS_CHILD : 종속적인 자녀 창의 형태, WS_VISIBLE : 즉시 화면에 갱신하여 출력 MCIWNDF_NOPLAYBAR : 플레이를 바를 생성하지 않음)
	//		L"../Resource/Video/Outro.wmv");	// 재생할 파일의 경로

	//	// 동영상을 재생할 크기를 설정
	//	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	//}
}

int CArena::Update()
{
	if (m_bBossEnd)
		return 3;

	// 처음엔 아무것도 없다가 500 넘어가면 조용해지고 박수치고 이동 막음
	if (!m_bBossStart)
	{
		if (CPlayer::GetInstance()->GetPosition().m_fX > 500)
		{
			StartBoss();
			m_bBossStart = true;
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"E_Crowd.wav", EChannelID::BGM, g_fVolume);
			CPlayer::GetInstance()->setBlockKeyInput(true);
		}
	}

	else
	{
		m_iBossTime = GetTickCount64() - m_iBossStartTime;

		// 1. 박수 사그라들면 보스 등장하면서 브금 바뀜
		if (!m_bBossAppear && m_iBossTime > 9000)
		{
			CSoundMgr::Get_Instance()->StopAll();
			CPlayer::GetInstance()->setBlockKeyInput(false);
			CSoundMgr::Get_Instance()->PlayBGM(L"BGM_FinalBoss.wav", g_fVolume);
			dynamic_cast<CMarkoth*>(m_pMarkoth)->MarkAPPEAR();
			CAMERA->CameraShaking(100);
			m_bBossAppear = true;
		}

		// 2. 

		//if (m_iBossTime > 0)
		//{
		//	++m_iBossTime;

		//	if (!m_bBossAppear && m_iBossTime > 5000)
		//	{
		//		CSoundMgr::Get_Instance()->PlaySound(L"BGM_MantisLord.wav", EChannelID::BGM, g_fVolume);
		//		dynamic_cast<CMarkoth*>(m_pMarkoth)->MarkAPPEAR();
		//		CAMERA->CameraShaking(50);
		//		m_bBossAppear = true;
		//	}
		//}

		//if (m_iBossEndTime > 0)
		//{
		//	if (!m_bBossComplete && m_iBossEndTime > 1000)
		//	{
		//		CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordBow.wav", EChannelID::MONSTERVOICE, g_fVolume);
		//	
		//		// 최종보스 종료 후
		//		m_bBossComplete = true;
		//	}
		//}
	}

	return CScene::Update();
}

void CArena::LateUpdate()
{
	CScene::LateUpdate();
}

void CArena::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"Arena");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);
}

void CArena::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CScene::Release();
}

void CArena::StartBoss()
{
	m_iBossStartTime = GetTickCount64();
}

void CArena::KillBoss()
{
	CPlayer::GetInstance()->SetFinalBossComplete(true);

	CSoundMgr::Get_Instance()->StopAll();

	m_bBossEnd = true;

	//// 실제 동영상 재생
	//MCIWndPlay(m_hVideo);
}