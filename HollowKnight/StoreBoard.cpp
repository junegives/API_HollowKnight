#include "pch.h"
#include "StoreBoard.h"
#include "BmpMgr.h"
#include "CameraMgr.h"
#include "Image.h"
#include "Item.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CStoreBoard::~CStoreBoard()
{
	for (auto& item : m_pItemArray)
	{
		item->Release();
		SAFE_DELETE<CObject*>(item);
	}
}

void CStoreBoard::Initialize()
{
	// Ÿ�� ����
	{
		m_eObjectType = EObjectType::STOREBOARD;
		m_eRender = ERenderID::UI;
	}

	// ��� �⺯ ����
	{
		m_onGravity = false;
		m_bCanCollision = false;
	}

	// ������ �ؽ�Ʈ�̹���
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreKeyText.bmp", L"StoreKeyText");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreMaskText.bmp", L"StoreMaskText");
		m_pItemText = new CImage;
		m_pItemText->setFrameKey(L"StoreKeyText", 0, 0);
		m_pItemText->SetPosition({ 1600.f, 800.f });
		m_pItemText->SetSize({ 300.f, 456.f });
		m_pItemText->Initialize();
		SCENE->GetCurrentScene()->AddObject(m_pItemText);
	}

	// ������ �̹���
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreItemList.bmp", L"StoreItemList");
		m_pItemImage = new CImage;
		m_pItemImage->setFrameKey(L"StoreItemList", 0, 0);
		m_pItemImage->SetPosition({ 1330.f, 900.f });
		m_pItemImage->SetSize({ 200.f, 200.f });
		m_pItemImage->Initialize();
		SCENE->GetCurrentScene()->AddObject(m_pItemImage);
	}

	// ȭ��ǥ �̹���
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreArrow.bmp", L"StoreArrow");
		m_pArrowImage = new CImage;
		m_pArrowImage->setFrameKey(L"StoreArrow", 0, 0);
		m_pArrowImage->SetPosition({ 1330.f, 835.f });
		m_pArrowImage->SetSize({ 200.f, 152.f });
		m_pArrowImage->Initialize();
		SCENE->GetCurrentScene()->AddObject(m_pArrowImage);
	}

	// ���� Ȯ�� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreCheck.bmp", L"StoreCheck");
		m_pCheck = new CImage;
		m_pCheck->setFrameKey(L"StoreCheck", 0, 0);
		m_pCheck->SetPosition({ 1500.f, 1050.f });
		m_pCheck->SetSize({ 450.f, 53.f });
		m_pCheck->Initialize();
		SCENE->GetCurrentScene()->AddObject(m_pCheck);
	}

	// ���� ���� �ؽ�Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Store/StoreBuy.bmp", L"StoreBuy");
		m_pSuccess = new CImage;
		m_pSuccess->setFrameKey(L"StoreBuy", 0, 0);
		m_pSuccess->SetPosition({ 1500.f, 1050.f });
		m_pSuccess->SetSize({ 300.f, 68.f });
		m_pSuccess->Initialize();
		SCENE->GetCurrentScene()->AddObject(m_pSuccess);
	}

	// ������ ����Ʈ
	{
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Item/Key.bmp", L"Key");
		CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Item/MaskPiece.bmp", L"MaskPiece");

		// ����
		m_pItemArray[0] = new CItem;
		m_pItemArray[0]->setFrameKey(L"Key", 0, 0);
		m_pItemArray[0]->SetSize({ 60.f, 60.f });
		m_pItemArray[0]->Initialize();
		dynamic_cast<CItem*>(m_pItemArray[0])->SetInfo(1, 200);

		// ����
		m_pItemArray[1] = new CItem;
		m_pItemArray[1]->setFrameKey(L"MaskPiece", 0, 0);
		m_pItemArray[1]->SetSize({ 60.f, 60.f });
		m_pItemArray[1]->Initialize();
		dynamic_cast<CItem*>(m_pItemArray[1])->SetInfo(2, 560);
	}
}

