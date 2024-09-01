#include "pch.h"
#include "UIGeo.h"
#include "HP.h"
#include "Soul.h"
#include "UIItem.h"
#include "UIInven.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Scene.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIGeo.bmp", L"UIGeo");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHealthEmpty.bmp", L"UIHealthEmpty");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHealthFull.bmp", L"UIHealthFull");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHealthAppear.bmp", L"UIHealthAppear");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHealthBroke.bmp", L"UIHealthBroke");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHud.bmp", L"UIHud");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIHudTest.bmp", L"UIHudTest");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UISoulIncrease.bmp", L"UISoulIncrease");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UISoulDecrease.bmp", L"UISoulDecrease");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/UI/UIInventory.bmp", L"UIInventory");

	// øµ»•
	{
		pSoul = new CSoul;
		pSoul->SetOnGravity(false);
		pSoul->Initialize();
		m_UIList.push_back(pSoul);
	}
	m_iSoul = CPlayer::GetInstance()->getSoul();

	// √º∑¬
	for(int i = 0; i < MAXHP; ++i)
	{
		pHP[i] = new CHP;
		pHP[i]->SetOnGravity(false);
		dynamic_cast<CHP*>(pHP[i])->setIndex(i);
		pHP[i]->Initialize();
		m_UIList.push_back(pHP[i]);
	}
	m_iHP = CPlayer::GetInstance()->getHP() - 1;

	// ¡ˆø¿
	{
		pGeo = new CUIGeo;
		pGeo->SetOnGravity(false);
		pGeo->Initialize();
		m_UIList.push_back(pGeo);
	}
	m_iGeo = CPlayer::GetInstance()->getGeo();

	// ¿Œ∫•≈‰∏Æ
	{
		pInventory = new CUIInven;
		pInventory->SetOnGravity(false);
		pInventory->Initialize();
		m_UIList.push_back(pInventory);
	}

	// ¿Œ∫•≈‰∏Æ æ∆¿Ã≈€
	for(int i = 0; i < 3; ++i)
	{
		pItem[i] = new CUIItem;
		pItem[i]->SetOnGravity(false);
		dynamic_cast<CUIItem*>(pItem[i])->setIndex(i);
		pItem[i]->Initialize();
		m_UIList.push_back(pItem[i]);
	}
}

int CUIMgr::Update()
{
	for (auto& iter : m_UIList)
	{
		iter->Update();
	}

	return (int32)EObjectState::NODEAD;
}

void CUIMgr::LateUpdate()
{
	for (auto& iter : m_UIList)
	{
		iter->LateUpdate();
	}
}

void CUIMgr::Render(HDC _hDC)
{
	if (SCENE->GetCurSceneType() == ESceneType::GAME_START) return;

	for (auto& iter : m_UIList)
	{
		iter->Render(_hDC);
	}
}

void CUIMgr::Release()
{
	for_each(m_UIList.begin(), m_UIList.end(), SAFE_DELETE<CUI*>);
}

// ¡ˆø¿ »πµÊ
void CUIMgr::setGeo(uint32 _iGeo)
{
	m_iGeo = _iGeo;
	dynamic_cast<CUIGeo*>(pGeo)->setGeo(m_iGeo);
}

void CUIMgr::gainGeo(uint32 _iGeo)
{
	m_iGeo += _iGeo;
	dynamic_cast<CUIGeo*>(pGeo)->setGeo(m_iGeo);
}

void CUIMgr::useGeo(uint32 _iGeo)
{
	m_iGeo -= _iGeo;
	dynamic_cast<CUIGeo*>(pGeo)->setGeo(m_iGeo);
}

void CUIMgr::getItem(TCHAR* _pImageKey, int _iItemIndex)
{
	pItem[_iItemIndex]->setFrameKey(_pImageKey, 0, 200);
}

void CUIMgr::useItem(int _iItemIndex)
{
	pItem[_iItemIndex]->setFrameKey(L"Empty", 0, 200);
}

// √º∑¬ »πµÊ
void CUIMgr::gainHP()
{
	m_iHP = CPlayer::GetInstance()->getHP();
	dynamic_cast<CHP*>(pHP[m_iHP-1])->gainHP();
}

// √º∑¬ «««ÿ
void CUIMgr::loseHP()
{
	m_iHP = CPlayer::GetInstance()->getHP();
	dynamic_cast<CHP*>(pHP[m_iHP])->loseHP();
}

// øµ»• »πµÊ
void CUIMgr::gainSoul()
{
	m_iSoul = CPlayer::GetInstance()->getSoul();
	dynamic_cast<CSoul*>(pSoul)->gainSoul();
}

// øµ»• ªÁøÎ
void CUIMgr::useSoul()
{
	m_iSoul = CPlayer::GetInstance()->getSoul();
	dynamic_cast<CSoul*>(pSoul)->useSoul();
}

void CUIMgr::setEmptySoul()
{
	m_iSoul = CPlayer::GetInstance()->getSoul();
	dynamic_cast<CSoul*>(pSoul)->setEmptySoul();
}

void CUIMgr::setMaxHP()
{
	for (int i = 0; i < MAXHP; ++i)
	{
		dynamic_cast<CHP*>(pHP[i])->gainHP();
	}
	m_iHP = MAXHP - 1;
}
