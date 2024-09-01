#include "pch.h"
#include "Object.h"

void CObject::OnCollided(CObject* _pObject)
{

}

void CObject::OnCollided(CObject* _pObject, EDirection _eDirection)
{

}

void CObject::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount64())
	{
		++m_tFrame.iFrameStart;

		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CObject::setFrameKey(TCHAR* _pFrameKey, int _End, int _Speed)
{
	m_pFrameKey = _pFrameKey;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = _End;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = _Speed;
	m_tFrame.dwTime = GetTickCount64();
}
