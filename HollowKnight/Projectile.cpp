#include "pch.h"
#include "Projectile.h"
#include "HitBox.h"
using namespace std;

void CProjectile::Initialize()
{
	m_eObjectType = EObjectType::PROJECTILE;
}

int CProjectile::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CProjectile::LateUpdate()
{
}

void CProjectile::Render(HDC _hdc)
{

}

void CProjectile::Release()
{
	dynamic_cast<CHitBox*>(m_cHitBox)->SetDelete(true);
}

void CProjectile::OnCollided(CObject* _pObject)
{
	switch (_pObject->GetObjectType())
	{
	case EObjectType::PLAYER:
		break;

	case EObjectType::MONSTER:
		break;

	case EObjectType::PROJECTILE:
		break;
	}
}
