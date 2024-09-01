#pragma once
#include "Object.h"
class CEffect : public CObject
{
public:
	CEffect() = default;
	virtual ~CEffect() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);
};
