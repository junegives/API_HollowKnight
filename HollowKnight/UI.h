#pragma once
#include "Object.h"
class CUI : public CObject
{
public:
	CUI() = default;
	virtual ~CUI() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

};

