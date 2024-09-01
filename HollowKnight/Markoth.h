#pragma once
#include "Boss.h"
class CMarkoth : public CBoss
{
public:
	CMarkoth();
	virtual ~CMarkoth();

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
	void MarkIDLE();
	void MarkAPPEAR();
	void MarkSPAWN();
	void MarkMOVE();
	void MarkSHOOT();
	void MarkROTATE();
	void MarkDEAD();

	void SetAttackTerm(int _iAttackTerm) { m_iAttackTerm = _iAttackTerm; }

private:

	EMonsterState m_eCurState = EMonsterState::ENUM_END;

	Vector	m_tOriginPosition;
	Vector	m_tOriginSize;
	Vector	m_tMove;
	float	m_fRandValueX;
	float	m_fRandValueY;
	int		m_iRandSignX;
	int		m_iRandSignY;

	Vector	m_tSwordMove;

	CObject* m_pAppearEffect;
	bool	m_isShowAppearEffect;

	int		m_iAppearTime = 0;

	int		m_iSpawnTime = 0;

	int		m_iMoveTime = 0;

	int		m_iRotateTime = 0;

	int		m_iShootTime = 0;
	int		m_iAttackTerm = 230;
	int		m_iDeadTime = 0;

	bool	m_isSpawnSword1 = false;
	bool	m_isSpawnSword2 = false;
	bool	m_isSpawnSword3 = false;

	float	m_fSwordSpeed = 0.f;

	int		m_iPlayTime = 0;
	bool	m_bStartMove = false;

	Vector vDir[8];
};