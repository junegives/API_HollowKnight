#include "pch.h"
#include "Skill.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraMgr.h"

void CSkill::Initialize()
{
	// 타입 관리
	{
		m_eObjectType = EObjectType::SKILL;
		m_eRender = ERenderID::EFFECT;
	}

	// 히트 박스 관리
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 100.f, 100.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}
}

int CSkill::Update()
{
	if (!m_isVisible)
	{
		m_cHitBox->SetSize({ 0.f, 0.f });
		return (int32)EObjectState::NODEAD;
	}
	switch ((int)m_eDir)
	{
	case (int)EDirection::LEFT:
		SetPosition(CPlayer::GetInstance()->GetPosition() + Vector{-100.f, 0.f});
		m_cHitBox->SetSize({ 130.f, 100.f });
		break;

	case (int)EDirection::RIGHT:
		SetPosition(CPlayer::GetInstance()->GetPosition() + Vector{ 100.f, 0.f });
		m_cHitBox->SetSize({ 130.f, 100.f });
		break;

	case (int)EDirection::UP:
		SetPosition(CPlayer::GetInstance()->GetPosition() + Vector{ 0.f, -100.f });
		m_cHitBox->SetSize({ 150.f, 150.f });
		break;

	case (int)EDirection::DOWN:
		SetPosition(CPlayer::GetInstance()->GetPosition() + Vector{ 0.f, 100.f });
		m_cHitBox->SetSize({ 150.f, 150.f });
		break;
	}
	m_cHitBox->SetPosition(m_tPosition);

	if (m_iShowTime < 20)
	{
		++m_iShowTime;
		return (int32)EObjectState::NODEAD;
	}
	else
	{
		m_isVisible = false;
		return (int32)EObjectState::DEAD;
	}
}

void CSkill::LateUpdate()
{
	if (!m_isVisible) return;

	__super::Move_Frame();
}

void CSkill::Render(HDC _hDC)
{
	if (!m_isVisible) return;

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

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

void CSkill::Release()
{
	SAFE_DELETE(m_cHitBox);
}

void CSkill::OnCollided(CObject* _pObject)
{
}

void CSkill::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}
