#pragma once
#include "Scene.h"
class CMantisTown : public CScene
{
public:
	CMantisTown() = default;
	virtual ~CMantisTown() = default;

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	virtual void StartBoss() override;
	virtual void KillBoss() override;

public:
	void	FirstBossDead();
	int		GetBossKillCount() { return m_iBossKillCnt; }
	bool	GetBossComplete() { return m_bossComplete; }

private:
	CObject*	pMantisLord1;
	CObject*	pMantisLord2;
	CObject*	pMantisLord3;

	CObject*	pWallLeft;
	CObject*	pWallRight;
	CObject*	pWallLeftTile;
	CObject*	pWallRightTile;
	CObject*	pObstacleLeft;
	CObject*	pObstacleRight;

	bool	m_isStand = false;
	bool	m_isWallDown = false;
	bool	m_isShaking = false;
	bool	m_isObstacleOpen = false;
	bool	m_isBossLeave = false;

	bool	m_isStartFirst = false;
	bool	m_isStartSecond = false;

	int		m_iBossKillCnt = 0;

	bool	m_bossComplete = false;

	bool	m_isBow = false;
	bool	m_isWallUp = false;
	bool	m_isObstacleClose = false;
	bool	m_isCameraReset = false;

	uint64	m_iBossStartTime = 0;
	uint64	m_iBossFightTime = 0;
	uint64	m_iBossEndTime = 0;
};
