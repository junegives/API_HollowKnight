#pragma once
#include "Object.h"

class CLine : public CObject
{
public:
	CLine() = default;
	CLine(ELineType _eLineType, Vector _tS, Vector _tE, int32 _iR, int32 _iG, int32 _iB)
		: m_eLineType(_eLineType), m_tStartPosition(_tS), m_tEndPosition(_tE),
		m_iR(_iR), m_iG(_iG), m_iB(_iB) {}
	virtual ~CLine() = default;

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	virtual void OnCollided(CObject* _pObject) override;

public:
	ELineType	GetLineType() const { return m_eLineType; }
	void		SetLineType(ELineType _eLineType) { m_eLineType = _eLineType; }
	
	Vector		GetStartPosition() { return m_tStartPosition; }
	void		SetStartPosition(Vector _tStartPosition) { m_tStartPosition = _tStartPosition; }
	
	Vector		GetEndPosition() { return m_tEndPosition; }
	void		SetEndPosition(Vector _tEndPosition) { m_tEndPosition = _tEndPosition; }


protected:
	ELineType m_eLineType = ELineType::ENUM_END;

	// 선분의 시작점
	Vector m_tStartPosition{ 0.0f, 0.0f };

	// 선분의 끝점
	Vector m_tEndPosition{ 0.0f, 0.0f };

	// 선분의 색상
	int32 m_iR = 0;
	int32 m_iG = 0;
	int32 m_iB = 0;
};

