#pragma once

class CGeometry final
{
public:
	static void DrawRectangle(HDC _hDC, Vector _tPosition, Vector _tSize);

	static void DrawEllipse(HDC _hDC, Vector _tPosition, float _fRadius);

	static void DrawTriangle(HDC _hDC, Vector _tPosition, Vector _tSize);

	static void DrawLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition);

	static void DrawColorLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition, int32 _iR, int32 _iG, int32 _iB, float fDeltaX);
	
	static void DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX);
	static void DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX, float fDeltaY);
	
	static void DrawColorEllipse(HDC _hDC, Vector _tPosition, float _fRadius, int32 _iR, int32 _iG, int32 _iB, float fDeltaX);
	
	static void DrawColorTriangle(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB, float fDeltaX);

	static void DrawColorLine(HDC _hDC, Vector _tStartPosition, Vector _tEndPosition, int32 _iR, int32 _iG, int32 _iB);
	static void DrawColorRect(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB);
	static void DrawColorEllipse(HDC _hDC, Vector _tPosition, float _fRadius, int32 _iR, int32 _iG, int32 _iB);
	static void DrawColorTriangle(HDC _hDC, Vector _tPosition, Vector _tSize, int32 _iR, int32 _iG, int32 _iB);

};

