#include "pch.h"
#include "Creature.h"
#include "HitBox.h"
#include "UIMgr.h"

void CCreature::Initialize()
{
	m_eRender = ERenderID::GAMEOBJECT;
}

int CCreature::Update()
{
	// 종단속도 지정
	if (m_fDt < 0.062f)
	{
		m_fDt += 0.002f;
		m_tVel = m_tVel + m_tGravity * m_fDt;
	}

	if (m_iInvincibleTime < m_iMaxInvincibleTime)
	{
		++m_iInvincibleTime;
	}
	else m_isInvincible = false;

	return (int32)EObjectState::NODEAD;
}

void CCreature::LateUpdate()
{

}

void CCreature::Render(HDC _hdc)
{

}

void CCreature::Release()
{
	//dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);
}

void CCreature::OnCollided(CObject* _pObject)
{
}

void CCreature::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}

// 데미지 입음
// 죽으면 false 반환
// 살아있으면 true 반환
bool CCreature::setDamage(int _iDamage)
{
	if (m_iHP - _iDamage <= 0)
	{
		m_iHP = 0;
		m_isDead = true;
	}
	else
	{
		m_iHP -= _iDamage;
		m_isDead = false;
	}
	m_isHPFull = false;

	return !m_isDead;
}