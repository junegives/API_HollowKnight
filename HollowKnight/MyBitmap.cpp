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

	m_hBitmap = (HBITMAP)LoadImage(NULL,			//���α׷� �ν��Ͻ� �ڵ�
									pFilePath,		// ������ ��θ� ����
									IMAGE_BITMAP,	// � Ÿ���� �о���� ����
									0,				// ����, ���� ũ�� ����(�츮�� ���Ͽ��� �о�� ���̱� ������ ������ �Ѱ��� �ʿ� ����)
									0,
									LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����� �ɼ� | LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ

	// SelectObject : �غ��� DC�� GDI ������Ʈ�� �ҷ��� ��Ʈ���� �����ϴ� �Լ�
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}