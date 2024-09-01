#include "pch.h"
#include "Monster.h"
#include "Tile.h"
#include "Effect.h"
#include "Player.h"
#include "SoundMgr.h"
using namespace std;

void CMonster::Initialize()
{
	CCreature::Initialize();
	m_eObjectType = EObjectType::MONSTER;
	m_eRender = ERenderID::GAMEOBJECT;
	// TODO: 오브젝트 타입, 몬스터 위치, 몬스터 크기, 몬스터 반지름, 몬스터 속도를 정의합니다.

	// 이펙트 관리
	{
		m_pHitCrack = new CEffect;
		m_pHitCrack->Initialize();
	}
}

int CMonster::Update()
{
	if (isOnGravity())
		m_tPosition = m_tPosition - m_tVel;

	if (m_isKnockBack)
	{
		if (m_iKnockBackTime < 10)
		{
			++m_iKnockBackTime;
			
			switch (m_eHitDir)
			{
			case EDirection::LEFT:
				m_tPosition.m_fX += (20 - m_iKnockBackTime);
				break;

			case EDirection::RIGHT:
				m_tPosition.m_fX -= (20 - m_iKnockBackTime);
				break;
			}
		}
		else
		{
			m_isKnockBack = false;
			m_iKnockBackTime = 0;
		}
	}

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

	else
	{
		m_tFrame.iMotion = 0;
	}

	if (m_iEffectTime < 10)
	{
		++m_iEffectTime;
	}
	else m_showEffect = false;

	return CCreature::Update();
}

void CMonster::LateUpdate()
{
	if (m_showEffect)
		m_pHitCrack->LateUpdate();

	__super::Move_Frame();
}

void CMonster::Render(HDC _hDC)
{
	if (m_showEffect)
		m_pHitCrack->Render(_hDC);

	CCreature::Render(_hDC);
}

void CMonster::Release()
{
	SAFE_DELETE(m_pHitCrack);
	CCreature::Release();
}

void CMonster::OnCollided(CObject* _pObject)
{
}

void CMonster::OnCollided(CObject* _pObject, EDirection _eDir)
{
}

void CMonster::MotionChange()
{
}

void CMonster::SetKnockBack(bool _isKnockBack, EDirection _eDir)
{
	m_isKnockBack = _isKnockBack;
	m_eHitDir = _eDir;
}

void CMonster::MonsterIdle()
{
	// 플레이어 감지
	Vector tPlayerPosition = CPlayer::GetInstance()->GetPosition();
	if (200.f >= tPlayerPosition.Distance(m_tPosition))
	{
		if (tPlayerPosition.m_fX < m_tPosition.m_fX)
			m_bLeft = true;
		else m_bLeft = false;

		m_eCurState = EMonsterState::MOVE;
	}
}

void CMonster::MonsterMove()
{
	if (m_bLeft)
		m_tPosition.m_fX -= m_fSpeed;
	else
		m_tPosition.m_fX += m_fSpeed;
}

void CMonster::MonsterFly()
{
}

void CMonster::MonsterDash()
{
}

void CMonster::MonsterJump()
{
}

void CMonster::MonsterShoot()
{
}

void CMonster::MonsterSlash()
{
}

void CMonster::MonsterDead()
{
}