int CStoreBoard::Update()
{
	// ���Ʒ�Ű �Է��ϸ� �ٸ� ���������� �Ѿ��
	if (CKeyMgr::GetInstance()->Key_Down(VK_UP))
	{
		CSoundMgr::Get_Instance()->StopSound(EChannelID::HIT);
		CSoundMgr::Get_Instance()->PlaySound(L"K_Change.wav", EChannelID::HIT, g_fVolume);
		m_pCheck->SetVisible(false);
		m_pSuccess->SetVisible(false);

		if (m_iItemNum != 0) {
			if (dynamic_cast<CImage*>(m_pItemImage)->MoveImage(EDirection::DOWN, 130.f, 30.f))
			{
				--m_iItemNum;
				m_pItemText->setFrameKey(L"StoreKeyText", 0, 0);
			}
		}
	}
	if (CKeyMgr::GetInstance()->Key_Down(VK_DOWN))
	{
		CSoundMgr::Get_Instance()->StopSound(EChannelID::HIT);
		CSoundMgr::Get_Instance()->PlaySound(L"K_Change.wav", EChannelID::HIT, g_fVolume);
		m_pCheck->SetVisible(false);

		if (m_iItemNum != m_iItemMax)
		{
			if (dynamic_cast<CImage*>(m_pItemImage)->MoveImage(EDirection::UP, 130.f, 30.f))
			{
				++m_iItemNum;
				m_pItemText->setFrameKey(L"StoreMaskText", 0, 0);
			}
		}
	}

	// z ������ �����ϱ�
	if (CKeyMgr::GetInstance()->Key_Down('Z'))
	{
		if (!m_pCheck->GettVisible())
		{
			// ���� �����Ͻðڽ��ϱ�?
			m_pCheck->SetVisible(true);
			CSoundMgr::Get_Instance()->StopSound(EChannelID::HIT);
			CSoundMgr::Get_Instance()->PlaySound(L"K_Confirm.wav", EChannelID::HIT, g_fVolume);
		}

		else
		{
			m_pCheck->SetVisible(false);
			if (!dynamic_cast<CItem*>(m_pItemArray[m_iItemNum])->isSelled())
			{
				// ���� Ȯ��
				if (CPlayer::GetInstance()->useGeo(dynamic_cast<CItem*>(m_pItemArray[m_iItemNum])->GetGeo()))
				{
					m_pSuccess->SetVisible(true);
					// �����ϸ� ��� �Ҹ� and NPC �����ϴٴ� �Ҹ� and ���� ������ and ȭ�� �ѱ����� ������ ǥ��
					CSoundMgr::Get_Instance()->StopSound(EChannelID::HIT);
					CSoundMgr::Get_Instance()->StopSound(EChannelID::NPC);
					CSoundMgr::Get_Instance()->PlaySound(L"K_Success.wav", EChannelID::HIT, g_fVolume);
					CSoundMgr::Get_Instance()->PlaySound(L"N_BuySuccess.wav", EChannelID::NPC, g_fVolume);
					CPlayer::GetInstance()->AddItem(m_pItemArray[m_iItemNum]);
					CPlayer::GetInstance()->SetHaveKey(true);

					CUIMgr::GetInstance()->setGeo(CPlayer::GetInstance()->getGeo());
				}
				else
				{
					// �Ұ����ϸ� ī�޶� ����ŷ and ���� ������ �Ҹ�
					CSoundMgr::Get_Instance()->StopSound(EChannelID::HIT);
					CSoundMgr::Get_Instance()->StopSound(EChannelID::NPC);
					CSoundMgr::Get_Instance()->PlaySound(L"K_Fail.wav", EChannelID::HIT, g_fVolume);
					CSoundMgr::Get_Instance()->PlaySound(L"N_BuyFail.wav", EChannelID::NPC, g_fVolume);
					CAMERA->CameraShaking(20);
				}
			}
			else
			{
				CAMERA->CameraShaking(20);
			}
		}
	}

	return 0;
}

void CStoreBoard::LateUpdate()
{
	if (!m_isVisible)
	{
		m_pItemText->SetVisible(false);
		m_pItemImage->SetVisible(false);
		m_pArrowImage->SetVisible(false);
		m_pCheck->SetVisible(false);
		m_pSuccess->SetVisible(false);
	}
	else
	{
		m_pItemText->SetVisible(true);
		m_pItemImage->SetVisible(true);
		m_pArrowImage->SetVisible(true);
	}
}

void CStoreBoard::Render(HDC _hDC)
{
	if (!m_isVisible) return;

	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	//BitBlt(_hDC, (int)fScrollX, (int)fScrollY, m_iWidth, m_iHeight, hGroundDC, 0, 0, SRCCOPY);
	//BitBlt(_hDC, vRenderPos.m_fX, vRenderPos.m_fY, m_tSize.m_fX, m_tSize.m_fY, hGroundDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hGroundDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
}

void CStoreBoard::Release()
{
}

void CStoreBoard::MotionChange()
{
}

void CStoreBoard::OnCollided(CObject* _pObject)
{
}

void CStoreBoard::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
