#pragma once
#include "Object.h"
class CFrontBG : public CObject
{
public:
	CFrontBG() = default;
	virtual ~CFrontBG() = default;

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
	int		m_iWidth;
	int		m_iHeight;
};

