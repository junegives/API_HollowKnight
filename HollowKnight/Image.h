#pragma once
#include "Object.h"
class CImage :
    public CObject
{
public:
	CImage() = default;
	virtual ~CImage() = default;

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
	bool MoveImage(EDirection _eDir, float _fAmount, int _iTime);

private:
	bool	m_isMoving = false;
	int		m_iCountTime = 0;
	int		m_iMovingTime = 0;
	float	m_fMoveAmount = 0;
	EDirection	m_eMoveDir = EDirection::ENUM_END;
};
