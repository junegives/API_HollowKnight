#pragma once
#include "Scene.h"
class CStore : public CScene
{
public:
	CStore() = default;
	virtual ~CStore() = default;

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;

public:
	void OpenStore();

private:
	bool			m_canOpenStore = false;

	bool			m_isShowText = false;
	const wchar_t*	m_pTextKey;
	Vector			m_vTextSize;
	Vector			m_vTextPosition;

	bool			m_isShowStore = false;

	CObject*		m_pStoreBoard;
};