#pragma once
#include "Scene.h"
class CDirtmouth : public CScene
{
public:
	CDirtmouth() = default;
	virtual ~CDirtmouth() = default;

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void EnterStore();

private:
	bool			m_canEnterStore = false;
	bool			m_isShowText = false;
	const wchar_t*	m_pTextKey;
	Vector			m_vTextSize;
	Vector			m_vTextPosition;
};

