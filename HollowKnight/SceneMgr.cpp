#include "pch.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Title.h"
#include "Obtain.h"
#include "MantisTown.h"
#include "Store.h"
#include "CrossRoad.h"
#include "Dirtmouth.h"
#include "Arena.h"
#include "SoundMgr.h"

CSceneMgr* CSceneMgr::_instance = nullptr;

CSceneMgr::CSceneMgr() : m_currentScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{

}

void CSceneMgr::ChangeCurrentScene(ESceneType _eSceneType)
{
	CSoundMgr::Get_Instance()->StopAll();

	if (nullptr != m_currentScene)
	{
		if (_eSceneType == m_currentScene->GetSceneType())
			return;
		m_ePrevSceneType = m_currentScene->GetSceneType();
		delete m_currentScene;
	}
	switch (_eSceneType)
	{
	case ESceneType::GAME_START:

		m_eCurSceneType = ESceneType::GAME_START;

		m_currentScene = new CTitle(); // new할 때 CScene을 상속 받아서 각각의 스테이지 만들 예정
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::GAME_START);
		break;

	case ESceneType::DIRTMOUTH:

		m_eCurSceneType = ESceneType::DIRTMOUTH;

		m_currentScene = new CDirtmouth(); // new할 때 CScene을 상속 받아서 각각의 스테이지 만들 예정
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::DIRTMOUTH);
		break;

	case ESceneType::CROSSROAD:
		m_eCurSceneType = ESceneType::CROSSROAD;

		m_currentScene = new CCrossRoad();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::CROSSROAD);
		break;

	case ESceneType::MANTISTOWN:

		m_eCurSceneType = ESceneType::MANTISTOWN;

		m_currentScene = new CMantisTown();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::MANTISTOWN);
		break;

	case ESceneType::OBTAIN:

		m_eCurSceneType = ESceneType::OBTAIN;

		m_currentScene = new CObtain();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::OBTAIN);
		break;

	case ESceneType::STORE:

		m_eCurSceneType = ESceneType::STORE;

		m_currentScene = new CStore();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::STORE);
		break;

	case ESceneType::ARENA:

		m_eCurSceneType = ESceneType::ARENA;

		m_currentScene = new CArena();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::ARENA);
		break;


	case ESceneType::ENUM_END:

		break;
	}
}

void CSceneMgr::RestartCurrentScene()
{
	m_ePrevSceneType = m_currentScene->GetSceneType();
	delete m_currentScene;

	switch (m_ePrevSceneType)
	{
	case ESceneType::GAME_START:

		m_eCurSceneType = ESceneType::GAME_START;

		m_currentScene = new CTitle(); // new할 때 CScene을 상속 받아서 각각의 스테이지 만들 예정
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::GAME_START);
		break;

	case ESceneType::DIRTMOUTH:

		m_eCurSceneType = ESceneType::DIRTMOUTH;

		m_currentScene = new CDirtmouth(); // new할 때 CScene을 상속 받아서 각각의 스테이지 만들 예정
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::DIRTMOUTH);
		break;

	case ESceneType::CROSSROAD:
		m_eCurSceneType = ESceneType::CROSSROAD;

		m_currentScene = new CCrossRoad();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::CROSSROAD);
		break;

	case ESceneType::MANTISTOWN:

		m_eCurSceneType = ESceneType::MANTISTOWN;

		m_currentScene = new CMantisTown();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::MANTISTOWN);
		break;

	case ESceneType::OBTAIN:

		m_eCurSceneType = ESceneType::OBTAIN;

		m_currentScene = new CObtain();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::OBTAIN);
		break;

	case ESceneType::STORE:

		m_eCurSceneType = ESceneType::STORE;

		m_currentScene = new CStore();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::STORE);
		break;

	case ESceneType::ARENA:

		m_eCurSceneType = ESceneType::ARENA;

		m_currentScene = new CArena();
		m_currentScene->Initialize();
		m_currentScene->SetSceneType(ESceneType::ARENA);
		break;


	case ESceneType::ENUM_END:

		break;
	}
}
