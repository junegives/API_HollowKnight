#pragma once
#include "Object.h"
class CWall : public CObject
{
public:
	CWall() = default;
	virtual ~CWall() = default;

public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void MotionChange();
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

public:
	void Down();
	void Up();

private:
	bool m_isUP = false;
	bool m_isDOWN = false;
	bool m_isVisible = false;
	bool m_isBlockChange = false;
};
