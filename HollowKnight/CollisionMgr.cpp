#include "pch.h"
#include "CollisionMgr.h"
#include "Object.h"
#include "Monster.h"
#include "Line.h"
#include "Tile.h"
#include "Player.h"
#include "UIMgr.h"
#include "Projectile.h"

CCollisionMgr* CCollisionMgr::_instance = nullptr;

CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::CollisionRect(list<CObject*> _srcList, list<CObject*> _dstList)
{
	RECT		rc{};

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			RECT tSrcRect = GetRect(src);
			RECT tDstRect = GetRect(dst);

			if (IntersectRect(&rc, &tSrcRect, &tDstRect))
			{
				src->OnCollided(dst);
				dst->OnCollided(src);

			}
		}
	}
}

void CCollisionMgr::MonsterAndTile(list<CObject*> _srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : _srcList)
	{
		if (!src->GetCanCollision() || !src->GetHitBox()->GetCanCollision()) continue;

		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			if (dynamic_cast<CTile*>(dst)->GetTileType() == ETileType::TRIGGER) continue;

			dstRect = RECT{ (long)(dst->GetPosition().m_fX) - (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) - (long)(dst->GetSize().m_fY / 2),
							(long)(dst->GetPosition().m_fX) + (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) + (long)(dst->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				// 좌우 충돌
				if (height > width)
				{
					// 좌 (플레이어가 왼쪽)
					if (src->GetHitBox()->GetPosition().m_fX < dst->GetPosition().m_fX)
					{
						//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX - width, src->GetHitBox()->GetPosition().m_fY });
						src->OnCollided(dst, EDirection::LEFT);
					}
					else
					{
						//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX + width, src->GetHitBox()->GetPosition().m_fY });
						src->OnCollided(dst, EDirection::RIGHT);
					}
				}

				// 상하 충돌
				else if (width > height)
				{
					// 상 (플레이어가 위쪽)
					if (src->GetHitBox()->GetPosition().m_fY < dst->GetPosition().m_fY)
					{
						//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height });
						src->OnCollided(dst, EDirection::UP);
					}
					else
					{
						//src->GetHitBox()->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY + height });
						src->OnCollided(dst, EDirection::DOWN);
					}
				}
			}
		}
	}
}

void CCollisionMgr::PlayerAndMonster(list<CObject*> srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		if (!src->GetCanCollision() || !src->GetHitBox()->GetCanCollision()) continue;

		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			if (!dst->GetCanCollision() || !dst->GetHitBox()->GetCanCollision()) continue;

			dstRect = RECT{ (long)(dst->GetHitBox()->GetPosition().m_fX) - (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) - (long)(dst->GetHitBox()->GetSize().m_fY / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fX) + (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) + (long)(dst->GetHitBox()->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				src->OnCollided(dst);

				//// 좌우 충돌
				//if (height > width)
				//{
				//	// 좌 (플레이어가 왼쪽)
				//	if (src->GetHitBox()->GetPosition().m_fX < dst->GetHitBox()->GetPosition().m_fX)
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX - width, src->GetHitBox()->GetPosition().m_fY });
				//		src->OnCollided(dst, EDirection::LEFT);
				//	}
				//	else
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX + width, src->GetHitBox()->GetPosition().m_fY });
				//		src->OnCollided(dst, EDirection::RIGHT);
				//	}
				//}

				//// 상하 충돌
				//else if (width > height)
				//{
				//	// 상 (플레이어가 위쪽)
				//	if (src->GetHitBox()->GetPosition().m_fY < dst->GetHitBox()->GetPosition().m_fY)
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height });
				//		src->OnCollided(dst, EDirection::UP);
				//	}
				//	else
				//	{
				//		src->GetHitBox()->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY + height });
				//		src->OnCollided(dst, EDirection::DOWN);
				//	}
				//}
			}
		}
	}
}

