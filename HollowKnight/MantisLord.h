#pragma once
#include "Boss.h"
class CMantisLord : public CBoss
{
public:
	CMantisLord();
	virtual ~CMantisLord();

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

public:
	void LordIdle();
	void LordStand();
	void LordLeave();
	void LordDashBEFORE();
	void LordDash();
	void LordDashAFTER();
	void LordWallTOP();
	void LordWallBOTTOM();
	void LordThrowTOP();
	void LordThrowBOTTOM();
	void LordThrowAFTER();
	void LordSmashBEFORE();
	void LordSmash();
	void LordSmashAFTER();
	void LordDead();
	void LordSit();
	void LordBow();
	void LordNotVisible();

	void SetAttackTerm(int _iAttackTerm) { m_iAttackTerm = _iAttackTerm; }
	void SetWaitingTime(int _iWaitingTime) { m_iWaitingTime = _iWaitingTime; }

	void SetSoloOrGroup(bool _isSolo, bool _isLeft) { m_isSolo = _isSolo; if (!m_isSolo) m_isLeft = _isLeft; }

	bool IsLordDead() { return m_isDead; }

private:
	Vector	m_tOriginPosition;
	Vector	m_tOriginSize;

	int		m_iLeaveTime = 0;
	int		m_iDashBeforeTime = 0;
	int		m_iDashTime = 0;

	int		m_iSmashBeforeTime = 0;
	int		m_iSmashTime = 0;

	CObject* m_pBoomerang;
	int		m_iShootBeforeTime = 0;
	int		m_iShootTime = 0;

	int		m_iAttackTerm = 80;
	int		m_iWaitingTime = 0;

	int		m_iDeadTime = 0;

	int		m_iSitTime = 0;

	int		m_iBowTime = 0;

	bool	m_isSolo = true;
	bool	m_isLeft = false;
	bool	m_isDead = false;

	int		m_iGroupAttack = 1;

	EMonsterState m_eSoloAttack = EMonsterState::ENUM_END;
	EMonsterState m_eGroupAttack = EMonsterState::DASH_BEFORE;
};