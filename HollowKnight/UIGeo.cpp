#include "pch.h"
#include "UIGeo.h"
#include "BmpMgr.h"
#include "Player.h"

void CUIGeo::Initialize()
{
	// 위치, 크기 관리
	{
		m_tPosition = { 280.f, 210.f };
		m_tSize = { 55.f, 59.f };
		m_iGeo = dynamic_cast<CPlayer*>(CPlayer::GetInstance())->getGeo();
	}

	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();

		m_pFrameKey = L"UIGeo";
	}

	CUI::Initialize();
}

int CUIGeo::Update()
{
	//MotionChange();
	return (int32)EObjectState::NODEAD;
}

void CUIGeo::LateUpdate()
{
	//__super::Move_Frame();
}

void CUIGeo::Render(HDC _hdc)
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
		RGB(255, 0, 0));	// 제거하고자 하는 색상값

	HFONT font, oldfont;
	TCHAR		szBuff[10] = L"";
	wsprintf(szBuff, L"%d", m_iGeo);
	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, 0x00ffffff);
	font = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"TrajanPro-Regular");
	oldfont = (HFONT)SelectObject(_hdc, font);
	TextOut(_hdc, 330, 185, szBuff, lstrlen(szBuff));
	SelectObject(_hdc, oldfont);
	DeleteObject(font);
}

void CUIGeo::Release()
{
}