#include "pch.h"
#include "Dirtmouth.h"
#include "CameraMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "FrontBG.h"

void CDirtmouth::Initialize()
{
	// 크기 관리
	{
		m_iWidth = 4500;
		m_iHeight = 2531;
	}

	// 매니저 관리
	{
		CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/Dirtmouth.dat");
		CScene::Initialize();
		CPlayer::GetInstance()->SetPosition({ 1500, 1300 });
		CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());
		CCameraMgr::GetInstance()->SetMaxX(3500);
		CCameraMgr::GetInstance()->SetMinX(1000);
		CCameraMgr::GetInstance()->SetMaxY(700);
		CCameraMgr::GetInstance()->SetMinY(2000);
		CSoundMgr::Get_Instance()->PlayBGM(L"BGM_DirtMouth.wav", g_fVolume);
	}

	// 들어가기 텍스트
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/EnterText.bmp", L"EnterText");
		m_pTextKey = L"EnterText";
		m_isShowText = false;
		m_canEnterStore = false;
		m_vTextPosition = { 2540.f, 1500.f };
		m_vTextSize = { 211.f, 146.f };
	}

	// 배경이미지 앞쪽
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"Dirtmouth_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}
}

int CDirtmouth::Update()
{
	float fLocation = CPlayer::GetInstance()->GetPosition().m_fX;

	if (fLocation > 2570 && fLocation < 2730)
	{
		m_canEnterStore = true;
		m_isShowText = true;
	}

	else
	{
		m_canEnterStore = false;
		m_isShowText = false;
	}

	EnterStore();

	return CScene::Update();
}

void CDirtmouth::LateUpdate()
{
	CScene::LateUpdate();
}

void CDirtmouth::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"Dirtmouth");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);

	if (m_isShowText)
	{
		HDC		hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pTextKey);

		Vector vRenderPos = CAMERA->GetRenderPos(m_vTextPosition);

		//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
		//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

		GdiTransparentBlt(_hDC,
			vRenderPos.m_fX,
			vRenderPos.m_fY,
			(int)m_vTextSize.m_fX,
			(int)m_vTextSize.m_fY,
			hMemDC,
			0,
			0,
			(int)m_vTextSize.m_fX,
			(int)m_vTextSize.m_fY,
			RGB(255, 0, 0));	// 제거하고자 하는 색상값
	}
}

void CDirtmouth::Release()
{
	CSoundMgr::Get_Instance()->StopSound(EChannelID::BGM);
	CScene::Release();
}

void CDirtmouth::EnterStore()
{
	// 상점에 들어갈 수 있는 조건
	if (m_canEnterStore)
	{
		// 윗방향키 누르면 상점 입장
		if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
		{
			CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::STORE);
			CPlayer::GetInstance()->SetPosition({ 760, 1100 });
		}
	}
}
