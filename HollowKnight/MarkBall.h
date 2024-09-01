#pragma once
#include "Projectile.h"
class CMarkBall : public CProjectile
{
public:
	CMarkBall();
	virtual ~CMarkBall();

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

	void SetDirectioin(Vector _vDir) { m_vDir = _vDir; }

private:
	// �߻�ü�� ����
	EProjectileType m_eProjectileType = EProjectileType::ENUM_END;

	// �߻�ü�� ����
	EProjectileOwnerType m_eProjectileOwnerType = EProjectileOwnerType::ENUM_END;

	// �߻�ü�� ���ݷ�
	float m_fDamage = 0.0f;		
	int				m_iTime = 0;
	Vector			m_vDir;
};