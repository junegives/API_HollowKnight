#pragma once

/***************
	전처리기
***************/
const int VK_MAX = 0xff;
const int WINCX = 1920;
const int WINCY = 1080;
const float PI = 3.141592f;
const float GRAVITY = 20.f;
const int MAXHP = 7;
const int MAXSOUL = 300;

#define KEYMAX		256

#define SCENE		CSceneMgr::GetInstance()
#define GET_SCENE	CSceneMgr::GetInstance()->GetCurrentScene()

#define COLLISION	CCollisionMgr::GetInstance()

#define Line		CLineMgr::GetInstance()

#define KEY			CKeyMgr::GetInstance()

#define SCROLL		CScrollMgr::GetInstance()

#define CAMERA		CCameraMgr::GetInstance()

#define BMP			CBmpMgr::GetInstance()

/***************
	템플릿
***************/
template<typename T>
void SAFE_DELETE(T& _ptr)
{
	if (_ptr)
	{
		delete _ptr;
		_ptr = nullptr;
	}
}

struct SAFE_DELETE_FUNCTOR
{
	template<typename T>
	void operator()(T& _ptr)
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
};

extern HWND g_hWnd;

extern float g_fVolume;

