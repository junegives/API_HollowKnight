#pragma once
#include "Scene.h"
class CArena : public CScene
{
public:
	CArena() = default;
	virtual ~CArena() = default;

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void StartBoss();
	void KillBoss();

private:
	CObject* m_pMarkoth;
	bool	m_bBossComplete;
	bool	m_bBossStart = false;
	bool	m_bBossAppear = false;
	bool	m_bBossEnd = false;
	
	int		m_iBossStartTime = 0;
	int		m_iBossTime = 0;
	int		m_iBossEndTime = 0;

	HWND		m_hVideo;
};