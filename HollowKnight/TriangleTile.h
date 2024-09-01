#pragma once
#include "Tile.h"

class CTriangleTile : public CTile
{
public:
	CTriangleTile() = default;
	virtual ~CTriangleTile() = default;

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;
};

