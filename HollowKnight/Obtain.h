#pragma once
#include "Scene.h"
class CObtain : public CScene
{
public:
	CObtain() = default;
	virtual ~CObtain() = default;

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void Survey();

private:
	bool			m_canSurvey = false;

	bool			m_isShowText = false;
	const wchar_t* m_pTextKey1;
	Vector			m_vTextSize1;
	Vector			m_vTextPosition1;

	bool			m_isShowLight = true;
	const wchar_t*	m_pTextKey2;
	Vector			m_vTextSize2;
	Vector			m_vTextPosition2;

	bool			m_isShowGet = false;
	const wchar_t*	m_pTextKey3;
	Vector			m_vTextSize3;
	Vector			m_vTextPosition3;

	int				m_iShowTime = 0;
};
