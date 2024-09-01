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

	// ������ ����
	// ������ false ��ȯ
	// ��������� true ��ȯ
	bool	setDamage(int _iDamage);

	void	setBlockKeyInput(bool _bBlock) { m_bBlockKeyInput = _bBlock; }

protected:
	// �ǰ�
	CObject*	m_pHitCrack;
	bool		m_showEffect = false;
	int			m_iEffectTime = 0;

	// �ǰ� �� ���� ����
	bool	m_isInvincible = false;
	bool	m_preInvincible = false;
	int		m_iInvincibleTime = 0;
	int		m_iMaxInvincibleTime = 0;

	// ü�� ����
	int		m_iHP;
	bool	m_isDead = false;
	bool	m_isHPFull = true;

	// ��� ����
	bool			m_bLeft = true;
	bool			m_bBlockChange = false;
	bool			m_bBlockMotionChange = false;
	bool			m_bBlockKeyInput = false;
};

