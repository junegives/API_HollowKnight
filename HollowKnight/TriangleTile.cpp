#include "pch.h"
#include "TriangleTile.h"
#include "Geometry.h"

void CTriangleTile::Initialize()
{
    CTile::Initialize();
    m_eTileType = ETileType::TRIANGLE;
}

void CTriangleTile::Update()
{

}

void CTriangleTile::LateUpdate()
{
}

void CTriangleTile::Render(HDC _hDC)
{
	CGeometry::DrawTriangle(_hDC, m_tPosition, m_tSize);
}

void CTriangleTile::Release()
{

}

void CTriangleTile::OnCollided(CObject* _pObject)
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
