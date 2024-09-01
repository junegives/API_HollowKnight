#pragma once

#include "MyBitmap.h"

class CBmpMgr
{
public:
	CBmpMgr();
	~CBmpMgr();

public:
	static CBmpMgr*		GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmpMgr;
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
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release(void);

private:
	static CBmpMgr*	m_pInstance;
	map<const TCHAR*, CMyBitmap*>		m_mapBit;
};