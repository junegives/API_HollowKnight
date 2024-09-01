#pragma once

class CObject;
class CLine;

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static CCollisionMgr* GetInstance()
	{
		if (!_instance)
		{
			_instance = new CCollisionMgr();
		}

		return _instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

public:
	static bool PlayerAndTile(list<CObject*> _srcList, list<CObject*> _dstList);
	static bool PlayerAndTileEx(list<CObject*> _srcList, list<CObject*> _dstList);
	static void MonsterAndTile(list<CObject*> srcList, list<CObject*> _dstList);
	static void PlayerAndMonster(list<CObject*> srcList, list<CObject*> _dstList);
	static void PlayerAndProjectile(list<CObject*> srcList, list<CObject*> _dstList);
	static void PlayerAndGeo(list<CObject*> srcList, list<CObject*> _dstList);
	static void SkillAndMonster(list<CObject*> srcList, list<CObject*> _dstList);
	static void GeoAndTile(list<CObject*> srcList, list<CObject*> _dstList);
	static void SkillAndTile(list<CObject*> srcList, list<CObject*> _dstList);

	static void CollisionMonster(list<CObject*> _srcList, list<CObject*> _dstList);
	static bool CheckLineMonster(CObject* _pSrc, CObject* _pDst);
	static bool CheckRectMonster(CObject* _pSrc, CObject* _pDst);
	static bool CheckTriangleMonster(CObject* _pSrc, CObject* _pDst);

	static void	CollisionRect(list<CObject*> _srcList, list<CObject*> _dstList);
	static void	CollisionTile(list<CObject*> _srcList, list<CObject*> _dstList);
	static bool	CheckRect(CObject* _pSrc, CObject* _pDst, float* pX, float* pY);

	static bool	CheckSphere(CObject* _pSrc, CObject* _pDst);
	static void CollisionSphere(list<CObject*> _srcList, list<CObject*> _dstList);

	static bool CheckLine(CObject* _pSrc, CLine* _pDst);
	static void CollisionLine(list<CObject*> _srcList, list<CLine*> _dstList);

	static RECT GetRect(CObject* _pSrc);

private:
	static CCollisionMgr* _instance;
};

