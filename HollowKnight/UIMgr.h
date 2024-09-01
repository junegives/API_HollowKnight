#pragma once

#include "UI.h"

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr();
		}

		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Initialize();
	int		Update();
	void	LateUpdate();
	void	Render(HDC _hDC);
	void	Release();

	list<CUI*> GetList() { return m_UIList; }

	// ü�� ȹ��
	void	gainHP();
	// ü�� ����
	void	loseHP();
	// ��ȥ ȹ��
	void	gainSoul();
	// ��ȥ ���
	void	useSoul();
	// ��ȥ �Ҹ�
	void	setEmptySoul();
	// ü�� ����
	void	setMaxHP();
	// ���� ����
	void	setGeo(uint32 _iGeo);
	// ���� ȹ��
	void	gainGeo(uint32 _iGeo);
	// ���� ���
	void	useGeo(uint32 _iGeo);
	// ������ ȹ��
	void	getItem(TCHAR* _pImageKey, int _iItemIndex);
	// ������ �Ҹ�
	void	useItem(int _iItemCode);



private:
	static CUIMgr* m_pInstance;

	int		m_iHP;
	int		m_iSoul;
	int		m_iGeo;

	list<CUI*>	m_UIList;
	CUI* pSoul;
	CUI* pHP[MAXHP];
	CUI* pGeo;
	CUI* pInventory;
	CUI* pItem[3];
};