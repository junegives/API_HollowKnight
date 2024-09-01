#pragma once
#include "Object.h"

class CCreature : public CObject
{
public:
	CCreature() = default;
	virtual ~CCreature() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void MotionChange()		= 0;
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

	// 데미지 입음
	// 죽으면 false 반환
	// 살아있으면 true 반환
	bool	setDamage(int _iDamage);

	void	setBlockKeyInput(bool _bBlock) { m_bBlockKeyInput = _bBlock; }

protected:
	// 피격
	CObject*	m_pHitCrack;
	bool		m_showEffect = false;
	int			m_iEffectTime = 0;

	// 피격 후 무적 상태
	bool	m_isInvincible = false;
	bool	m_preInvincible = false;
	int		m_iInvincibleTime = 0;
	int		m_iMaxInvincibleTime = 0;

	// 체력 관리
	int		m_iHP;
	bool	m_isDead = false;
	bool	m_isHPFull = true;

	// 모션 관리
	bool			m_bLeft = true;
	bool			m_bBlockChange = false;
	bool			m_bBlockMotionChange = false;
	bool			m_bBlockKeyInput = false;
};

