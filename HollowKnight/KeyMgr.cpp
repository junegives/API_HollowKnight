#include "pch.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyMgr::~CKeyMgr()
{

}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	if ((!m_bKeyState[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if (m_bKeyUpState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyUpState[_iKey] = !m_bKeyUpState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyUpState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeyUpState[i] = !m_bKeyUpState[i];
	}

	return false;
}

void CKeyMgr::Setup()
{
	// bit 모두 0으로 설정
	m_bitKeyUp.reset();
	m_bitKeyDown.reset();
}

bool CKeyMgr::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// 키가 이전에 눌리지 않은 상태
		if (!m_bitKeyDown[key])
		{
			// 눌린 상태로 변환
			m_bitKeyDown.set(key, true);
			return true;
		}
	}
	else
	{
		m_bitKeyDown.set(key, false);
	}

	return false;
}

bool CKeyMgr::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_bitKeyUp.set(key, true);
	}
	else
	{
		// 키가 눌렀다가 땠을 때
		if (m_bitKeyUp[key])
		{
			// 눌린 상태로 변환
			m_bitKeyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool CKeyMgr::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool CKeyMgr::isToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001) return true;
	return false;
}