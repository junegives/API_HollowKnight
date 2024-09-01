#include "pch.h"
#include "Title.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "FrontBG.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void CTitle::Initialize()
{
	m_iWidth = 1920;
	m_iHeight = 1080;
	CScene::Initialize();
	CPlayer::GetInstance()->SetPosition({ -900, 2000 });
	//CPlayer::GetInstance()->SetOnGravity(false);

	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_FogCayon.wav", g_fVolume);
}

int CTitle::Update()
{
	if (CKeyMgr::GetInstance()->Key_Down(VK_RETURN))
	{
		SCENE->ChangeCurrentScene(ESceneType::DIRTMOUTH);
	}

	return CScene::Update();
}

void CTitle::LateUpdate()
{
	CScene::LateUpdate();
}

void CTitle::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"Title");

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	BitBlt(_hDC, 0, 0, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);

	CScene::Render(_hDC);
}

void CTitle::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CScene::Release();
}