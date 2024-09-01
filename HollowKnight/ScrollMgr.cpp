#include "pch.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::_instance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f), m_fPrevX(0.f), m_fPrevY(0.f)
{

}

CScrollMgr::~CScrollMgr()
{

}

void CScrollMgr::CalcPositionX(float _fPlrX)
{
		float fTemp = 400 - _fPlrX;

		//if (!m_bLock)
		//{
		SetScrollX(m_fPrevX - fTemp);
		//}
		m_fPrevX = fTemp;
}

void CScrollMgr::CalcPositionY(float _fPlrY)
{
		float fTemp = -1500 + _fPlrY;
		//if (!m_bLock)
		//{
		SetScrollY(m_fPrevY - fTemp);
		//}
		m_fPrevY = fTemp;
}
