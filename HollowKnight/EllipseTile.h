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
	// TODO: ��� ������ �����մϴ�.
};

