#pragma once
#include "Object.h"

class CCameraMgr
{
private:
	CCameraMgr();
	~CCameraMgr();


public:
	static CCameraMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCameraMgr;
		}

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Update();
	void Render(HDC _hDC);

public:
	void	SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; }
	void	SlowMoveToTarget(Vector _vTarget, float _fTime);
	void	UnLock() { m_bTempTarget = false; }
	void	SetLookPos(Vector _pos) { m_vLookPos = _pos; }
	void	SetResoultion(Vector _resolution) { m_vResolution = _resolution; }
	void	CalcDiff();
	Vector	GetRenderPos(Vector _vObjPos);
	Vector	GetLookPos();
	void	CameraShaking(int _iTime);

	void	FadeOut();
	void	FadeIn();

	void SetMinX(float f) { m_fMinX = f; }
	void SetMinY(float f) { m_fMinY = f; }
	void SetMaxX(float f) { m_fMaxX = f; }
	void SetMaxY(float f) { m_fMaxY = f; }


private:
	static CCameraMgr* m_pInstance;
	
	CObject*	m_pTarget;		// 카메라 중심 타겟
	Vector		m_vLookPos;		// 카메라 중심 위치
	Vector		m_vResolution = { 1920.f, 1080.f };	// 해상도
	Vector		m_vDiff;		// 카메라 중심과 해상도 중심의 차이

	float		m_fMinX = 0.f;
	float		m_fMaxX = 0.f;
	float		m_fMinY = 0.f;
	float		m_fMaxY = 0.f;

	bool		m_isMoving = false;
	bool		m_bTempTarget = false;

	Vector		m_vTarget;
	Vector		m_vToMove;
	float		m_fTime;

	bool		m_bShaking = false;
	int			m_iTime = 0;
	int			m_iShakingTime = 0;
	float		m_fShakingAmount = 0.f;
	int			m_iShakingDir = 1;

	bool		m_isFadeOut = false;
	int			m_iFadeOutTime = 0;
	int			m_iAlpahValue = 0;
	bool		m_isUnlocked = false;
};
