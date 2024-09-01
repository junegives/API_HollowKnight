#pragma once
#include "UI.h"
class CHP : public CUI
{
public:
	CHP() = default;
	virtual ~CHP() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	void gainHP();
	void loseHP();
	void setIndex(int _iIndex) { m_iIndex = _iIndex; }

private:
	uint32	m_iHP = MAXHP;
	int		m_iIndex;
	bool	m_isEmpty = false;
	bool	m_isMotionChange = false;
	bool	m_isChangeEnd = false;
};

