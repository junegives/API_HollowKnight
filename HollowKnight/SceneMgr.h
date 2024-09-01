#pragma once

class CScene;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr* GetInstance()
	{
		if (!_instance)
		{
			_instance = new CSceneMgr();
		}

		return _instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	CScene* GetCurrentScene() { return m_currentScene; }
	void ChangeCurrentScene(ESceneType _sceneType);
	void RestartCurrentScene();
	void DeleteScene() { SAFE_DELETE<CScene*>(m_currentScene); }
	
public:
	ESceneType GetPrevSceneType() const { return m_ePrevSceneType; }
	ESceneType GetCurSceneType() const { return m_eCurSceneType; }

private:
	static CSceneMgr* _instance;
	CScene* m_currentScene;

	ESceneType m_eCurSceneType = ESceneType::ENUM_END;
	ESceneType m_ePrevSceneType = ESceneType::ENUM_END;
};