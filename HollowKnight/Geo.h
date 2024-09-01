#pragma once
#include "Object.h"
class CGeo : public CObject
{
public:
	CGeo() = default;
	CGeo(int iSize);
	virtual ~CGeo() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

	int			GetAmount() { return m_iAmount; }
	void		SetAmount(int _iAmount) { m_iAmount = _iAmount; }
	void		SetDelete(bool _isDelete) { m_isDeleted = _isDelete; }

private:
	int			m_iAmount = 0;
	bool		m_isDeleted = false;

	// ÇÇ°Ý
	CObject*	m_pGetEffect;
	bool		m_showEffect = false;
	int			m_iEffectTime = 0;
};