void CCollisionMgr::PlayerAndProjectile(list<CObject*> srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		if (!src->GetCanCollision() || !src->GetHitBox()->GetCanCollision()) continue;

		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			if (!dst->GetCanCollision() || !dst->GetHitBox()->GetCanCollision()) continue;

			dstRect = RECT{ (long)(dst->GetHitBox()->GetPosition().m_fX) - (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) - (long)(dst->GetHitBox()->GetSize().m_fY / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fX) + (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) + (long)(dst->GetHitBox()->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				src->OnCollided(dst);

				//// 좌우 충돌
				//if (height > width)
				//{
				//	// 좌 (플레이어가 왼쪽)
				//	if (src->GetHitBox()->GetPosition().m_fX < dst->GetHitBox()->GetPosition().m_fX)
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX - width, src->GetHitBox()->GetPosition().m_fY });
				//		src->OnCollided(dst, EDirection::LEFT);
				//	}
				//	else
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX + width, src->GetHitBox()->GetPosition().m_fY });
				//		src->OnCollided(dst, EDirection::RIGHT);
				//	}
				//}

				//// 상하 충돌
				//else if (width > height)
				//{
				//	// 상 (플레이어가 위쪽)
				//	if (src->GetHitBox()->GetPosition().m_fY < dst->GetHitBox()->GetPosition().m_fY)
				//	{
				//		src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height });
				//		src->OnCollided(dst, EDirection::UP);
				//	}
				//	else
				//	{
				//		src->GetHitBox()->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY + height });
				//		src->OnCollided(dst, EDirection::DOWN);
				//	}
				//}
			}
		}
	}
}

void CCollisionMgr::PlayerAndGeo(list<CObject*> srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		if (!src->GetCanCollision() || !src->GetHitBox()->GetCanCollision()) continue;

		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			if (!dst->GetCanCollision() || !dst->GetHitBox()->GetCanCollision()) continue;

			dstRect = RECT{ (long)(dst->GetHitBox()->GetPosition().m_fX) - (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) - (long)(dst->GetHitBox()->GetSize().m_fY / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fX) + (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) + (long)(dst->GetHitBox()->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				src->OnCollided(dst);
				dst->OnCollided(src);
			}
		}
	}
}

void CCollisionMgr::SkillAndMonster(list<CObject*> srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			if (!dst->GetCanCollision() || !dst->GetHitBox()->GetCanCollision()) continue;

			dstRect = RECT{ (long)(dst->GetHitBox()->GetPosition().m_fX) - (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) - (long)(dst->GetHitBox()->GetSize().m_fY / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fX) + (long)(dst->GetHitBox()->GetSize().m_fX / 2),
							(long)(dst->GetHitBox()->GetPosition().m_fY) + (long)(dst->GetHitBox()->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;


				// 좌 (스킬이 왼쪽)
				if (src->GetHitBox()->GetPosition().m_fX < dst->GetHitBox()->GetPosition().m_fX)
				{
					src->OnCollided(dst);
					dst->OnCollided(src, EDirection::LEFT);
				}
				else
				{
					src->OnCollided(dst);
					dst->OnCollided(src, EDirection::RIGHT);
				}

				src->OnCollided(dst);
				dst->OnCollided(src);
			}
		}
	}
}

void CCollisionMgr::GeoAndTile(list<CObject*> srcList, list<CObject*> dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : dstList)
		{
			if (dynamic_cast<CTile*>(dst)->GetTileType() == ETileType::TRIGGER) continue;

			dstRect = RECT{ (long)(dst->GetPosition().m_fX) - (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) - (long)(dst->GetSize().m_fY / 2),
							(long)(dst->GetPosition().m_fX) + (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) + (long)(dst->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect)
				|| (srcRect.left < dstRect.right && srcRect.right > dstRect.left &&
					srcRect.bottom == dstRect.top))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				// 좌우 충돌
				if (height > width)
				{
					// 좌 (지오가 왼쪽)
					if (src->GetHitBox()->GetPosition().m_fX < dst->GetPosition().m_fX)
					{
						src->SetPosition({ src->GetHitBox()->GetPosition().m_fX - width, src->GetHitBox()->GetPosition().m_fY });
						//src->OnCollided(dst, EDirection::LEFT);
					}
					else
					{
						src->SetPosition({ src->GetHitBox()->GetPosition().m_fX + width, src->GetHitBox()->GetPosition().m_fY });
						//src->OnCollided(dst, EDirection::RIGHT);
					}
				}

				// 상하 충돌
				else if (width > height)
				{
					// 상 (플레이어가 위쪽)
					if (src->GetHitBox()->GetPosition().m_fY < dst->GetPosition().m_fY)
					{
						//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height + (abs(src->GetPosition().m_fY - src->GetHitBox()->GetPosition().m_fY) / 2) });
						src->OnCollided(dst, EDirection::UP);
					}
					else
					{
						src->GetHitBox()->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY + height });
						//src->OnCollided(dst, EDirection::DOWN);
					}
				}

				else if (srcRect.bottom == dstRect.top)
				{
					//std::cout << "맞닿았는데 처리안됨!" << std::endl;
					//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height + (abs(src->GetPosition().m_fY - src->GetHitBox()->GetPosition().m_fY) / 2) });
					src->OnCollided(dst, EDirection::UP);
				}
			}
		}
	}
}

