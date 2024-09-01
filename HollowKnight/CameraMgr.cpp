#include "pch.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

CCameraMgr::CCameraMgr()
{
}

CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::Initialize()
{
	CBmpMgr::GetInstance()->Insert_Bmp(L"../Resource/Image/Background/FadeOut.bmp", L"FadeOut");

	m_vResolution.m_fX = WINCX;
	m_vResolution.m_fY = WINCY;
}

void CCameraMgr::Update()
{
	// ������Ʈ Ÿ���� �ƴ� ���� Ÿ���� �����ϴ� ���
	if (m_bTempTarget)
	{
		// ���� Ÿ�ٿ� �̵����� ���
		if (m_isMoving)
		{
			// �Ÿ� = �ð� * �ӷ�
			// m_vToMove = m_fTime * x;
			m_vLookPos += m_vToMove / m_fTime;

			if (m_vLookPos == m_vTarget || (m_vLookPos-m_vTarget).Length() < 1.f)
			{
				m_isMoving = false;
				m_vLookPos = m_vTarget;
			}
		}
	}

	// ������Ʈ Ÿ���� �����ϴ� ���
	else if (m_pTarget)
	{
		if (m_pTarget->GetIsDead())
			m_pTarget = nullptr;

		else
		{
			m_vLookPos = m_pTarget->GetPosition();

			if (m_vLookPos.m_fX <= m_fMinX)
				m_vLookPos.m_fX = m_fMinX;
			if (m_vLookPos.m_fX >= m_fMaxX)
				m_vLookPos.m_fX = m_fMaxX;
			if (m_vLookPos.m_fY >= m_fMinY)
				m_vLookPos.m_fY = m_fMinY;
			if (m_vLookPos.m_fY <= m_fMaxY)
				m_vLookPos.m_fY = m_fMaxY;
		}
	}

	// ����ŷ�ϴ� ���
	if (m_bShaking)
	{
		if (m_iShakingTime < m_iTime)
		{
			if (!(m_iShakingTime % 3))
			{
				m_iShakingDir *= -1;
			}
				
			// ����ŷ ���� (���� ���߱� ���ؼ� ���� �����ֱ�)
			if (0 > m_iShakingDir)
			{
				m_fShakingAmount = (m_iTime - m_iShakingTime) / 10 * m_iShakingDir;
			}
			else
			{
				m_fShakingAmount = (m_iTime - m_iShakingTime + 3) / 10 * m_iShakingDir;
			}

			m_vLookPos += { m_fShakingAmount, m_fShakingAmount };
			++m_iShakingTime;
		}

		else 
		{
			m_bShaking = false;
			m_iShakingTime = 0;
		}
	}

	if (m_isFadeOut)
	{
		if (m_iFadeOutTime < 255)
		{
		}

		else if (m_iFadeOutTime == 256)
		{
			CPlayer::GetInstance()->PlayerRestart();
			UnLock();
			m_iFadeOutTime++;
		}

		else if (m_iFadeOutTime < 300)
		{
			m_iFadeOutTime++;
		}

		else if (m_iFadeOutTime < 423)
		{
			FadeIn();
			m_iFadeOutTime++;
		}

		else
		{
			m_isFadeOut = false;
		}
	}

	CalcDiff();
}

void CCameraMgr::Render(HDC _hDC)
{
	if (m_isFadeOut)
	{
		HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(L"FadeOut");

		Vector vRenderPos = CCameraMgr::GetInstance()->GetLookPos();

		BLENDFUNCTION bf = {};
		
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = m_iAlpahValue;

		AlphaBlend(_hDC, 0, 0,
			WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, bf);
	}
}

void CCameraMgr::SlowMoveToTarget(Vector _vTarget, float _fTime)
{
	m_bTempTarget = true;
	m_isMoving = true;

	m_vTarget = _vTarget;
	// ��ǥ ��ġ ���� - �ٶ󺸰� �ִ� ���� = ���������� ����
	m_vToMove = _vTarget - m_vLookPos;
	// �̵��ϴµ� �ҿ��� �ð�
	m_fTime = _fTime;
}

void CCameraMgr::CalcDiff()
{
	m_vDiff = m_vLookPos - (m_vResolution / 2.f);
}

Vector CCameraMgr::GetRenderPos(Vector _vObjPos)
{
	return _vObjPos - m_vDiff;
}

Vector CCameraMgr::GetLookPos()
{
	return m_vLookPos;
}

void CCameraMgr::CameraShaking(int _iTime)
{
	m_bShaking = true;

	// ����ŷ�� �ҿ��� �ð�
	m_iTime = _iTime;
}

void CCameraMgr::FadeOut()
{
	m_isFadeOut = true;

	//BLENDFUNCTION _bf = {};
	//_bf.BlendOp = AC_SRC_OVER;
	//_bf.BlendFlags = 0;
	//_bf.AlphaFormat = AC_SRC_OVER;
	//_bf.SourceConstantAlpha = m_iFadeOutTime;

	//HDC hDC = GetDC(g_hWnd);
	//HDC hBackDC = {};
	//HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(L"FadeOut");
	//Vector vRenderPos = CCameraMgr::GetInstance()->GetLookPos();


	//GdiAlphaBlend(hBackDC, 0, 0, vRenderPos.m_fX - WINCX/2, vRenderPos.m_fX - WINCY / 2, hMemDC, 0, 0, WINCX, WINCY, _bf);
	//::BitBlt(hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
	//::PatBlt(hBackDC, 0, 0, WINCX, WINCY, WHITENESS);

	m_iFadeOutTime += 2;
	if (m_iFadeOutTime < 256)
		m_iAlpahValue = m_iFadeOutTime;
}

void CCameraMgr::FadeIn()
{
	m_iAlpahValue -= 2;
}
