#include "pch.h"
#include "Store.h"
#include "CameraMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Tile.h"
#include "Player.h"
#include "SoundMgr.h"
#include "FrontBG.h"
#include "StoreBoard.h"

void CStore::Initialize()
{
	// ũ�� ����
	{
		m_iWidth = 2500;
		m_iHeight = 1406;
	}

	// �Ŵ��� ����
	{
		CTileMgr::GetInstance()->LoadTile(L"../Resource/Map/Store.dat");
		CScene::Initialize();
		CPlayer::GetInstance()->SetPosition({ 750, 1000 });
		CCameraMgr::GetInstance()->SetMaxX(1250);
		CCameraMgr::GetInstance()->SetMinX(1250);
		CCameraMgr::GetInstance()->SetMaxY(800);
		CCameraMgr::GetInstance()->SetMinY(800);
		CSoundMgr::Get_Instance()->PlaySound(L"BGM_Store.wav", EChannelID::BGM, g_fVolume);
	}

	// ����̹��� ����
	{
		pFrontImage = new CFrontBG;
		pFrontImage->setFrameKey(L"Store_FRONT", 0, 0);
		pFrontImage->SetSize({ (float)m_iWidth, (float)m_iHeight });
		pFrontImage->Initialize();
		AddObject(pFrontImage);
	}

	// ���� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Text/StoreText.bmp", L"StoreText");
		m_pTextKey = L"StoreText";
		m_isShowText = false;
		m_canOpenStore = false;
		m_vTextPosition = {1250.f, 620.f};
		m_vTextSize = {155.f, 158.f};
	}

	// ��������
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreBoardBlack.bmp", L"StoreBoard");
		m_pStoreBoard = new CStoreBoard;
		m_pStoreBoard->setFrameKey(L"StoreBoard", 0, 0);
		m_pStoreBoard->SetPosition({1500.f, 800.f});
		m_pStoreBoard->SetSize({600.f, 781.f});
		m_pStoreBoard->Initialize();
		AddObject(m_pStoreBoard);
	}

	//// ������Ʈ ����
	//{
	//	// ���� ��
	//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/Pillar.bmp", L"Wall");

	//	pWallLeft = new CWall;
	//	pWallLeft->setFrameKey(L"Wall", 0, 100);
	//	pWallLeft->SetPosition({ 1000.f, 500.f });
	//	pWallLeft->SetSize({ 174.f, 1344.f });
	//	pWallLeft->Initialize();
	//	AddObject(pWallLeft);

	//	pWallRight = new CWall;
	//	pWallRight->setFrameKey(L"Wall", 0, 100);
	//	pWallRight->SetPosition({ 2710.f, 500.f });
	//	pWallRight->SetSize({ 174.f, 1344.f });
	//	pWallRight->Initialize();
	//	AddObject(pWallRight);

	//	// ���� ��ֹ�
	//}
}

int CStore::Update()
{
	// �÷��̾� ��ġ ��� �޾ƿͼ�
	// m_fX�� ���� �̻��̸� bool ���� true�� ���� image show
	float fLocation = CPlayer::GetInstance()->GetPosition().m_fX;

	if (fLocation > 1000)
	{
		m_canOpenStore = true;
		m_isShowText = true;
	}

	else
	{
		m_canOpenStore = false;
		m_isShowText = false;
	}

	OpenStore();

	return CScene::Update();
}

void CStore::LateUpdate()
{
	if (m_isShowStore)
		m_isShowText = false;

	if (m_isShowStore)
		m_pStoreBoard->SetVisible(true);
	else
		m_pStoreBoard->SetVisible(false);

	CScene::LateUpdate();
}

void CStore::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(L"Store");

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
			RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
	}
}

void CStore::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
	CScene::Release();
}

void CStore::OpenStore()
{
	// ������ ����Ǵ� ����
	if (m_canOpenStore)
	{
		// ������ �����ִ� ����
		if (m_isShowStore)
		{
			// Q������ ������
			if (CKeyMgr::GetInstance()->Key_Down('A'))
			{
				m_isShowStore = false;
				// �÷��̾� �ൿ Ǯ��
				CPlayer::GetInstance()->setBlockKeyInput(false);
				std::cout << "���� ����" << std::endl;
			}
		}
		// ������ �������� ���� ����
		else
		{
			// ������Ű ������ ���� ����
			if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
			{
				m_isShowStore = true;
				// �÷��̾� �ൿ ����
				CPlayer::GetInstance()->setBlockKeyInput(true);
				std::cout << "���� ����" << std::endl;
			}
		}
	}
}