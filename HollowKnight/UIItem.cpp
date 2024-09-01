#include "pch.h"
#include "UIItem.h"
#include "BmpMgr.h"

void CUIItem::Initialize()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::UI;
		m_eRender = ERenderID::FRONT_FRONT_UI;
	}

	// 위치, 크기 관리
	{
		m_tPosition = { 1605.f + (float)m_iIndex * 95.f, 130.f };
		m_tSize = { 60.f, 60.f };
	}
	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();

		m_pFrameKey = L"Empty";
	}
}

int CUIItem::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CUIItem::LateUpdate()
{

	__super::Move_Frame();
}

void CUIItem::Render(HDC _hdc)
{
	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(_hdc,
		m_tPosition.m_fX - m_tSize.m_fX / 2,
		m_tPosition.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		0,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값
}

void CUIItem::Release()
{
}