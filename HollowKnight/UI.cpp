#include "pch.h"
#include "UI.h"

void CUI::Initialize()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::UI;
		m_eRender = ERenderID::UI;
	}
}

int CUI::Update()
{
	//// 종단속도 지정
	//if (m_fDt < 0.05f)
	//{
	//	m_fDt += 0.001f;
	//	m_tVel = m_tVel + m_tGravity * m_fDt;
	//}

	return (int32)EObjectState::NODEAD;
}

void CUI::LateUpdate()
{
}

void CUI::Render(HDC _hdc)
{
}

void CUI::Release()
{
}
