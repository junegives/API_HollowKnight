#include "pch.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "CameraMgr.h"

CMainGame::CMainGame()
{
	m_dwTime = GetTickCount64();
	m_iFPS = 0;
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	_CrtDumpMemoryLeaks();
}

void CMainGame::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hDC = ::GetDC(_hWnd);

	::GetClientRect(_hWnd, &m_rect);
	m_hDCBack = ::CreateCompatibleDC(m_hDC);
	m_bmpBack = ::CreateCompatibleBitmap(m_hDC, m_rect.right, m_rect.bottom);
	HBITMAP prevBmp = (HBITMAP)::SelectObject(m_hDCBack, m_bmpBack);
	::DeleteObject(prevBmp);

	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::GetInstance()->ChangeCurrentScene(ESceneType::GAME_START);

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Title.bmp", L"Title");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/TestScene.bmp", L"TestScene");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Dirtmouth.bmp", L"Dirtmouth");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Dirtmouth_FRONT.bmp", L"Dirtmouth_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/CrossRoad.bmp", L"CrossRoad");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/CrossRoad_FRONT.bmp", L"CrossRoad_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/MantisTown.bmp", L"MantisTown");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/MantisTown_FRONT.bmp", L"MantisTown_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Obtain.bmp", L"Obtain");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Obtain_FRONT.bmp", L"Obtain_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Store.bmp", L"Store");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Store_FRONT.bmp", L"Store_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Arena.bmp", L"Arena");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Arena_FRONT.bmp", L"Arena_FRONT");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene1_back.bmp", L"Scene2_BACK");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene1_front.bmp", L"Scene2_FRONT");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene2_back.bmp", L"Stage2_BACK");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene2_front.bmp", L"Stage2_FRONT");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene3_back.bmp", L"Scene3_BACK");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/Scene3_front.bmp", L"Scene3_FRONT");

	// 이펙트 이미지 추가
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/HitCrack.bmp", L"HitCrack");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/HitEffect.bmp", L"HitEffect");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/StunEffect.bmp", L"StunEffect");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/DeathEffect.bmp", L"DeathEffect");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/FireBallEffect_L.bmp", L"FireBallEffect_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/FireBallEffect_R.bmp", L"FireBallEffect_R");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Effect/FocusEffect.bmp", L"FocusEffect");

	// 스킬 이미지 추가 (플레이어)
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectDownSlash.bmp", L"EffectDownSlash");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectSlash_L.bmp", L"EffectSlash_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectSlash_R.bmp", L"EffectSlash_R");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectUpSlash.bmp", L"EffectUpSlash");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireEnd_L.bmp", L"FireEnd_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireShoot_L.bmp", L"FireShoot_L");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireStart_L.bmp", L"FireStart_L");

	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireEnd_R.bmp", L"FireEnd_R");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireShoot_R.bmp", L"FireShoot_R");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireStart_R.bmp", L"FireStart_R");

	// 스킬 이미지 추가 (몬스터 & 보스)
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/MantisLordsWhite/LordBoomerang.bmp", L"LordBoomerang");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkBALL.bmp", L"MarkBALL");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Boss/Markoth/MarkBALL_Y.bmp", L"MarkBALL_Y");

	// 지오 이미지
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoSmallIdle.bmp", L"GeoSmallIdle");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoSmallAir.bmp", L"GeoSmallAir");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoMediumIdle.bmp", L"GeoMediumIdle");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoMediumAir.bmp", L"GeoMediumAir");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoBigIdle.bmp", L"GeoBigIdle");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoBigAir.bmp", L"GeoBigAir");
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Object/GeoGet.bmp", L"GeoGet");

	CUIMgr::GetInstance()->Initialize();
	CCameraMgr::GetInstance()->Initialize();

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

	//m_hVideo = MCIWndCreate(g_hWnd,		// 부모 창의 핸들
	//	nullptr,	// 윈도우를 사용하는 인스턴스 핸들(null인 경우 초기화 창의 기본 인스턴스 정보)
	//	WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // 모양 옵션(WS_CHILD : 종속적인 자녀 창의 형태, WS_VISIBLE : 즉시 화면에 갱신하여 출력 MCIWNDF_NOPLAYBAR : 플레이를 바를 생성하지 않음)
	//	L"../Resource/Video/Wildlife.wmv");	// 재생할 파일의 경로

	//// 동영상을 재생할 크기를 설정
	//MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

}

