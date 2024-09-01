#include "pch.h"
#include "HP.h"
#include "BmpMgr.h"
#include "KeyMgr.h"

void CHP::Initialize()
{
	// ��ġ, ũ�� ����
	{
		m_tPosition = { 280.f + (float)m_iIndex * 80.f, 130.f };
		m_tSize = { 80.f, 175.f };
	}
	// �̹��� ����
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
	// ü�� ���� UI�� ����� ���
	if (m_isChangeEnd)
	{
		// �ش� ü�� UI�̰� �� ü���� ���
		if (m_isEmpty)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount64();

			m_pFrameKey = L"UIHealthEmpty";
		}

		// �ش� ü�� UI�� ���� ü���� ���
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
		RGB(255, 0, 0));	// �����ϰ��� �ϴ� ����
}

void CHP::Release()
{
}

// ������ LateUpdate���� ȣ�����ֱ�
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

// ������ LateUpdate���� ȣ�����ֱ�
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