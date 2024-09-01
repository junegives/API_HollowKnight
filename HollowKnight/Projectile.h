#pragma once
#include "Object.h"

class CProjectile : public CObject
{
public:
	CProjectile() = default;
	virtual ~CProjectile() = default;

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

public:
	virtual void OnCollided(CObject* _pObject) override;

public:
	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }
	float GetDamage() const { return m_fDamage; }

	void SetProjectileType(EProjectileType _eProjectileType) { m_eProjectileType = _eProjectileType; }
	EProjectileType GetProjectileType() const { return m_eProjectileType; }

	void SetProjectileOwnerType(EProjectileOwnerType _eProjectileOwnerType) { m_eProjectileOwnerType = _eProjectileOwnerType; }
	EProjectileOwnerType GetProjectileOwnerType() const { return m_eProjectileOwnerType; }

	void SetDirection(EDirection _eDir) { m_eDir = _eDir; }

private:
	// 발사체의 종류
	EProjectileType m_eProjectileType = EProjectileType::ENUM_END;

	// 발사체의 주인
	EProjectileOwnerType m_eProjectileOwnerType = EProjectileOwnerType::ENUM_END;

	// 발사체의 공격력
	float m_fDamage = 0.0f;

public:
	void SetOwnerDead(bool _isDead) { m_isOwnerDead = _isDead; }
	bool GetOwnerDead() { return m_isOwnerDead; }

protected:
	// 주인 죽었는지 (죽었으면 딜 안들어감)
	bool	m_isOwnerDead = false;
};