void CCollisionMgr::SkillAndTile(list<CObject*> srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	for (auto& src : srcList)
	{
		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{
			dstRect = RECT{ (long)(dst->GetPosition().m_fX) - (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) - (long)(dst->GetSize().m_fY / 2),
							(long)(dst->GetPosition().m_fX) + (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) + (long)(dst->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect))
			{
				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				src->OnCollided(dst);
			}
		}
	}
}

bool CCollisionMgr::PlayerAndTile(list<CObject*> _srcList, list<CObject*> _dstList)
{
	RECT temp;
	RECT srcRect;
	RECT dstRect;

	bool isTrigger = false;

	for (auto& src : _srcList)
	{
		srcRect = RECT{ (long)(src->GetHitBox()->GetPosition().m_fX) - (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) - (long)(src->GetHitBox()->GetSize().m_fY / 2),
						(long)(src->GetHitBox()->GetPosition().m_fX) + (long)(src->GetHitBox()->GetSize().m_fX / 2),
						(long)(src->GetHitBox()->GetPosition().m_fY) + (long)(src->GetHitBox()->GetSize().m_fY / 2) };

		for (auto& dst : _dstList)
		{

			dstRect = RECT{ (long)(dst->GetPosition().m_fX) - (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) - (long)(dst->GetSize().m_fY / 2),
							(long)(dst->GetPosition().m_fX) + (long)(dst->GetSize().m_fX / 2),
							(long)(dst->GetPosition().m_fY) + (long)(dst->GetSize().m_fY / 2) };

			if (IntersectRect(&temp, &srcRect, &dstRect)
				|| (srcRect.left < dstRect.right && srcRect.right > dstRect.left &&
				srcRect.bottom == dstRect.top)
				|| (srcRect.top < dstRect.bottom && srcRect.bottom > dstRect.top &&
				srcRect.left == dstRect.right)
				|| (srcRect.top < dstRect.bottom && srcRect.bottom > dstRect.top &&
				srcRect.right == dstRect.left)
				)
			{
				if (ETileType::TRIGGER == dynamic_cast<CTile*>(dst)->GetTileType())
				{
					src->OnCollided(dst, EDirection::UP);
					isTrigger = true;
					continue;
				}

				float width = temp.right - temp.left;
				float height = temp.bottom - temp.top;

				// 좌우 충돌
				if (height > width)
				{
					// 좌 (플레이어가 왼쪽)
					if (src->GetHitBox()->GetPosition().m_fX < dst->GetPosition().m_fX)
					{
						src->SetPosition({ src->GetHitBox()->GetPosition().m_fX - width, src->GetHitBox()->GetPosition().m_fY });
						src->OnCollided(dst, EDirection::LEFT);
					}
					else
					{
						src->SetPosition({ src->GetHitBox()->GetPosition().m_fX + width, src->GetHitBox()->GetPosition().m_fY });
						src->OnCollided(dst, EDirection::RIGHT);
					}
				}

				// 상하 충돌
				else if (width > height)
				{
					// 상 (플레이어가 위쪽)
					if (src->GetHitBox()->GetPosition().m_fY < dst->GetPosition().m_fY)
					{
						src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height + (abs(src->GetPosition().m_fY - src->GetHitBox()->GetPosition().m_fY) / 2)});
						src->OnCollided(dst, EDirection::UP);
					}
					else
					{
						src->GetHitBox()->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY + height });
						src->OnCollided(dst, EDirection::DOWN);
					}
				}

				else if ((srcRect.left < dstRect.right && srcRect.right > dstRect.left) && srcRect.bottom == dstRect.top)
				{
					//std::cout << "맞닿았는데 처리안됨!" << std::endl;
					//src->SetPosition({ src->GetHitBox()->GetPosition().m_fX, src->GetHitBox()->GetPosition().m_fY - height + (abs(src->GetPosition().m_fY - src->GetHitBox()->GetPosition().m_fY) / 2) });
					src->OnCollided(dst, EDirection::UP);
				}

				else if ((srcRect.top < dstRect.bottom && srcRect.bottom > dstRect.top) &&
					srcRect.left == dstRect.right)
				{
					src->OnCollided(dst, EDirection::RIGHT);
				}

				else if ((srcRect.top < dstRect.bottom && srcRect.bottom > dstRect.top) &&
					srcRect.right == dstRect.left)
				{
					src->OnCollided(dst, EDirection::LEFT);
				}

			}
		}
	}

	return isTrigger;
}

