//#pragma once
//#include "Skill.h"
//
//class CSkillMgr
//{
//private:
//	CSkillMgr();
//	~CSkillMgr();
//
//public:
//	static CSkillMgr* GetInstance()
//	{
//		if (!m_pInstance)
//		{
//			m_pInstance = new CSkillMgr();
//		}
//
//		return m_pInstance;
//	}
//
//	static void DestroyInstance()
//	{
//		if (m_pInstance)
//		{
//			delete m_pInstance;
//			m_pInstance = nullptr;
//		}
//	}
//
//public:
//	void	Initialize();
//	void	Update();
//	void	LateUpdate();
//	void	Render(HDC _hDC);
//	void	Release();
//
//	list<CSkill*> GetList() { return m_SkillList; }
//
//private:
//	static CSkillMgr* m_pInstance;
//
//	list<CSkill*>	m_SkillList;
//	CSkill* m_pSlash;
//	CSkill* m_pFireBall;
//};