#include "pch.h"
#include "UIInven.h"
#include "BmpMgr.h"
#include "Player.h"
#include "Image.h"
#include "SceneMgr.h"
#include "Scene.h"

void CUIInven::Initialize()
{
	// ��ġ, ũ�� ����
	{
		m_tPosition = { 1700.f, 130.f };
		m_tSize = { 290.f, 100.f };
	}

	// �̹��� ����
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();

		m_pFrameKey = L"UIInventory";
	}

	CUI::Initialize();
}

int CUIInven::Update()
{
	//MotionChange();
	return (int32)EObjectState::NODEAD;
}

void CUIInven::LateUpdate()
{
	//__super::Move_Frame();
}

void CUIInven::Render(HDC _hdc)
{
	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(_hdc,
		m_tPosition.m_fX - m_tSize.m_fX / 2,
		m_tPosition.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
}

void CUIInven::Release()
{
}