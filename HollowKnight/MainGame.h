#pragma once

class CMainGame final {
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(HWND _hWnd);
	int Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HWND m_hWnd{};
	HDC m_hDC{};

	RECT m_rect{};
	HDC m_hDCBack = {};
	HBITMAP m_bmpBack = {};

	uint64		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];

	bool		m_bEnd = false;
	HWND		m_hVideo;
};