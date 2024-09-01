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
	// ũ�� ����
	{
		m_iWidth = 13000;
		m_iHeight = 2737;
	}

	// �Ŵ��� ����
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

	// ����̹��� ����
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"CrossRoad_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// ����
	{
		// ���� 1 : ���ٴϴ� ����
		CMonster* pCrawlid = new CCrawlid;
		pCrawlid->SetPosition({ 3300, 2300 });
		pCrawlid->SetSize({ 151.f, 107.f });
		pCrawlid->Initialize();
		AddObject(pCrawlid);

		// ���� 2 : �뽬 ����
		CMonster* pDashBug = new CDashBug;
		pDashBug->SetPosition({ 6000, 2200 });
		pDashBug->SetSize({ 150.f, 150.f });
		pDashBug->Initialize();
		AddObject(pDashBug);
	}
	// ���� 3 : ���ƴٴϴ� �ĸ� (�ܼ� �����)
	// ���� 4 : �÷��̾� �������� �Ѿ� ��� �ĸ� (���� �Ÿ� ����)

	// �ö󰡱� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/ClimbText.bmp", L"ClimbText");
		m_pTextKey1 = L"ClimbText";
		m_isShowText1 = false;
		m_canClimb = false;
		m_vTextPosition1 = { 3720.f, 1650 };
		m_vTextSize1 = { 199.f, 164.f };
	}

	// �����ϱ� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/SurveyText.bmp", L"SurveyText");
		m_pTextKey2 = L"SurveyText";
		m_isShowText2 = false;
		m_canSurvey = false;
		m_vTextPosition2 = { 9960.f, 1500 };
		m_vTextSize2 = { 247.f, 193.f };
	}

	// ���� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/EnterText.bmp", L"EnterText");
		m_pTextKey3 = L"EnterText";
		m_isShowText3 = false;
		m_canEnter = false;
		m_vTextPosition3 = { 9985.f, 1500 };
		m_vTextSize3 = { 211.f, 146.f };
	}

	// Ű�� �ʿ��մϴ�
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
		// Ű�� �ʿ��մϴ� �����ֱ� ������ �ð�
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
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
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
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
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
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
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
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
	}
}

void CCrossRoad::Release()
{
	CSoundMgr::Get_Instance()->StopSound(EChannelID::BGM);
	CScene::Release();
}

void CCrossRoad::Climb()
{
	// ���� �� �ִ� ����
	if (m_canClimb)
	{
		// ������Ű ������ ���� ����
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
	// ���� �� �ִ� ����
	if (m_canSurvey)
	{
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			// �� ����
			if (CPlayer::GetInstance()->isHaveKey())
			{
				// ö�� �Ҹ� ����
				CSoundMgr::Get_Instance()->PlaySound(L"E_DoorOpen.wav", EChannelID::BOSSEFFECT, g_fVolume);
				m_isOpen = true;
			}

			// ���� ��������� ��Ʈ
			else
			{
				CSoundMgr::Get_Instance()->PlaySound(L"K_Success.wav", EChannelID::BOSSEFFECT, g_fVolume);
				m_isShowNeedKey = true;
				// �÷��̾� �ൿ ����
				CPlayer::GetInstance()->setBlockKeyInput(true);
			}
		}
	}
}

void CCrossRoad::Enter()
{
	// �� �� �ִ� ����
	if (m_canEnter)
	{
		// ������Ű ������ �Ʒ��� ����
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::ARENA);
			CPlayer::GetInstance()->SetPosition({ 150.f, 988.523f });
			m_bSceneChanged = true;
		}
	}
}
