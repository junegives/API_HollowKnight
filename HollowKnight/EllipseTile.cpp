#include "pch.h"
#include "EllipseTile.h"
#include "Geometry.h"

void CEllipseTile::Initialize()
{
	CTile::Initialize();
	m_eTileType = ETileType::ELLIPSE;
}

void CEllipseTile::Update()
{

}

void CEllipseTile::LateUpdate()
{

}

void CEllipseTile::Render(HDC _hDC)
{
	CGeometry::DrawEllipse(_hDC, m_tPosition, m_fRadius);
}

void CEllipseTile::Release()
{

}

void CEllipseTile::OnCollided(CObject* _pObject)
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
