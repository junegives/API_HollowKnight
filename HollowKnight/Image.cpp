#include "pch.h"
#include "Image.h"
#include "BmpMgr.h"
#include "CameraMgr.h"

void CImage::Initialize()
{
	m_eObjectType = EObjectType::IMAGE;
	m_eRender = ERenderID::FRONT_UI;
	m_isVisible = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iMotion = 0;

	if (m_pFrameKey == L"StoreArrow") m_eRender = ERenderID::FRONT_FRONT_UI;
}

int CImage::Update()
{
	if (m_iCountTime < m_iMovingTime - 1)
	{
		m_iCountTime++;

		switch (m_eMoveDir)
		{
		case EDirection::LEFT:
			break;
		case EDirection::UP:
			m_tPosition.m_fY -= (m_fMoveAmount / m_iMovingTime);
			break;
		case EDirection::RIGHT:
			break;
		case EDirection::DOWN:
			m_tPosition.m_fY += (m_fMoveAmount / m_iMovingTime);
			break;
		default:
			break;
		}
	}
	else
	{
		m_isMoving = false;
	}

	return 0;
}

void CImage::LateUpdate()
{
}

void CImage::Render(HDC _hDC)
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

void CImage::Release()
{
}

void CImage::MotionChange()
{
}

void CImage::OnCollided(CObject* _pObject)
{
}

void CImage::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}

bool CImage::MoveImage(EDirection _eDir, float _fAmount, int _iTime)
{
	if (m_isMoving) return false;

	m_isMoving = true;
	m_iCountTime = 0;
	m_fMoveAmount = _fAmount;
	m_iMovingTime = _iTime;
	m_eMoveDir = _eDir;

	return true;
}
