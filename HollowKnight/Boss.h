#pragma once
#include "Monster.h"
class CBoss : public CCreature
{
public:
	CBoss() = default;
	virtual ~CBoss() = default;

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

	EBossType GetBossType() { return m_eBossType; }

protected:
	// 몬스터의 타입
	EBossType		m_eBossType = EBossType::ENUM_END;

	EMonsterState	m_ePreState = EMonsterState::ENUM_END;
	EMonsterState	m_eCurState = EMonsterState::ENUM_END;

	bool			m_bPreLeft = false;

	bool			m_bDelayTime = false;
	int				m_iDelayTime = 0;
};