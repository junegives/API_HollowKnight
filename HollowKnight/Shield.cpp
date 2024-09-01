#include "pch.h"
#include "Shield.h"
#include "HitBox.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CShield::CShield()
{
}

CShield::~CShield()
{
}

void CShield::Initialize()
{
	// Ÿ�� ����
	{
		m_eObjectType = EObjectType::PROJECTILE;
		m_eRender = ERenderID::EFFECT;
	}

	// ��Ʈ �ڽ� ����
	{
		m_cHitBox = new CHitBox;
		m_cHitBox->SetPosition(m_tPosition);
		m_cHitBox->SetSize({ 230.f, 75.f });
		m_cHitBox->Initialize();
		//CSceneMgr::GetInstance()->GetCurrentScene()->AddObject(m_cHitBox);
	}

	// �ൿ ����
	{
		m_fSpeed = 13.f;
		m_iTime = 0;
	}

	// ��� ����
	{
		switch (m_eDir)
		{
			// ���� ������ ���� ���
		case EDirection::LU:
			m_vDir = { m_fSpeed, m_fSpeed / 13 };
			break;

			// ������ ������ ���� ���
		case EDirection::RU:
			m_vDir = { -m_fSpeed, m_fSpeed / 13 };
			break;

			// ���� �Ʒ����� ���� ���
		case EDirection::LD:
			m_vDir = { m_fSpeed, -m_fSpeed / 13 };
			break;

			// ������ �Ʒ����� ���� ���
		case EDirection::RD:
			m_vDir = { -m_fSpeed, -m_fSpeed / 13 };
			break;
		}
	}

	CProjectile::Initialize();
}

int CShield::Update()
{
	CSoundMgr::Get_Instance()->PlaySound(L"M_MantisLordBoomerang.wav", EChannelID::MONSTERSKILL, g_fVolume);
	m_bDead = CalcPath();
	m_cHitBox->SetPosition(m_tPosition);

	// n�� �� �Ҹ�Ǵ°ɷ�

	return m_bDead;
}

void CShield::LateUpdate()
{
	__super::Move_Frame();
}

void CShield::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->Find_Img(m_pFrameKey);

	Vector vRenderPos = CAMERA->GetRenderPos(m_tPosition);

	GdiTransparentBlt(_hDC,
		vRenderPos.m_fX - m_tSize.m_fX / 2,
		vRenderPos.m_fY - m_tSize.m_fY / 2,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tSize.m_fX,
		0,
		(int)m_tSize.m_fX,
		(int)m_tSize.m_fY,
		RGB(255, 0, 255));	// �����ϰ��� �ϴ� ����
}

void CShield::Release()
{
	SAFE_DELETE(m_cHitBox);
}

void CShield::OnCollided(CObject* _pObject)
{
}

void CShield::OnCollided(CObject* _pObject, EDirection _eDirection)
{
}

bool CShield::CalcPath()
{
	if (100 > m_iTime)
	{
		SetPosition(m_tPosition + m_vDir);
		++m_iTime;
		return false;
	}
	else if (220 > m_iTime)
	{
		SetPosition({ m_tPosition.m_fX - m_vDir.m_fX, m_tPosition.m_fY + m_vDir.m_fY });
		++m_iTime;
		return false;
	}
	else
	{
		return true;
	}
}
