#include "pch.h"
#include "HitBox.h"
#include "ScrollMgr.h"
#include "CameraMgr.h"

void CHitBox::Initialize()
{
	m_eObjectType = EObjectType::HITBOX;
	m_eRender = ERenderID::DEBUG_UI;
}

int CHitBox::Update()
{
	if (m_isDeleted)
		return (int32)EObjectState::DEAD;
	else
		return (int32)EObjectState::NODEAD;
}

void CHitBox::LateUpdate()
{
}

void CHitBox::Render(HDC _hDC)
{
	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	HPEN hNewPen, hPrevPen;
	HBRUSH hNewBrush, hPrevBrush;
	hNewPen = CreatePen(PS_DOT, 5, RGB(255, 0, 0));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hPrevBrush = (HBRUSH)SelectObject(_hDC, hNewBrush);

	//CGeometry::DrawColorRect(_hDC, m_tPosition, m_tSize, 255, 0, 0, (float)fScrollX, (float)fScrollY);
	CGeometry::DrawColorRect(_hDC, vRenderPos, m_tSize, 255, 0, 0);

	::SelectObject(_hDC, hPrevBrush);
	::DeleteObject(hNewBrush);
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CHitBox::Release()
{
}

void CHitBox::OnCollided(CObject* _pObject)
{
}

void CHitBox::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
