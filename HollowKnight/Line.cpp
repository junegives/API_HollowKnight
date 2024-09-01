#include "pch.h"
#include "Line.h"
#include "ScrollMgr.h"

void CLine::Initialize()
{
	m_eObjectType = EObjectType::LINE;
}

int CLine::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CLine::LateUpdate()
{

}

void CLine::Render(HDC _hDC)
{
	//여기여기여기여기
	float fDeltaX = CScrollMgr::GetInstance()->GetScrollX();
	CGeometry::DrawColorLine(_hDC, m_tStartPosition, m_tEndPosition, m_iR, m_iG, m_iB, fDeltaX);
}

void CLine::Release()
{

}

void CLine::OnCollided(CObject* _pObject)
{

}
