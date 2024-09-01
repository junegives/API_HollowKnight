#include "pch.h"
#include "Geometry.h"

void CGeometry::DrawRectangle(HDC _hDC, Vector _tPosition, Vector _tSize)
{
	::Rectangle(_hDC,
		(int32)(_tPosition.m_fX - _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f),
		(int32)(_tPosition.m_fX + _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
}

void CGeometry::DrawEllipse(HDC _hDC, Vector _tPosition, float _fRadius)
{
	::Ellipse(_hDC,
		(int32)(_tPosition.m_fX - _fRadius),
		(int32)(_tPosition.m_fY - _fRadius),
		(int32)(_tPosition.m_fX + _fRadius),
		(int32)(_tPosition.m_fY + _fRadius));
}

void CGeometry::DrawTriangle(HDC _hDC, Vector _tPosition, Vector _tSize)
{
	::MoveToEx(_hDC, (int32)(_tPosition.m_fX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f), nullptr);
	::LineTo(_hDC, (int32)(_tPosition.m_fX - _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX + _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f));
}

void CGeometry::DrawLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition)
{
	::MoveToEx(_hDC, (int32)_tStartPosition.m_fX, (int32)_tStartPosition.m_fY, nullptr);
	::LineTo(_hDC, (int32)_tEndPosition.m_fX, (int32)_tEndPosition.m_fY);
}

void CGeometry::DrawColorLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition, int32 _iR, int32 _iG, int32 _iB, float fDeltaX) {
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::MoveToEx(_hDC, (int32)(_tStartPosition.m_fX + fDeltaX), (int32)_tStartPosition.m_fY, nullptr);
	::LineTo(_hDC, (int32)(_tEndPosition.m_fX + fDeltaX), (int32)_tEndPosition.m_fY);
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}


void CGeometry::DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::Rectangle(_hDC,
		(int32)(_tPosition.m_fX + fDeltaX - _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f),
		(int32)(_tPosition.m_fX + fDeltaX + _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}


void CGeometry::DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX, float fDeltaY)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::Rectangle(_hDC,
		(int32)(_tPosition.m_fX + fDeltaX - _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY + fDeltaY - _tSize.m_fY * 0.5f),
		(int32)(_tPosition.m_fX + fDeltaX + _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY + fDeltaY + _tSize.m_fY * 0.5f));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CGeometry::DrawColorEllipse(HDC _hDC, Vector _tPosition, float _fRadius, int32 _iR, int32 _iG, int32 _iB, float fDeltaX)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::Ellipse(_hDC,
		(int32)(_tPosition.m_fX + fDeltaX - _fRadius),
		(int32)(_tPosition.m_fY - _fRadius),
		(int32)(_tPosition.m_fX + fDeltaX + _fRadius),
		(int32)(_tPosition.m_fY + _fRadius));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CGeometry::DrawColorTriangle(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::MoveToEx(_hDC, (int32)(_tPosition.m_fX + fDeltaX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f), nullptr);
	::LineTo(_hDC, (int32)(_tPosition.m_fX + fDeltaX - _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX + fDeltaX + _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX + fDeltaX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CGeometry::DrawColorLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition, int32 _iR, int32 _iG, int32 _iB) {
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::MoveToEx(_hDC, (int32)(_tStartPosition.m_fX), (int32)_tStartPosition.m_fY, nullptr);
	::LineTo(_hDC, (int32)(_tEndPosition.m_fX), (int32)_tEndPosition.m_fY);
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}


void CGeometry::DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::Rectangle(_hDC,
		(int32)(_tPosition.m_fX - _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f),
		(int32)(_tPosition.m_fX + _tSize.m_fX * 0.5f),
		(int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CGeometry::DrawColorEllipse(HDC _hDC, Vector _tPosition, float _fRadius, int32 _iR, int32 _iG, int32 _iB)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::Ellipse(_hDC,
		(int32)(_tPosition.m_fX - _fRadius),
		(int32)(_tPosition.m_fY - _fRadius),
		(int32)(_tPosition.m_fX + _fRadius),
		(int32)(_tPosition.m_fY + _fRadius));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}

void CGeometry::DrawColorTriangle(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB)
{
	HPEN hNewPen, hPrevPen;
	hNewPen = CreatePen(PS_DOT, 2, RGB(_iR, _iG, _iB));
	hPrevPen = (HPEN)SelectObject(_hDC, hNewPen);
	::MoveToEx(_hDC, (int32)(_tPosition.m_fX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f), nullptr);
	::LineTo(_hDC, (int32)(_tPosition.m_fX - _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX + _tSize.m_fX * 0.5f), (int32)(_tPosition.m_fY + _tSize.m_fY * 0.5f));
	::LineTo(_hDC, (int32)(_tPosition.m_fX), (int32)(_tPosition.m_fY - _tSize.m_fY * 0.5f));
	::SelectObject(_hDC, hPrevPen);
	::DeleteObject(hNewPen);
}