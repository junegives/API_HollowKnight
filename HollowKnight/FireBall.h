#pragma once
#include "Skill.h"
class CFireBall : public CSkill
{
public:
	CFireBall() = default;
	virtual ~CFireBall() = default;

public:
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

public:
	void SetDirection(EDirection _eDir) { m_eDir = _eDir; m_iShowTime = 0; }

private:
	int				m_iShowTime = 0;
	EDirection		m_eDir;
	bool			m_bLeft;

	// 벽 충돌 이펙트
	CObject*	m_pGetEffect;
	bool		m_showEffect = false;
	int			m_iEffectTime = 0;
};
