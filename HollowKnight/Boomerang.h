#pragma once
#include "Projectile.h"
class CBoomerang : public CProjectile
{
public:
	CBoomerang();
	virtual ~CBoomerang();

public:
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);

public:

	void SetProjectileType(EProjectileType _eProjectileType) { m_eProjectileType = _eProjectileType; }
	EProjectileType GetProjectileType() const { return m_eProjectileType; }

	void SetProjectileOwnerType(EProjectileOwnerType _eProjectileOwnerType) { m_eProjectileOwnerType = _eProjectileOwnerType; }
	EProjectileOwnerType GetProjectileOwnerType() const { return m_eProjectileOwnerType; }

	bool CalcPath();

private:
	// 발사체의 종류
	EProjectileType m_eProjectileType = EProjectileType::ENUM_END;

	// 발사체의 주인
	EProjectileOwnerType m_eProjectileOwnerType = EProjectileOwnerType::ENUM_END;

	// 발사체의 공격력
	float m_fDamage = 0.0f;

	int				m_iTime = 0;
	Vector			m_vDir;
};