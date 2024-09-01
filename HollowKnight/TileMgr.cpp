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

//플레이어 기준 하위 라인 탐색 함수(가로 라인)
//현재 플레이어의 fx,fy를 받아서 가장 가까운 하위 라인의 x,y 좌표 반환. 
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
	HANDLE		hFile = CreateFile(_pFrameKey, // 파일의 경로와 이름
		GENERIC_READ,		// 파일 접근 모드 GENERIC_WRITE(쓰기 전용), GENERIC_READ(읽기 전용)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인가에 대한 설정(NULL인 경우 공유하지 않음)
		NULL,				// 보안 속성, NULL인 경우 기본 보안 상태
		OPEN_EXISTING,		// 생성 방식, CREATE_ALWAYS(쓰기 전용 : 파일이 없다면 생성, 있으면 덮어 쓰기), OPEN_EXISTING(읽기 전용 : 파일이 있을 경우에만 열기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용 또는 숨김 파일 등), 아무런 속성이 없는 일반 파일로 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않기 때문에 NULL

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