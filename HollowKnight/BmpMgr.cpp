#include "pch.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{

}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&pImgKey](auto& obj) {
		return !lstrcmp(pImgKey, obj.first);
		});

	if (iter == m_mapBit.end())
	{
		CMyBitmap*		pBmp = new CMyBitmap;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}

}

HDC CBmpMgr::Find_Img(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&pImgKey](auto& obj) {
		return !lstrcmp(pImgKey, obj.first);
		});

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release(void)
{
	for (auto& iter : m_mapBit)
	{
		if (nullptr != iter.second)
		{
			SAFE_DELETE(iter.second);
			iter.second = nullptr;
		}
	}

	m_mapBit.clear();
}