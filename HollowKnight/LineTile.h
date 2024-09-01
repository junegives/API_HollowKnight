#pragma once
#include "Tile.h"

class CLineTile : public CTile
{
public:
	CLineTile() = default;
	virtual ~CLineTile() = default;

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;

public:
	Vector GetStartPosition() const { return m_tStartPosition; }
	void SetStartPosition(Vector _tStartPosition) { m_tStartPosition = _tStartPosition; }
	
	Vector GetEndPosition() const { return m_tEndPosition; }
	void SetEndPosition(Vector _tEndPosition) { m_tEndPosition = _tEndPosition; }

private:
	// 선분의 시작점
	Vector m_tStartPosition{ 0.0f, 0.0f };
	
	// 선분의 끝점
	Vector m_tEndPosition{ 0.0f, 0.0f };
};

