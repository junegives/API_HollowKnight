#pragma once
#include "Scene.h"
class CCrossRoad : public CScene
{
public:
	CCrossRoad() = default;
	virtual ~CCrossRoad() = default;

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void Climb();
	void Survey();
	void Enter();

private:
	bool			m_canClimb = false;
	bool			m_isShowText1 = false;
	const wchar_t* m_pTextKey1;
	Vector			m_vTextSize1;
	Vector			m_vTextPosition1;

	bool			m_canSurvey = false;
	bool			m_isShowText2 = false;
	const wchar_t* m_pTextKey2;
	Vector			m_vTextSize2;
	Vector			m_vTextPosition2;

	bool			m_canEnter = false;
	bool			m_isShowText3 = false;
	const wchar_t*	m_pTextKey3;
	Vector			m_vTextSize3;
	Vector			m_vTextPosition3;

	bool			m_isOpen = false;

	bool			m_isShowNeedKey = false;
	const wchar_t*	m_pTextKey4;
	Vector			m_vTextSize4;
	Vector			m_vTextPosition4;

	int				m_iShowTime = 0;
};