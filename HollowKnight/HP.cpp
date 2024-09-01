#include "pch.h"
#include "HP.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

void CHP::Initialize()
{
	// 위치, 크기 관리
	{
		m_tPosition = { 280.f + (float)m_iIndex * 80.f, 130.f };
		m_tSize = { 80.f, 175.f };
	}
	// 이미지 관리
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 50;
		m_tFrame.dwTime = GetTickCount64();

		m_pFrameKey = L"UIHealthFull";
	}

	CUI::Initialize();
}

int CHP::Update()
{
	if (m_isMotionChange)
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_isChangeEnd = true;
		}
	}
	return (int32)EObjectState::NODEAD;
}

void CHP::LateUpdate()
{
	// 체력 변경 UI가 종료된 경우
	if (m_isChangeEnd)
	{
		// 해당 체력 UI이가 빈 체력인 경우
		if (m_isEmpty)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();

			m_pFrameKey = L"UIHealthEmpty";
		}

		// 해당 체력 UI가 꽉찬 체력인 경우
		else
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();

			m_pFrameKey = L"UIHealthFull";
		}

		m_isMotionChange = false;
		m_isChangeEnd = false;
	}

	__super::Move_Frame();
}

void CHP::Render(HDC _hdc)
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

void CHP::Release()
{
}

// 무조건 LateUpdate에서 호출해주기
void CHP::gainHP()
{
	m_isMotionChange = true;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	m_pFrameKey = L"UIHealthAppear";
	m_isEmpty = false;

}

// 무조건 LateUpdate에서 호출해주기
void CHP::loseHP()
{
	m_isMotionChange = true;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();

	m_pFrameKey = L"UIHealthBroke";
	m_isEmpty = true;

}