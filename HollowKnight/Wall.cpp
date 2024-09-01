#include "pch.h"
#include "Wall.h"
#include "CameraMgr.h"
#include "BmpMgr.h"

void CWall::Initialize()
{
	m_eObjectType = EObjectType::WALL;
	m_eRender = ERenderID::GAMEOBJECT;
	m_fSpeed = 20.f;
}

int CWall::Update()
{
	if (m_isDOWN)
	{
		m_isVisible = true;
		m_tPosition.m_fY += m_fSpeed;
		if (m_tPosition.m_fY > 1860)
		{
			m_isDOWN = false;
		}
	}

	if (m_isUP)
	{
		m_tPosition.m_fY -= m_fSpeed;
		if (m_tPosition.m_fY < 0)
		{
			m_isVisible = false;
			m_isUP = false;
		}
	}
	return 0;
}

void CWall::LateUpdate()
{
}

void CWall::Render(HDC _hDC)
{
	if (!m_isVisible) return;

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
		RGB(21, 57, 86));	// 제거하고자 하는 색상값
}

void CWall::Release()
{
}

void CWall::MotionChange()
{
	
}

void CWall::OnCollided(CObject* _pObject)
{
}

void CWall::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}

void CWall::Down()
{
	m_isDOWN = true;
}

void CWall::Up()
{
	m_isUP = true;
}