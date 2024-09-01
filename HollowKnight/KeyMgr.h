#pragma once

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);

	// 키매니저 초기화
	void		Setup();

	// 키가 한번 눌림
	bool		isOnceKeyDown(int key);
	// 키를 눌렀다 뗌
	bool		isOnceKeyUp(int key);
	// 키를 누르고 있음
	bool		isStayKeyDown(int key);
	// 키를 키고 끔
	bool		isToggleKey(int key);

public:
	static CKeyMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
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

private:
	static CKeyMgr* m_pInstance;

	bool			m_bKeyState[VK_MAX];

	bool			m_bKeyUpState[VK_MAX];
	bool			m_bKeyPressingState[VK_MAX];
	
	bitset<KEYMAX> m_bitKeyUp;
	bitset<KEYMAX> m_bitKeyDown;
};

