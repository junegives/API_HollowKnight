#include "pch.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "CameraMgr.h"

void CTile::Initialize()
{
	m_eRender = ERenderID::DEBUG_UI;
	m_eObjectType = EObjectType::TILE;
	m_tPosition = { (m_tInfo.fLeft + m_tInfo.fRight) / 2, (m_tInfo.fTop + m_tInfo.fBottom) / 2 };
	m_tSize = { (abs(m_tInfo.fLeft - m_tInfo.fRight)), abs(m_tInfo.fTop - m_tInfo.fBottom) };
}

int CTile::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CTile::LateUpdate()
{

}

void CTile::Render(HDC _hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	HPEN hNewPen, hPrevPen;
	HBRUSH hNewBrush, hPrevBrush;
	hNewPen = CreatePen(PS_DOT, 5, RGB(m_tInfo.iR, m_tInfo.iG, m_tInfo.iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hPrevBrush = (HBRUSH)SelectObject(_hDC, hNewBrush);

	//CGeometry::DrawColorRect(_hDC, m_tPosition, m_tSize, m_tInfo.iR, m_tInfo.iG, m_tInfo.iB, fScrollX, fScrollY);
	CGeometry::DrawColorRect(_hDC, vRenderPos, m_tSize, m_tInfo.iR, m_tInfo.iG, m_tInfo.iB);

	::SelectObject(_hDC, hPrevBrush);
	::DeleteObject(hNewBrush);
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CTile::Release()
{

}

void CTile::OnCollided(CObject* _pObject)
{

}