#include "pch.h"
#include "LineMgr.h"


CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

//�÷��̾� ���� ���� ���� Ž�� �Լ�(���� ����)
//���� �÷��̾��� fx,fy�� �޾Ƽ� ���� ����� ���� ������ x,y ��ǥ ��ȯ. 
bool CLineMgr::DetectHorizontal(float _fX, float _fY, float& _ValueY, float& _ValueX)
{
	if (m_LineList.empty())
		return false;

	float fResultY = 0.f;
	CLine* tempLine = nullptr;

	for (auto& iter : m_LineList) {
		if (iter->GetStartPosition().m_fX <= _fX && iter->GetEndPosition().m_fX > _fX &&
			iter->GetLineType() == ELineType::GROUND) {

			float fTempY = CalculatePositionY(iter, _fX);

			if ((fTempY >= _fY && fResultY > fTempY) || fResultY == 0.f) {
				tempLine = iter;
				fResultY = fTempY;
			}
		}
	}

	if (!tempLine)
		return false;

	_ValueY = fResultY;
	_ValueX = CalculatePositionX(tempLine, _ValueY);

	return true;
}

//����(���η� �������ִ� ����) ������ ���� �Լ�
bool CLineMgr::DetectVertical(float _fY, float _fX, float* _ValueX, float _fRadius, pair<float, float>& _ropeY)
{

	if (m_LineList.empty())
		return false;
	bool	bIsDetectSuc = false;

	float fTopY = 0.f;
	float fBottomY = 0.f;

	for (auto& iter : m_LineList) {

		if (iter->GetStartPosition().m_fY - 25.f > iter->GetEndPosition().m_fY - 25.f) {
			fTopY = iter->GetEndPosition().m_fY - 25.f;
			fBottomY = iter->GetStartPosition().m_fY - 25.f;
		}
		else {

			fTopY = iter->GetStartPosition().m_fY - 25.f;
			fBottomY = iter->GetEndPosition().m_fY - 25.f;
		}


		if ((_fY >= fTopY &&
			_fY <= fBottomY) &&
			(_fX + _fRadius >= iter->GetEndPosition().m_fX &&
				_fX - _fRadius <= iter->GetEndPosition().m_fX) &&
			iter->GetLineType() == ELineType::WALL) {

			*_ValueX = CalculatePositionX(iter, fBottomY);
			bIsDetectSuc = true;
			_ropeY = { fBottomY, fTopY };
			break;
		}
	}

	return bIsDetectSuc;
}

//������ �������� ���� X������ Y���� ����ϴ� �Լ�
float CLineMgr::CalculatePositionY(CLine* _pLine, float _fXpos)
{
	float fPositionY = 0.f;

	float fLeftX = _pLine->GetStartPosition().m_fX;
	float fLeftY = _pLine->GetStartPosition().m_fY - 25.f;
	float fRightX = _pLine->GetEndPosition().m_fX;
	float fRightY = _pLine->GetEndPosition().m_fY - 25.f;

	fPositionY = ((fLeftY - fRightY) / (fLeftX - fRightX)) * (_fXpos - fRightX) + fRightY;

	return fPositionY;

}

//������ �������� ���� Y������ X���� ����ϴ� �Լ�
float CLineMgr::CalculatePositionX(CLine* _pLine, float _fYpos)
{
	float fPositionX = 0.f;

	float fLeftX = _pLine->GetStartPosition().m_fX;
	float fLeftY = _pLine->GetStartPosition().m_fY - 25.f;
	float fRightX = _pLine->GetEndPosition().m_fX;
	float fRightY = _pLine->GetEndPosition().m_fY - 25.f;

	fPositionX = ((fLeftY - fRightY) * _fYpos / ((fLeftY - fRightY) / (fLeftX - fRightX))) + fRightX;

	return fPositionX;

}

//�÷��̾� ���� ���� ���� + x���� �޾� �˸��� y�� ��ȯ
bool CLineMgr::CollisionLine(float* pY, float* pX, float& m_fX, float fRadius)
{
	if (m_LineList.empty())
		return false;

	CLine* pTarget = nullptr;
	float fResultY = 0.f;

	for (auto& iter : m_LineList) {
		if (iter->GetStartPosition().m_fX + fRadius >= m_fX &&
			iter->GetStartPosition().m_fX - fRadius <= m_fX &&
			iter->GetStartPosition().m_fY - fRadius <= m_fX &&
			iter->GetStartPosition().m_fX - fRadius <= m_fX) {
			pTarget = iter;
			break;
		}
	}

	if (!pTarget)
		return false;

	if (pTarget->GetStartPosition().m_fX - pTarget->GetEndPosition().m_fX == 0 ||
		pTarget->GetStartPosition().m_fY - pTarget->GetEndPosition().m_fY == 0) {
		*pY = pTarget->GetStartPosition().m_fY;
	}
	else
	{
		*pY = CalculatePositionY(pTarget, m_fX);
	}

	return true;
}

bool CLineMgr::ZipCollision(CObject* _line, float& pY, float _fX)
{
	if (m_LineList.empty())
		return false;


	if ((dynamic_cast<CLine*>(_line))->GetEndPosition().m_fX <= _fX) {
		return false;
	}

	pY = CalculatePositionY(dynamic_cast<CLine*>(_line), _fX);

	return true;
}

void CLineMgr::LoadLine(const wstring& _wPath)
{
	// L"../Resources/Map/Stage1.dat"
	HANDLE hFile = CreateFile(_wPath.c_str(),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	DWORD dwByte = 0;

	tagLine tLine = {};
	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(tLine), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}

		ELineType eLineType = tLine.eLineType;
		Vector tStartPosition = tLine.tLPoint;
		Vector tEndPosition = tLine.tRPoint;;
		int32 iR = tLine.iR;
		int32 iG = tLine.iG;
		int32 iB = tLine.iB;

		CLine cLine(eLineType, tStartPosition, tEndPosition, iR, iG, iB);
		m_LineList.push_back(new CLine(cLine));
	}

	CloseHandle(hFile);
	Initialize();
}

void CLineMgr::Initialize(void)
{
	for (auto& iter : m_LineList)
		iter->Initialize();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), SAFE_DELETE<CLine*>);
	m_LineList.clear();
}