int CMainGame::Update()
{
	if (CSceneMgr::GetInstance()->GetCurrentScene()->Update() == 3)
	{
		m_bEnd = true;
		return 0;
	}
	CUIMgr::GetInstance()->Update();
	CCameraMgr::GetInstance()->Update();


	if (CKeyMgr::GetInstance()->Key_Down(VK_F1))
		CUIMgr::GetInstance()->gainHP();

	if (CKeyMgr::GetInstance()->Key_Down(VK_F2))
	{
		CUIMgr::GetInstance()->loseHP();
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_F3))
		CUIMgr::GetInstance()->gainSoul();

	if (CKeyMgr::GetInstance()->Key_Down(VK_F4))
		CUIMgr::GetInstance()->useSoul();

	return (int32)EObjectState::NODEAD;
}

void CMainGame::LateUpdate()
{
	if (m_bEnd) return;

	list<CObject*>* pObjectList = CSceneMgr::GetInstance()->GetCurrentScene()->getObjectList();
	list<CObject*> pPlayerList = pObjectList[(int32)EObjectType::PLAYER];
	list<CObject*> pMonsterList = pObjectList[(int32)EObjectType::MONSTER];
	list<CObject*> pProjectileList = pObjectList[(int32)EObjectType::PROJECTILE];
	list<CObject*> pTileList = pObjectList[(int32)EObjectType::TILE];
	list<CObject*> pSkillList = pObjectList[(int32)EObjectType::SKILL];
	list<CObject*> pGeoList = pObjectList[(int32)EObjectType::GEO];

	// 몬스터 충돌
	if (pMonsterList.size() != 0)
	{
		CCollisionMgr::GetInstance()->SkillAndMonster(pSkillList, pMonsterList);
		CCollisionMgr::GetInstance()->PlayerAndMonster(pPlayerList, pMonsterList);
		CCollisionMgr::GetInstance()->MonsterAndTile(pMonsterList, pTileList);
	}

	// 플레이어 충돌
	CCollisionMgr::GetInstance()->PlayerAndProjectile(pPlayerList, pProjectileList);
	CCollisionMgr::GetInstance()->PlayerAndGeo(pPlayerList, pGeoList);
	if (CCollisionMgr::GetInstance()->PlayerAndTile(pPlayerList, pTileList))
	{
		if (CPlayer::GetInstance()->GetChangeScene())
			return;
	}

	// 나머지 충돌
	CCollisionMgr::GetInstance()->GeoAndTile(pGeoList, pTileList);
	CCollisionMgr::GetInstance()->SkillAndTile(pSkillList, pTileList);

	CSceneMgr::GetInstance()->GetCurrentScene()->LateUpdate();
	CUIMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	if (m_bEnd)
	{
		return;
	}

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = GetTickCount64();

		// SetWindowText : 윈도우 타이틀에 출력하는 함수
		SetWindowText(g_hWnd, m_szFPS);
	}

	// TODO: 더블 버퍼링 코드를 병합해야 합니다.
	CSceneMgr::GetInstance()->GetCurrentScene()->Render(m_hDCBack);
	CUIMgr::GetInstance()->Render(m_hDCBack);
	CCameraMgr::GetInstance()->Render(m_hDCBack);
	::BitBlt(m_hDC, 0, 0, m_rect.right, m_rect.bottom, m_hDCBack, 0, 0, SRCCOPY);
	::PatBlt(m_hDCBack, 0, 0, m_rect.right, m_rect.bottom, WHITENESS);
	// 여기까지 병합해야 합니다.
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSoundMgr::Destroy_Instance();
	CUIMgr::DestroyInstance();
	CCollisionMgr::DestroyInstance();
	CScrollMgr::DestroyInstance();
	CCameraMgr::DestroyInstance();
	CBmpMgr::DestroyInstance();

	if (nullptr != CSceneMgr::GetInstance()->GetCurrentScene())
	{
		CSceneMgr::GetInstance()->DeleteScene();
	}

	CTileMgr::DestroyInstance();
	CLineMgr::DestroyInstance();
	CKeyMgr::DestroyInstance();
	CSceneMgr::DestroyInstance();
	CPlayer::DestroyInstance();
	CSoundMgr::Destroy_Instance();

	ReleaseDC(m_hWnd, m_hDC);
}
