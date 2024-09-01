#include "pch.h"
#include "Boss.h"
#include "ScrollMgr.h"
#include "Effect.h"

void CBoss::Initialize()
{
	m_eObjectType = EObjectType::MONSTER;

	// ÀÌÆåÆ® °ü¸®
	{
		m_pHitCrack = new CEffect;
		m_pHitCrack->Initialize();
	}

	CCreature::Initialize();
}

int CBoss::Update()
{
	if (m_iEffectTime < 10)
	{
		++m_iEffectTime;
	}
	else m_showEffect = false;

	if (m_bDelayTime)
	{
		if (m_iDelayTime < 4)
		{
			m_tFrame.iMotion = 1;
		}

		else if (m_iDelayTime > 18)
		{
			m_bDelayTime = false;
			m_iDelayTime = 0;
		}
		m_iDelayTime++;
	}

	CCreature::Update();
	return (int32)EObjectState::NODEAD;
}

void CBoss::LateUpdate()
{
	if (m_showEffect)
		m_pHitCrack->LateUpdate();

	CCreature::LateUpdate();
}

void CBoss::Render(HDC _hdc)
{
	if (m_showEffect)
		m_pHitCrack->Render(_hdc);

	CCreature::Render(_hdc);
}

void CBoss::Release()
{
	SAFE_DELETE(m_pHitCrack);
	__super::Release();
}

void CBoss::OnCollided(CObject* _pObject)
{
}

void CBoss::OnCollided(CObject* _pObject, EDirection _eDir)
{
}

void CBoss::MotionChange()
{
}