void CCollisionMgr::CollisionTile(list<CObject*> _srcList, list<CObject*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY))
			{
				switch (dynamic_cast<CTile*>(dst)->GetTileType())
				{
				case ETileType::GROUND:
					// 땅을 밟은 경우
					// 상하 충돌 먼저
					// 좌우 충돌이면 그냥 미끄러지게


					// 상하 충돌
					if (m_fY <= 0)
					{
						if (src->GetPosition().m_fY < dst->GetPosition().m_fY)
						{
							src->OnCollided(dst, EDirection::UP);
						}
						else // 하 충돌
						{
							src->OnCollided(dst, EDirection::DOWN);
						}
					}
					else if (m_fX <= 0)
					{
						if (src->GetPosition().m_fX < dst->GetPosition().m_fX)
						{
							src->OnCollided(dst, EDirection::RIGHT);
						}
						else if (src->GetPosition().m_fX > dst->GetPosition().m_fX) // 우 충돌
						{
							src->OnCollided(dst, EDirection::LEFT);
						}
					}
					break;

				case ETileType::WALL:
					// 벽에 닿은 경우
					// 좌우 충돌 먼저 (항상 벽렉트 위에 그라운드 렉트 얹어주기)
					// 그다음 상하 충돌

				// 좌우 충돌
					if (m_fX <= 0)
					{
						if (src->GetPosition().m_fX < dst->GetPosition().m_fX)
						{
							src->OnCollided(dst, EDirection::RIGHT);
						}
						else if (src->GetPosition().m_fX > dst->GetPosition().m_fX) // 우 충돌
						{
							src->OnCollided(dst, EDirection::LEFT);
						}
					}

					//// 상하 충돌
					//else if (m_fY <= 0)
					//{
					//	if (src->GetPosition().m_fY < dst->GetPosition().m_fY)
					//	{
					//		src->OnCollided(dst, EDirection::UP);
					//	}
					//	else // 하 충돌
					//	{
					//		src->OnCollided(dst, EDirection::DOWN);
					//	}
					//}
					//break;

				case ETileType::OBSTACLE:
					// 장애물에 닿은 경우
					// 상하 충돌 먼저
					// 그다음 좌우충돌
					break;

				default:
					break;
				}

			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObject* _pSrc, CObject* _pDst, float* pX, float* pY)
{
	float		fWidth = abs(_pDst->GetPosition().m_fX - _pSrc->GetPosition().m_fX);
	float		fHeight = abs(_pDst->GetPosition().m_fY - _pSrc->GetPosition().m_fY);

	float		fCX = (_pDst->GetSize().m_fX + _pSrc->GetSize().m_fX) * 0.5f;
	float		fCY = (_pDst->GetSize().m_fY + _pSrc->GetSize().m_fY) * 0.5f;

	// 충돌하는 경우
	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		*pX = fWidth - fCX;
		*pY = fHeight - fCY;

		return true;
	}

	return false;

	/*if (_pSrc->GetRect().left <= _pDst.GetRect().right &&
		_pDst->GetRect().left <= _pSrc->GetRect().right &&
		_pSrc->GetRect().bottom <= _pDst->GetRect().top &&
		_pDst->GetRect().bottom <= _pSrc->GetRect().top)
	{
		return true;
	}

	return false;*/
}

