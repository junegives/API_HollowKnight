#pragma once
#include "Tile.h"

class CEllipseTile : public CTile
{
public:
	CEllipseTile() = default;
	virtual ~CEllipseTile() = default;

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;

private:
	// TODO: 멤버 변수를 선언합니다.
};

