#include "pch.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Line.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "TileMgr.h"
#include "CameraMgr.h"

float		g_fVolume = 1.f;

CScene::CScene()
{

}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	m_objLists[(int32)EObjectType::PLAYER].push_back(CPlayer::GetInstance());
	CCameraMgr::GetInstance()->SetTarget(CPlayer::GetInstance());

	for (auto& list : m_objLists)
	{
		if (list.size() == 0)
			continue;

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			if ((*it)->GetObjectType() == EObjectType::PLAYER && CPlayer::GetInstance()->GetInitiailized())
				continue;
			(*it)->Initialize();
		}
	}

	m_dwTime = GetTickCount64();
}

int CScene::Update()
{
	if (CKeyMgr::GetInstance()->Key_Down('R'))
	{
		m_bTileVisible = !m_bTileVisible;
	}

	if (CKeyMgr::GetInstance()->Key_Down('H'))
		m_bHitBoxVisible = !m_bHitBoxVisible;

	for (auto& list : m_objLists)
	{
		if (list.size() == 0)
			continue;


		for (auto it = list.begin(); it != list.end(); )
		{
			if ((*it)->GetObjectType() == EObjectType::PROJECTILE)
			{
				if (m_isStopProjectile)
					(*it)->SetCanCollision(false);
			}

			if ((int32)EObjectState::DEAD == (*it)->Update())
			{
				CObject* pRemove = *it;
				it = list.erase(it);
				pRemove->Release();
				SAFE_DELETE<CObject*>(pRemove);
				continue;
			}
			++it;
		}
	}

	if (m_dwTime + 1000 < GetTickCount64())
	{
		auto it = m_objLists[(int)EObjectType::PLAYER].begin();
		std::cout << "X좌표 : ";
		std::cout << (*it)->GetPosition().m_fX << std::endl;
		std::cout << "Y좌표 : ";
		std::cout << (*it)->GetPosition().m_fY << std::endl;
		std::cout << "------------------------" << std::endl;

		m_dwTime = GetTickCount64();
	}

	return (int32)EObjectState::NODEAD;
}

void CScene::LateUpdate()
{
	for (size_t i = 0; i < (int)EObjectType::ENUM_END; ++i)
	{
		if (m_objLists[i].size() == 0)
			continue;

		for (auto& iter = m_objLists[i].begin(); iter != m_objLists[i].end(); )
		{
			(*iter)->LateUpdate();

			if ((*iter)->GetIsDead())
			{
				SAFE_DELETE<CObject*>(*iter);
				iter = m_objLists[i].erase(iter);
				continue;
			}

			else
			{
				if (i == (int)EObjectType::TILE)
					if (!m_bTileVisible)
					{
						++iter;
						continue;
					}

				if (i == (int)EObjectType::HITBOX)
					if (!m_bHitBoxVisible || !(*iter)->GetCanCollision())
					{
						++iter;
						continue;
					}

				// 오브젝트의 RenderID를 가져와서
				ERenderID		eID = (*iter)->GetRenderID();
				// m_RenderList의 해당 RenderID 인덱스에 오브젝트 저장
				m_RenderList[(int)eID].push_back(*iter);

				++iter;
			}


			if (m_objLists[i].empty())
				break;
		}
	}
}

void CScene::Render(HDC _hDC)
{
	for (size_t i = 0; i < (int)ERenderID::ENUM_END; ++i)
	{
		m_RenderList[i].sort([](CObject* pDst, CObject* pSrc) -> bool
		{
			return pDst->GetPosition().m_fY < pSrc->GetPosition().m_fY;
		});

		for (auto* iter : m_RenderList[i])
			iter->Render(_hDC);

		m_RenderList[i].clear();
	}
}

void CScene::Release()
{
	for (auto& list : m_objLists)
	{
		if (list.size() == 0)
			continue;

		if (!list.empty() && EObjectType::PLAYER == list.back()->GetObjectType())
		{
			//CPlayer::GetInstance()->DestroyInstance();
		}
		else
		{
			std::for_each(list.begin(), list.end(), [](auto& _objPtr) {

				if (_objPtr->GetObjectType() == EObjectType::HITBOX)
				{
					if (dynamic_cast<CHitBox*>(_objPtr)->GetOwner() != EObjectType::PLAYER)
					{
						_objPtr->Release();
						SAFE_DELETE<CObject*>(_objPtr);
					}
				}
				else
				{
					_objPtr->Release();
					SAFE_DELETE<CObject*>(_objPtr);
				}
			});
		}

		list.clear();
	}
}

void CScene::StartBoss()
{
}

void CScene::KillBoss()
{
}

void CScene::AddObject(CObject* _obj)
{
	switch (_obj->GetObjectType())
	{
	case EObjectType::MONSTER:
		m_objLists[static_cast<unsigned int>(EObjectType::MONSTER)].push_back(_obj);
		break;
	case EObjectType::PLAYER:
		m_objLists[static_cast<unsigned int>(EObjectType::PLAYER)].push_back(_obj);
		break;
	case EObjectType::PROJECTILE:
		m_objLists[static_cast<unsigned int>(EObjectType::PROJECTILE)].push_back(_obj);
		break;
	case EObjectType::ITEM:
		m_objLists[static_cast<unsigned int>(EObjectType::ITEM)].push_back(_obj);
		break;
	case EObjectType::LINE:
		m_objLists[static_cast<unsigned int>(EObjectType::LINE)].push_back(_obj);
		break;
	case EObjectType::TILE:
		m_objLists[static_cast<unsigned int>(EObjectType::TILE)].push_back(_obj);
		break;
	case EObjectType::HITBOX:
		m_objLists[static_cast<unsigned int>(EObjectType::HITBOX)].push_back(_obj);
		break;
	case EObjectType::SKILL:
		m_objLists[static_cast<unsigned int>(EObjectType::SKILL)].push_back(_obj);
		break;
	case EObjectType::WALL:
		m_objLists[static_cast<unsigned int>(EObjectType::WALL)].push_back(_obj);
		break;
	case EObjectType::FRONTBG:
		m_objLists[static_cast<unsigned int>(EObjectType::FRONTBG)].push_back(_obj);
		break;
	case EObjectType::IMAGE:
		m_objLists[static_cast<unsigned int>(EObjectType::IMAGE)].push_back(_obj);
		break;
	case EObjectType::GEO:
		m_objLists[static_cast<unsigned int>(EObjectType::GEO)].push_back(_obj);
		break;
	case EObjectType::STOREBOARD:
		m_objLists[static_cast<unsigned int>(EObjectType::STOREBOARD)].push_back(_obj);
		break;
	}
}

// DeleteObject가 과연 필요한가??
void CScene::DeleteObject(CObject* _obj)
{
	m_objLists[static_cast<unsigned int>(_obj->GetObjectType())].remove(_obj);
}

list<CObject*>* CScene::getObjectList()
{
	return m_objLists;
}
