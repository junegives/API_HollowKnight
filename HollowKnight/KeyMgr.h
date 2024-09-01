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

	// Ű�Ŵ��� �ʱ�ȭ
	void		Setup();

	// Ű�� �ѹ� ����
	bool		isOnceKeyDown(int key);
	// Ű�� ������ ��
	bool		isOnceKeyUp(int key);
	// Ű�� ������ ����
	bool		isStayKeyDown(int key);
	// Ű�� Ű�� ��
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

