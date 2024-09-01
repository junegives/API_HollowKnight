#pragma once

#include "windows.h"

class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();
	
public:
	HDC		Get_MemDC() { return m_hMemDC; }

public:
	void	Load_Bmp(const TCHAR* pFilePath);
	void	Release();


private:
	HDC			m_hMemDC;		
	HBITMAP		m_hBitmap;

	HBITMAP		m_hOldBmp;
	};


// DDB(Device Dependent Bitmap) : ��ġ�� �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� ������ �̹��� �����ͷ� �����Ǿ� �־� �پ��� �ػ��� ��ġ���� �������ϰ� ������ ���Ѵ�.
// DIB(Device Independent Bitmap) : ��ġ�� �������� ��Ʈ�� ���� ����, DDB�� ���� ���� ���̺�, �ػ� ���� ���� �߰� ������ �����Ƿ� ��ġ�� ���ӵ��� �ʾ� Ȱ�뵵�� �� �������ϰ� ȣȯ���� �پ