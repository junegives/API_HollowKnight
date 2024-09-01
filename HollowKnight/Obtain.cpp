#include "pch.h"
#include "Obtain.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "FrontBG.h"
#include "Image.h"

void CObtain::Initialize()
{
	m_iWidth = 2560;
	m_iHeight = 1440;
	CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/Obtain.dat");
	CScene::Initialize();
	CPlayer::GetInstance()->SetPosition({ 2500, 600 });
	CPlayer::GetInstance()->SetLeft(true);
	CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());
	CCameraMgr::GetInstance()->SetMaxX(1600);
	CCameraMgr::GetInstance()->SetMinX(1000);
	CCameraMgr::GetInstance()->SetMaxY(700);
	CCameraMgr::GetInstance()->SetMinY(900);

	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Obtain.wav", g_fVolume);
	// ����̹��� ����
	pFrontImage = new CFrontBG;
	pFrontImage->setFrameKey(L"Obtain_FRONT", 0, 0);
	pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
	pFrontImage->Initialize();
	AddObject(pFrontImage);

	// ���� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/SurveyText.bmp", L"SurveyText");
		m_pTextKey1 = L"SurveyText";
		m_isShowText = false;
		m_canSurvey = false;
		m_vTextPosition1 = { 880.f, 950.f };
		m_vTextSize1 = { 247.f, 193.f };
	}

	// �� �̹���
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Image/Light.bmp", L"Light");
		m_pTextKey2 = L"Light";
		m_isShowLight = true;
		m_vTextPosition2 = { 890.f, 1107.f };
		m_vTextSize2 = { 212.f, 209.f };
	}

	// ȹ�� �̹���
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Image/GetWallJump.bmp", L"GetWallJump");
		m_pTextKey3 = L"GetWallJump";
		m_isShowGet = false;
		m_vTextPosition3 = { 600.f, 100.f };
		m_vTextSize3 = { 797.f, 800.f };
	}
}

int CObtain::Update()
{
	// �÷��̾� ��ġ ��� �޾ƿͼ�
	// m_fX�� ���� �̻��̸� bool ���� true�� ���� image show
	float fLocation = CPlayer::GetInstance()->GetPosition().m_fX;
	float fLocationY = CPlayer::GetInstance()->GetPosition().m_fY;

	if (!CPlayer::GetInstance()->GetCanWallJump())
	{
		m_isShowLight = true;
	}
	else
	{
		m_isShowLight = false;
	}

	if (fLocation > 900 && fLocation < 1300 && fLocationY > 1100 && m_isShowLight)
	{
		m_canSurvey = true;
		m_isShowText = true;
	}

	else
	{
		m_canSurvey = false;
		m_isShowText = false;
	}

	if (m_isShowGet)
	{
		m_iShowTime++;
		// �ر� �����ֱ� ������ �ð�
		if (m_iShowTime > 400)
		{
			CSoundMgr::Get_Instance()->StopSound(EChannelID::MONSTER);
			m_isShowGet = false;
			CPlayer::GetInstance()->setBlockKeyInput(false);
		}
	}

	Survey();

	CSoundMgr::Get_Instance()->PlaySound(L"BGM_ObtainBack.wav", EChannelID::BGMBACK, g_fVolume);
	return CScene::Update();
}

void CObtain::LateUpdate()
{
	if (m_isShowGet)
	{
		m_isShowText = false;
		m_isShowLight = false;
	}

	//if (m_isShowStore)
	//	m_pStoreBoard->SetVisible(true);
	//else
	//	m_pStoreBoard->SetVisible(false);

	CScene::LateUpdate();

}

void CObtain::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"Obtain");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);

	// �� ���
	if (m_isShowLight)
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

	if (m_isShowText)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey1);

		Vector vRenderPos = CAMERA->GetRenderPos(m_vTextPosition1);

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

	if (m_isShowGet)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey3);

		GdiTransparentBlt(_hDC,
			m_vTextPosition3.m_fX,
			m_vTextPosition3.m_fY,
			(int)m_vTextSize3.m_fX,
			(int)m_vTextSize3.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize3.m_fX,
			(int)m_vTextSize3.m_fY,
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
	}
}

void CObtain::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CScene::Release();
}

void CObtain::Survey()
{
	// ���簡 ����Ǵ� ����
	if (m_canSurvey)
	{
		// ������Ű ������ ����
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			CSoundMgr::Get_Instance()->StopSound(EChannelID::BGM);
			CSoundMgr::Get_Instance()->PlaySound(L"K_Success.wav", EChannelID::MONSTER, g_fVolume);
			m_isShowGet = true;
			CPlayer::GetInstance()->SetCanWallJump(true);
			// �÷��̾� �ൿ ����
			CPlayer::GetInstance()->setBlockKeyInput(true);
			std::cout << "���� ����" << std::endl;
		}
	}
}
