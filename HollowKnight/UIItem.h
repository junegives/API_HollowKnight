#pragma once
#include "UI.h"
class CUIItem : public CUI
{
public:
	CUIItem() = default;
	virtual ~CUIItem() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	void setIndex(int _iIndex) { m_iIndex = _iIndex; }

private:
	int		m_iIndex;
	bool	m_isEmpty = false;
};

