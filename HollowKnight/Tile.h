#pragma once
#include "Object.h"

class CTile : public CObject
{
public:
	CTile() = default;
	CTile(TILE _tInfo) : m_tInfo(_tInfo) {}
	virtual ~CTile() = default;

public:
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;

public:
	ETileType	GetTileType() const { return m_tInfo.eTileType; }

protected:
	TILE m_tInfo;
};