void CCollisionMgr::CollisionMonster(list<CObject*> _srcList, list<CObject*> _dstList)
{
	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			/*switch (dynamic_cast<CMonster*>(dst)->GetMonsterType())
			{*/
				// Ellipse
			//case EMonsterType::STATIC_GEAR:
			//	if (CheckSphere(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);

			//	}
			//	break;

			//	// Triangle
			//	// 네모랑 네모 ㅜㅜ
			//case EMonsterType::FLOWER:
			//	if (CheckTriangleMonster(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);

			//	}
			//	break;

			//	// Line
			//case EMonsterType::SPINNING_FIRE:
			//	if (CheckLineMonster(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);

			//	}
			//	break;

			//	// Ellipse
			//case EMonsterType::DYNAMIC_GEAR:
			//	if (CheckSphere(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);

			//	}
			//	break;

			//	// Rectangle
			//	// 일단 네모랑 네모 충돌로 만듦...
			//case EMonsterType::STONE:
			//	if (CheckRectMonster(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);
			//	}
			//	break;

			//	// Triangle
			//	// 네모랑 네모 ㅜㅜ
			//case EMonsterType::MUSHROOM:
			//	if (CheckTriangleMonster(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);

			//	}
			//	break;

			//case EMonsterType::BOSS:
			//	if (CheckSphere(src, dst))
			//	{
			//		src->OnCollided(dst);
			//		dst->OnCollided(src);
			//	}
			//	break;

			//default:
			//	break;
			//}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObject* _pSrc, CObject* _pDst)
{
	float		fWidth = fabs(_pDst->GetPosition().m_fX - _pSrc->GetPosition().m_fX);
	float		fHeight = fabs(_pDst->GetPosition().m_fY - _pSrc->GetPosition().m_fY);

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (_pDst->GetSize().m_fX + _pSrc->GetSize().m_fX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::CollisionSphere(list<CObject*> _srcList, list<CObject*> _dstList)
{
	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckSphere(src, dst))
			{
				src->OnCollided(dst);
				dst->OnCollided(src);

			}
		}
	}
}

bool CCollisionMgr::CheckLine(CObject* _pSrc, CLine* _pDst)
{
	switch (_pSrc->GetObjectType())
	{
		// 플레이어와 라인 충돌
	case EObjectType::PLAYER:
	{
		Vector Pc = { _pSrc->GetPosition().m_fX, _pSrc->GetPosition().m_fY };
		Vector P1 = { dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fX , dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fY };
		Vector P2 = { dynamic_cast<CLine*>(_pDst)->GetEndPosition().m_fX , dynamic_cast<CLine*>(_pDst)->GetEndPosition().m_fY };
		Vector P4 = P2 - P1;

		float u = (Pc - P1).Dot(P4) / (P2 - P1).Dot(P4);

		Vector P = P1 + (P2 - P1) * u;

		return ((_pSrc->GetSize().m_fX / 2 >= (P - Pc).Length()) && (P1.m_fX <= GetRect(_pSrc).right) && (P2.m_fX >= GetRect(_pSrc).left) && P1.m_fY >= GetRect(_pSrc).top && P2.m_fY <= GetRect(_pSrc).bottom);
	}
	// 몬스터와 라인 충돌
	case EObjectType::MONSTER:
	{
		// 충돌
		if (ELineType::WALL == dynamic_cast<CLine*>(_pDst)->GetLineType())
		{
			if ((_pSrc->GetPosition().m_fX + _pSrc->GetSize().m_fX * 0.5f >= dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fX) &&
				(_pSrc->GetPosition().m_fX - _pSrc->GetSize().m_fX * 0.5f <= dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fX))
			{
				return true;
			}
		}

		break;
	}

	// 총알과 라인 충돌
	case EObjectType::PROJECTILE:
	{
		Vector Pc = { _pSrc->GetPosition().m_fX, _pSrc->GetPosition().m_fY };
		Vector P1 = { dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fX,dynamic_cast<CLine*>(_pDst)->GetStartPosition().m_fY };
		Vector P2 = { dynamic_cast<CLine*>(_pDst)->GetEndPosition().m_fX, dynamic_cast<CLine*>(_pDst)->GetEndPosition().m_fY };
		Vector P3 = P2 - P1;

		float u = (Pc - P1).Dot(P3) / (P2 - P1).Dot(P3);

		Vector P = P1 + (P2 - P1) * u;

		return ((_pSrc->GetSize().m_fX / 2 >= (P - Pc).Length()) && (P1.m_fX <= GetRect(_pSrc).right) && (P2.m_fX >= GetRect(_pSrc).left) && P1.m_fY >= GetRect(_pSrc).top && P2.m_fY <= GetRect(_pSrc).bottom);

	}
	}

	return false;
}

