#include "pch.h"
#include "MyBitmap.h"

CMyBitmap::CMyBitmap()
{
}

CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC			hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			//프로그램 인스턴스 핸들
									pFilePath,		// 파일의 경로를 전달
									IMAGE_BITMAP,	// 어떤 타입을 읽어올지 전달
									0,				// 가로, 세로 크기 전달(우리는 파일에서 읽어올 것이기 때문에 별도로 넘겨줄 필요 없음)
									0,
									LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 불러오는 옵션 | LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

	// SelectObject : 준비한 DC의 GDI 오브젝트를 불러온 비트맵을 선택하는 함수
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}