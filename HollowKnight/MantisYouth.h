#pragma once
#include "Monster.h"
class CMantisYouth : public CMonster
{
public:
	CMantisYouth() = default;
	virtual ~CMantisYouth() = default;


public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void MotionChange()		override;
	virtual void OnCollided(CObject* _pObject) override;
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection) override;

public:
	void MonsterIdle();
	void MonsterStart();
	void MonsterFly();
	void MonsterTurn();
	void MonsterAttack();
	void MonsterDead();

private:
	int	m_iFlyTime = 0;
	int	m_iAttackTime = 0;
	int	m_iFollowTime = 0;
};

