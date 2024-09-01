#include "pch.h"
#include "RectangleTile.h"
#include "Geometry.h"

void CRectangleTile::Initialize()
{
	CTile::Initialize();
	m_eTileType = ETileType::RECTANGLE;
}

void CRectangleTile::Update()
{

}

void CRectangleTile::LateUpdate()
{

}

void CRectangleTile::Render(HDC _hdc)
{
	CGeometry::DrawRectangle(_hdc, m_tPosition, m_tSize);
}

void CRectangleTile::Release()
{

}

void CRectangleTile::OnCollided(CObject* _pObject)
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