void CCollisionMgr::CollisionLine(list<CObject*> _srcList, list<CLine*> _dstList)
{

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckLine(src, dst))
			{
				src->OnCollided(dst);
				dst->OnCollided(src);

			}
		}
	}
}

RECT CCollisionMgr::GetRect(CObject* _pObj)
{
	RECT rc;

	rc.left = LONG(_pObj->GetPosition().m_fX - (_pObj->GetSize().m_fX * 0.5f));
	rc.top = LONG(_pObj->GetPosition().m_fY - (_pObj->GetSize().m_fY * 0.5f));
	rc.right = LONG(_pObj->GetPosition().m_fX + (_pObj->GetSize().m_fX * 0.5f));
	rc.bottom = LONG(_pObj->GetPosition().m_fY + (_pObj->GetSize().m_fY * 0.5f));

	return rc;
}

bool CCollisionMgr::CheckLineMonster(CObject* _pSrc, CObject* _pDst)
{
	//Vector Pc = { _pSrc->GetPosition().m_fX, _pSrc->GetPosition().m_fY };
	//Vector P1 = { _pDst->GetPosition().m_fX , _pDst->GetPosition().m_fY };
	//Vector P2 = { dynamic_cast<CSpinningFire*>(_pDst)->GetEndPoint()->m_fX , dynamic_cast<CSpinningFire*>(_pDst)->GetEndPoint()->m_fY };
	//Vector P4 = P2 - P1;

	//float u = (Pc - P1).Dot(P4) / (P2 - P1).Dot(P4);

	//Vector P = P1 + (P2 - P1) * u;

	//if ((_pSrc->GetSize().m_fX / 2 >= (P - Pc).Length()) && (P1.m_fX <= GetRect(_pSrc).right) && (P2.m_fX >= GetRect(_pSrc).left) && P1.m_fY >= GetRect(_pSrc).top && P2.m_fY <= GetRect(_pSrc).bottom)
	//{
	//	float f1 = _pSrc->GetPosition().m_fX;
	//	float f2 = _pSrc->GetPosition().m_fY;
	//	float f3 = dynamic_cast<CSpinningFire*>(_pDst)->GetEndPoint()->m_fX;
	//	float f4 = dynamic_cast<CSpinningFire*>(_pDst)->GetEndPoint()->m_fY;

	//	return true;
	//}

	return false;
	//return ((_pSrc->GetSize().m_fX / 2 >= (P - Pc).Length()) && (P1.m_fX <= GetRect(_pSrc).right) && (P2.m_fX >= GetRect(_pSrc).left) && P1.m_fY >= GetRect(_pSrc).top && P2.m_fY <= GetRect(_pSrc).bottom);
}

bool CCollisionMgr::CheckRectMonster(CObject* _pSrc, CObject* _pDst)
{
	float		fWidth = abs(_pDst->GetPosition().m_fX - _pSrc->GetPosition().m_fX);
	float		fHeight = abs(_pDst->GetPosition().m_fY - _pSrc->GetPosition().m_fY);

	float		fCX = (_pDst->GetSize().m_fX + _pSrc->GetSize().m_fX) * 0.5f;
	float		fCY = (_pDst->GetSize().m_fY + _pSrc->GetSize().m_fY) * 0.5f;

	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		return true;
	}

	return false;
}

bool CCollisionMgr::CheckTriangleMonster(CObject* _pSrc, CObject* _pDst)
{
	float		fWidth = abs(_pDst->GetPosition().m_fX - _pSrc->GetPosition().m_fX);
	float		fHeight = abs(_pDst->GetPosition().m_fY - _pSrc->GetPosition().m_fY);

	float		fCX = (_pDst->GetSize().m_fX + _pSrc->GetSize().m_fX) * 0.5f;
	float		fCY = (_pDst->GetSize().m_fY + _pSrc->GetSize().m_fY) * 0.5f;

	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		return true;
	}

	return false;
}