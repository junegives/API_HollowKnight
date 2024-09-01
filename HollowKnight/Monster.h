#pragma once
#include "Creature.h"

class CMonster : public CCreature
{
public:
	CMonster() = default;
	virtual ~CMonster() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;
	virtual void OnCollided(CObject* _pObject, EDirection _eDir) override;
	virtual void MotionChange()		override;

	EMonsterType GetMonsterType() { return m_eMonsterType; }
	void		 SetKnockBack(bool _isKnockBack, EDirection _eDir);

public:
	void MonsterIdle();
	void MonsterMove();
	void MonsterFly();
	void MonsterDash();
	void MonsterJump();
	void MonsterShoot();
	void MonsterSlash();
	void MonsterDead();

protected:
	// 몬스터의 타입
	EMonsterType	m_eMonsterType = EMonsterType::ENUM_END;
	bool			m_isKnockBack = false;
	int				m_iKnockBackTime = 0;
	EDirection		m_eHitDir = EDirection::ENUM_END;

	EMonsterState	m_ePreState = EMonsterState::ENUM_END;
	EMonsterState	m_eCurState = EMonsterState::ENUM_END;

	bool			m_bPreLeft = false;

	bool			m_bDelayTime = false;
	int				m_iDelayTime = 0;

	bool			m_bDamage = false;
	int				m_iDamageTime = 0;
};