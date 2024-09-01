#pragma once
#include "UI.h"
class CUIGeo : public CUI
{
public:
	CUIGeo() = default;
	virtual ~CUIGeo() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	void setGeo(uint32 _iGeo) { m_iGeo = _iGeo; }

private:
	uint32	m_iGeo = 0;
};

