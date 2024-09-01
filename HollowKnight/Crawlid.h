#pragma once
#include "Monster.h"
class CCrawlid : public CMonster
{
public:
	CCrawlid() = default;
	virtual ~CCrawlid() = default;


public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void MotionChange()		override;
	virtual void OnCollided(CObject* _pObject) override;
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection) override;

};

