#pragma once
#include "UI.h"
class CSoul : public CUI
{
public:
	CSoul() = default;
	virtual ~CSoul() = default;

public:
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	void gainSoul();
	void useSoul();
	void setEmptySoul();

private:
	int		m_iSoul;
	int		m_iPreSoul;
	bool	m_isMotionChange = false;
	bool	m_isChangeEnd = false;
	bool	m_isIncreasing = false;

	bool	m_isStopFrame = true;
};