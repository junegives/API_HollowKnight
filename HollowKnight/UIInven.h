#pragma once
#include "UI.h"
class CUIInven : public CUI
{
public:
	CUIInven() = default;
	virtual ~CUIInven() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;
};