#pragma once

#include "Types.h"
#include "LineMgr.h"

class CObject;

class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void SetSceneType(ESceneType _sceneType) { m_eSceneType = _sceneType; }
	ESceneType GetSceneType() { return m_eSceneType; }
	virtual void StartBoss();
	virtual void KillBoss();

public:
	void AddObject(CObject* _obj);
	void DeleteObject(CObject* _obj);
	list<CObject*>* getObjectList();
	void	SetBlockProjectile() { m_isStopProjectile = true; }

private:
	list<CObject*>	m_objLists[static_cast<unsigned int>(EObjectType::ENUM_END)];
	list<CObject*>	m_RenderList[static_cast<unsigned int>(ERenderID::ENUM_END)];

	ESceneType		m_eSceneType;
	uint64			m_dwTime;
	static TCHAR*	m_pFrameKey;
	bool			m_bTileVisible = false;
	bool			m_bHitBoxVisible = false;
	bool			m_isStopProjectile = false;

protected:
	int			m_iWidth;
	int			m_iHeight;
	CObject*	pFrontImage;
	bool		m_bSceneChanged = false;
};