#pragma once

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static CScrollMgr* GetInstance()
	{
		if (nullptr == _instance)
		{
			_instance = new CScrollMgr();
		}

		return _instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

public:
	void SetScrollX(float _fSpeed)
	{
		m_fScrollX -= _fSpeed;
	}
	void SetScrollY(float _fSpeed)
	{
		m_fScrollY += _fSpeed;
	}

	void Reset()
	{
		m_fScrollX = 0.f;
		m_fScrollY = 0.f;
	}

	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }

	void CalcPositionX(float _fPlrX);
	void CalcPositionY(float _fPlrY);

	void Scroll_Lock(LONG Width, LONG Height)
	{
		if (0.f < m_fScrollX)
		{
			m_fScrollX = 0.f;
			m_bLock = true;
		}

		else if (0.f < m_fScrollY)
		{
			m_fScrollY = 0.f;
			m_bLock = true;
		}

		else if (WINCX - Width > m_fScrollX)
		{
			m_fScrollX = WINCX - Width;
			m_bLock = true;
		}

		else if (WINCY - Height > m_fScrollY)
		{
			m_fScrollY = WINCY - Height;
			m_bLock = true;
		}

		else m_bLock = false;
	}


private:
	static CScrollMgr* _instance;

	float	m_fScrollX;
	float	m_fScrollY;
	float	m_fPrevX;
	float	m_fPrevY;

	bool	m_bLock = false;
};