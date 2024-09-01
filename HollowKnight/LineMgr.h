#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	static CLineMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	void	Initialize();
	void	Render(HDC hDC);
	void	Release();

public:

	list<CLine*> GetList() { return m_LineList; }

	bool	DetectHorizontal(float _fX, float _fY, float& _ValueY, float& _ValueX);
	bool	DetectVertical(float _fY, float _fX, float* _ValueX, float _fRadius, pair<float, float>& _ropeY);

	float	CalculatePositionY(CLine* _pLine, float _fXpos);
	float	CalculatePositionX(CLine* _pLine, float _fXpos);
	bool	CollisionLine(float* pY, float* pX, float& m_fX, float fRadius);
	bool	ZipCollision(CObject* _line, float& pY, float _fX);


	void	LoadLine(const wstring& _wPath);

private:
	list<CLine*>			m_LineList;
	static CLineMgr*		m_pInstance;
};


