#include "pch.h"
#include "FrontBG.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

void CFrontBG::Initialize()
{
	m_eObjectType = EObjectType::FRONTBG;
	m_eRender = ERenderID::FRONTGROUND;
}

int CFrontBG::Update()
{
	return 0;
}

void CFrontBG::LateUpdate()
{
}

void CFrontBG::Render(HDC _hDC)
{
	HDC		hGroundDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos({ 0.f, 0.f });

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX,
		vRenderPos.m_fY,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hGroundDC,
		0,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값
}

void CFrontBG::Release()
{
}

void CFrontBG::MotionChange()
{
}

void CFrontBG::OnCollided(CObject* _pObject)
{
}

void CFrontBG::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
