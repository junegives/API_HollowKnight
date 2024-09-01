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
	// ũ�� ����
	{
		m_iWidth = 1920;
		m_iHeight = 1080;
		m_iWidth = 2050;
		m_iHeight = 1150;
	}

	// �Ŵ��� ����
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

	// ����̹��� ����
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"Arena_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// ����
	{
		m_pMarkoth = new CMarkoth;
		m_pMarkoth->SetPosition({ 960.f, 500.f });
		m_pMarkoth->SetSize({ 280.f, 420.f });
		m_pMarkoth->Initialize();
		AddObject(m_pMarkoth);
	}

	// ���� ����
	//{
	//	m_hVideo = MCIWndCreate(g_hWnd,		// �θ� â�� �ڵ�
	//		nullptr,	// �����츦 ����ϴ� �ν��Ͻ� �ڵ�(null�� ��� �ʱ�ȭ â�� �⺻ �ν��Ͻ� ����)
	//		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // ��� �ɼ�(WS_CHILD : �������� �ڳ� â�� ����, WS_VISIBLE : ��� ȭ�鿡 �����Ͽ� ��� MCIWNDF_NOPLAYBAR : �÷��̸� �ٸ� �������� ����)
	//		L"../Resource/Video/Outro.wmv");	// ����� ������ ���

	//	// �������� ����� ũ�⸦ ����
	//	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	//}
}

int CArena::Update()
{
	if (m_bBossEnd)
		return 3;

	// ó���� �ƹ��͵� ���ٰ� 500 �Ѿ�� ���������� �ڼ�ġ�� �̵� ����
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

		// 1. �ڼ� ��׶��� ���� �����ϸ鼭 ��� �ٲ�
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
		//		// �������� ���� ��
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

	//// ���� ������ ���
	//MCIWndPlay(m_hVideo);
}