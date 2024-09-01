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

	// Ã¼·Â È¹µæ
	void	gainHP();
	// Ã¼·Â ÇÇÇØ
	void	loseHP();
	// ¿µÈ¥ È¹µæ
	void	gainSoul();
	// ¿µÈ¥ »ç¿ë
	void	useSoul();
	// ¿µÈ¥ ¼Ò¸ê
	void	setEmptySoul();
	// Ã¼·Â ¼³Á¤
	void	setMaxHP();
	// Áö¿À º¯°æ
	void	setGeo(uint32 _iGeo);
	// Áö¿À È¹µæ
	void	gainGeo(uint32 _iGeo);
	// Áö¿À »ç¿ë
	void	useGeo(uint32 _iGeo);
	// ¾ÆÀÌÅÛ È¹µæ
	void	getItem(TCHAR* _pImageKey, int _iItemIndex);
	// ¾ÆÀÌÅÛ ¼Ò¸ð
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