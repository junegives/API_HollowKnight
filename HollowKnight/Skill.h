#pragma once
#include "Object.h"
class CSkill : public CObject
{
public:
	CSkill() = default;
	virtual ~CSkill() = default;

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
	bool isFireBall() { return m_isFireBall; }

private:
	int				m_iShowTime = 0;
	EDirection		m_eDir;

protected:
	bool			m_isFireBall = false;
};
