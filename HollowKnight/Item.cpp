#include "pch.h"
#include "Item.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

void CItem::Initialize()
{
	m_eObjectType = EObjectType::ITEM;
	m_eRender = ERenderID::FRONT_UI;
	m_isVisible = false;
	m_onGravity = false;
}

int CItem::Update()
{
	return 0;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC _hDC)
{
	if (!m_isVisible) return;

	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hGroundDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값
}

void CItem::Release()
{
}

void CItem::MotionChange()
{
}

void CItem::OnCollided(CObject* _pObject)
{
}

void CItem::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
