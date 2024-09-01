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
	// �߻�ü�� ����
	EProjectileType m_eProjectileType = EProjectileType::ENUM_END;

	// �߻�ü�� ����
	EProjectileOwnerType m_eProjectileOwnerType = EProjectileOwnerType::ENUM_END;

	// �߻�ü�� ���ݷ�
	float m_fDamage = 0.0f;

public:
	void SetOwnerDead(bool _isDead) { m_isOwnerDead = _isDead; }
	bool GetOwnerDead() { return m_isOwnerDead; }

protected:
	// ���� �׾����� (�׾����� �� �ȵ�)
	bool	m_isOwnerDead = false;
};