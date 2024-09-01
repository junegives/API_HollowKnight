#include "pch.h"
//#include "SkillMgr.h"
//#include "BmpMgr.h"
//
//CSkillMgr* CSkillMgr::m_pInstance = nullptr;
//
//CSkillMgr::~CSkillMgr()
//{
//	Release();
//}
//
//void CSkillMgr::Initialize()
//{
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectDownSlash.bmp", L"EffectDownSlash");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectUpSlash.bmp", L"EffectUpSlash");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectSlash_L.bmp", L"EffectSlash_L");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/EffectSlash_R.bmp", L"EffectSlash_R");
//
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireStart_L.bmp", L"FireStart_L");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireShoot_L.bmp", L"FireShoot_L");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireEnd_L.bmp", L"FireEnd_L");
//
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireStart_R.bmp", L"FireStart_R");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireShoot_R.bmp", L"FireShoot_R");
//	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Skill/FireEnd_R.bmp", L"FireEnd_R");
//
//	// 파이어볼
//	{
//		m_pFireBall = new CSkill;
//		m_pFireBall->SetOnGravity(false);
//		m_pFireBall->Initialize();
//		m_SkillList.push_back(m_pFireBall);
//	}
//
//	// 슬래쉬
//	{
//		m_pSlash = new CSkill;
//		m_pSlash->SetOnGravity(false);
//		m_pSlash->Initialize();
//		m_SkillList.push_back(m_pSlash);
//	}
//}
//
//void CSkillMgr::Update()
//{
//}
//
//void CSkillMgr::LateUpdate()
//{
//}
//
//void CSkillMgr::Render(HDC _hDC)
//{
//}
//
//void CSkillMgr::Release()
//{
//}
