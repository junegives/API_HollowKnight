#pragma once
#include "Object.h"
class CStoreBoard : public CObject
{
public:
	CStoreBoard() = default;
	virtual ~CStoreBoard();

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

private:
	CObject* m_pItemText;
	CObject* m_pItemImage;
	CObject* m_pArrowImage;
	CObject* m_pCheck;
	CObject* m_pSuccess;
	CObject* m_pFail;

	CObject* m_pItemArray[2];

	int		m_iItemNum = 0;
	int		m_iItemMax = 1;
	int		m_iMoveTime = 0;

};

