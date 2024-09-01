#pragma once
#include "Object.h"
class CHitBox : public CObject
{
public:
	CHitBox() = default;
	virtual ~CHitBox() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

	void	SetDelete(bool _isDelete) { 
		m_tPosition;
		m_tSize;
		m_isDeleted = _isDelete;
	}
	void	SetOwner(EObjectType _eType) { m_eOwner = _eType; }
	EObjectType	GetOwner() { return m_eOwner; }

private:
	bool		m_isDeleted = false;
	EObjectType m_eOwner = EObjectType::ENUM_END;
};

