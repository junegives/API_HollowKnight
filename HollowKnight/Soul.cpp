#include "pch.h"
#include "Soul.h"
#include "Player.h"
#include "BmpMgr.h"

void CSoul::Initialize()
{
	// 위치, 크기 관리
	{
		m_tPosition = { 220.f, 150.f };
		m_tSize = { 260.f, 158.f };
		m_iSoul = CPlayer::GetInstance()->getSoul();
		m_iPreSoul = m_iSoul;
	}

	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();
		m_isStopFrame = true;

		m_pFrameKey = L"UISoulDecrease";
	}

	CUI::Initialize();
}

int CSoul::Update()
{
	if (m_isMotionChange)
	{
		if(m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_isChangeEnd = true;
		}
	}

	return (int32)EObjectState::NODEAD;
}

void CSoul::LateUpdate()
{
	// 체력 변경 UI가 종료된 경우
	if (m_isChangeEnd)
	{
		m_isStopFrame = true;
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		m_tFrame.iFrameEnd = m_tFrame.iFrameEnd;
		m_tFrame.iMotion = 0;
		
		m_tFrame.dwSpeed		= 50;
		m_tFrame.dwTime			= GetTickCount64();

		m_isMotionChange = false;
		m_isChangeEnd = false;
	}

	if (!m_isStopFrame)
		__super::Move_Frame();
}

void CSoul::Render(HDC _hdc)
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
}

void CSoul::Release()
{
}

void CSoul::gainSoul()
{
	if (!m_isIncreasing)
	{
		if (30 - m_tFrame.iFrameStart >= 30) return;
		m_tFrame.iFrameStart = 30 - m_tFrame.iFrameStart;
	}
	else
	{
		if (m_tFrame.iFrameStart >= 30) return;
	}

	m_isStopFrame = false;
	m_isMotionChange = true;
	m_pFrameKey = L"UISoulIncrease";
	m_isIncreasing = true;
	m_iSoul = CPlayer::GetInstance()->getSoul();
	m_tFrame.iFrameStart = m_iPreSoul / 10;
	m_tFrame.iFrameEnd = m_iSoul / 10;
	m_iPreSoul = m_iSoul;

	if (m_tFrame.iFrameEnd > 30) m_tFrame.iFrameEnd = 30;
	

	m_tFrame.dwTime = GetTickCount64();
}

void CSoul::useSoul()
{
	if (m_isIncreasing)
	{
		if (30 - m_tFrame.iFrameStart >= 30) return;
		m_tFrame.iFrameStart = 30 - m_tFrame.iFrameStart;
	}
	else
	{
		if (m_tFrame.iFrameStart >= 30) return;
	}

	m_isStopFrame = false;
	m_isMotionChange = true;
	m_pFrameKey = L"UISoulDecrease";
	m_isIncreasing = false;
	m_iSoul = CPlayer::GetInstance()->getSoul();
	m_tFrame.iFrameStart = 30 - m_iPreSoul / 10;
	m_tFrame.iFrameEnd = 30 - m_iSoul / 10;
	m_iPreSoul = m_iSoul;
	if (m_tFrame.iFrameEnd > 30) m_tFrame.iFrameEnd = 30;

	m_tFrame.dwTime = GetTickCount64();
}


void CSoul::setEmptySoul()
{
	m_isStopFrame = false;
	m_isMotionChange = true;
	m_pFrameKey = L"UISoulDecrease";
	m_isIncreasing = false;
	m_tFrame.iFrameStart = 30;
	m_tFrame.iFrameEnd = 30;

	m_iSoul = CPlayer::GetInstance()->getSoul();
	m_iPreSoul = m_iSoul;

	m_tFrame.dwTime = GetTickCount64();
}