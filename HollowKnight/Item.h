#pragma once
#include "Object.h"
class CItem : public CObject
{
public:
	CItem() = default;
	virtual ~CItem() = default;

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
	void SetInfo(int _iItemNum, int _iItemGeo) { m_iItemNum = _iItemNum; m_iItemGeo = _iItemGeo; }
	int  GetItemCode() { return m_iItemNum; }
	bool isSelled() { return m_isSelled; }
	int  GetGeo() { return m_iItemGeo; }

private:
	int		m_iItemNum;
	int		m_iItemGeo;
	bool	m_isSelled = false;
};

