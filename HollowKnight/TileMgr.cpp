#include "pch.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"


CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	//Release();
}

void CTileMgr::Initialize(void)
{
	//for (auto& iter : m_TileList)
	//	iter->Initialize();
}

int CTileMgr::Update()
{
	return (int32)EObjectState::NODEAD;
}

void CTileMgr::LateUpdate()
{

}

void CTileMgr::Render(HDC hDC)
{

}

void CTileMgr::Release()
{
	//for_each(m_TileList.begin(), m_TileList.end(), SAFE_DELETE<CTile*>);
	//m_TileList.clear();
}

//�÷��̾� ���� ���� ���� Ž�� �Լ�(���� ����)
//���� �÷��̾��� fx,fy�� �޾Ƽ� ���� ����� ���� ������ x,y ��ǥ ��ȯ. 
bool CTileMgr::DetectHorizontal(float _fX, float _fY, float& _ValueY, float& _ValueX)
{
	if (m_TileList.empty())
		return false;

	float fResultY = 0.f;
	CTile* tempTile = nullptr;

	for (auto& iter : m_TileList) {
		if (iter->GetPosition().m_fX - iter->GetSize().m_fX / 2 <= _fX && iter->GetPosition().m_fX + iter->GetSize().m_fX / 2 > _fX &&
			iter->GetTileType() == ETileType::GROUND) {

			float fTempY = iter->GetPosition().m_fY - iter->GetSize().m_fY / 2;

			tempTile = iter;
			fResultY = fTempY;

		}
	}

	if (!tempTile)
		return false;

	_ValueY = fResultY;
	_ValueX = _fX;

	return true;
}

void CTileMgr::LoadTile(const wchar_t* _pFrameKey)
{
	HANDLE		hFile = CreateFile(_pFrameKey, // ������ ��ο� �̸�
		GENERIC_READ,		// ���� ���� ��� GENERIC_WRITE(���� ����), GENERIC_READ(�б� ����)
		NULL,				// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ���ΰ��� ���� ����(NULL�� ��� �������� ����)
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,		// ���� ���, CREATE_ALWAYS(���� ���� : ������ ���ٸ� ����, ������ ���� ����), OPEN_EXISTING(�б� ���� : ������ ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ���� �Ǵ� ���� ���� ��), �ƹ��� �Ӽ��� ���� �Ϲ� ���Ϸ� ����
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʱ� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	TILE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObject* pTile = new CTile(tInfo);
		pTile->Initialize();

		CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(pTile);

		m_TileList.push_back(new CTile(tInfo));
	}

	CloseHandle(hFile);
}