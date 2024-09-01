#include "pch.h"
#include "LineTile.h"
#include "Geometry.h"

void CLineTile::Initialize()
{
	CTile::Initialize();
	m_eTileType = ETileType::LINE;
}

void CLineTile::Update()
{

}

void CLineTile::LateUpdate()
{

}

void CLineTile::Render(HDC _hDC)
{
	CGeometry::DrawLine(_hDC, m_tStartPosition, m_tEndPosition);
}

void CLineTile::Release()
{

}

void CLineTile::OnCollided(CObject* _pObject)
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
