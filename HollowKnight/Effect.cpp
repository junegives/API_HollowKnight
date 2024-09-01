#include "pch.h"
#include "Effect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

void CEffect::Initialize()
{
	m_eObjectType = EObjectType::EFFECT;
	m_eRender = ERenderID::DEBUG_UI;

	if (m_pFrameKey == L"FocusEffect") m_eRender = ERenderID::BACK_EFFECT;

	SetOnGravity(false);
}

int CEffect::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CEffect::LateUpdate()
{
	__super::Move_Frame();
}

void CEffect::Render(HDC _hDC)
{   
	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 0));	// 제거하고자 하는 색상값
}

void CEffect::Release()
{
}

void CEffect::OnCollided(CObject* _pObject)
{
}

void CEffect::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
