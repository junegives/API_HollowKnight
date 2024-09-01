#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	static CTileMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileMgr;
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
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

public:
	list<CTile*> GetList() { return m_TileList; }
	void LoadTile(const wchar_t* _pFrameKey);
	
	bool DetectHorizontal(float _fX, float _fY, float& _ValueY, float& _ValueX);

private:
	//list<CTile*>			m_TileList;
	list<CTile*>			m_TileList;
	ETileType				m_eTileType = ETileType::ENUM_END;
	bool					m_bTileVisible = false;

	static CTileMgr* m_pInstance;
};


