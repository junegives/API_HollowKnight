#pragma once
#include "Creature.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "HitBox.h"
#include "UIMgr.h"

class CPlayer : public CCreature {
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize()		override;
	virtual int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hdc)	override;
	virtual void Release()			override;

public:
	static CPlayer* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CPlayer;
		}

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	virtual void OnCollided(CObject* _pObject) override;
	virtual void OnCollided(CObject* _pObject, EDirection _eDir) override;
	virtual void MotionChange()		override;

public:
	void KeyInput();
	void PlayerMove();
	void PlayerFall();
	void PlayerJump();
	void PlayerDoubleJump();
	void PlayerDash();
	void PlayerSlash();
	void PlayerClimb();
	void PlayerWallJump();
	void PlayerShoot();
	void PlayerStun();
	void PlayerReady();
	void PlayerFocusStart();
	void PlayerFocus();
	void PlayerFocusGet();
	void PlayerFocusEnd();
	void PlayerDead();

	void SetLeft(bool _isLeft) { m_bLeft = _isLeft; }

private:
	float			m_fSpeed = 0.f;
	float			m_fJumpSpeed = 0.f;
	float			m_fFallSpeed = 0.f;
	float			m_fJumpTime = 0.f;
	float			m_fWallJumpTime = 0.f;
	float			m_fDoubleJumpTime = 0.f;
	float			m_fDashSpeed = 0.f;
	float			m_fDashTime = 0.f;
	float			m_fSlashTime = 0.f;
	float			m_fShootTime = 0.f;
	float			m_fStunTime = 0.f;
	float			m_fDeadTime = 0.f;
	float			m_fRestartTime = 0.f;

	int				m_iFocusTime = 0;
	int				m_iPressingSTime = 0;

	bool			m_isFocusStartEnd = false;
	bool			m_isFocusEnd = false;
	bool			m_isFocusGetEnd = false;

	EPlayerState	m_ePreState = EPlayerState::ENUM_END;
	EPlayerState	m_eCurState = EPlayerState::ENUM_END;

private:
	static CPlayer*	m_pInstance;
	CObject*		m_currentCollided;

	bool isIdle = false;
	bool isWalk = false;
	bool isSlash = false;
	bool isSlashUp = false;
	bool isSlashDown = false;
	bool isDash = false;
	bool isDeath = false;
	bool isFocus = false;
	bool isFocusEnd = false;
	bool isFocusGet = false;
	bool isFocusGetOnce = false;
	bool isShoot = false;
	bool isJump = false;
	bool isDoubleJump = false;
	bool isFall = false;
	bool isClimb = false;
	bool isWallJump = false;

	bool m_bBlockTrigger = false;
	bool m_bBlockAll = false;
	bool m_bBossFight = false;
	bool m_bBossComplete = false;
	int	 m_iBlockTime = 0;

public:
	// 체력 회복 
	// 회복 했으면 true 반환
	// 풀피라 회복 못하면 false 반환
	bool	increaseHP(int _iIncrease)
	{
		if (m_iHP >= MAXHP) return false;
		m_iHP += _iIncrease;
		if (m_iHP >= MAXHP)
		{
			m_iHP = MAXHP;
		}
		CUIMgr::GetInstance()->gainHP();
		return true;
	}
	// 체력 셋
	void	setHP(int _iHP) {
		m_iHP = _iHP;
		if (m_iHP >= MAXHP)
		{
			m_iHP = MAXHP;
			m_isHPFull = true;
			m_isDead = false;
		}
		else if (m_iHP <= 0)
		{
			m_iHP = 0;
			m_isDead = true;
			m_isHPFull = false;
		}
		else
		{
			m_isDead = false;
			m_isHPFull = false;
		}
	}
	// 체력 겟
	int		getHP() { return m_iHP; }

	int		getHPMax() { return MAXHP; }

	// 소울 소모
	bool	useSoul(int _iUsing)
	{
		if (m_iSoul - _iUsing < 0) return false;
		m_iSoul -= _iUsing;
		if (m_iSoul == 0)
		{
			m_isSoulEmpty = true;
		}
		std::cout << m_iSoul << std::endl;
		CUIMgr::GetInstance()->useSoul();
		return true;
	}
	// 소울 획득
	bool	gainSoul(int _iGet)
	{
		if (m_iSoul >= MAXSOUL) return false;
		m_iSoul += _iGet;
		if (m_iSoul >= MAXSOUL)
		{
			m_iSoul = 300;
			m_isSoulFull = true;
		}
		std::cout << m_iSoul << std::endl;
		CUIMgr::GetInstance()->gainSoul();
		return true;

	}
	// 소울 셋
	void	setSoul(int _iSoul) {
		m_iSoul = _iSoul;
		if (m_iSoul >= MAXSOUL)
		{
			m_iSoul = MAXSOUL;
			m_isSoulFull = true;
			m_isSoulEmpty = false;
		}
		else if (m_iSoul <= 0)
		{
			m_iSoul = 0;
			m_isSoulFull = false;
			m_isSoulEmpty = true;
		}
		else
		{
			m_isSoulFull = false;
			m_isSoulEmpty = false;
		}
	}
	// 소울 겟
	int	getSoul() { return m_iSoul; }

	// 지오 획득
	void	gainGeo(int _iGet)
	{
		m_iGeo += _iGet;
	}
	// 지오 사용
	bool	useGeo(int _iUse)
	{
		if (0 > m_iGeo - _iUse)
		{
			return false;
		}
		m_iGeo -= _iUse;
		return true;
	}
	// 모든 지오 잃어버림
	void	loseAllGeo() { m_iGeo = 0; }
	// 지오 셋
	void	setGeo(int _iGeo) { m_iGeo = _iGeo; }
	// 지오 겟
	int		getGeo() { return m_iGeo; }

private:

	int		m_iSoul = MAXSOUL;
	bool	m_isSoulEmpty = false;
	bool	m_isSoulFull = false;

	int		m_iGeo = 0;

// 이펙트
private:
	// 포커스
	CObject*	m_pFocusEffect;
	bool		m_showFocusEffect = false;
	int			m_iFocusEffectTime = 0;

// 스킬
	CObject*	m_pSlash;
	bool		m_showSlash = false;
	int			m_iSlashTime = 0;

	CObject*	m_pFireBall;
	bool		m_showFire = false;
	int			m_iFireTime = 0;

private:
	bool	m_isChangeScene = false;

public:
	bool	GetChangeScene() { return m_isChangeScene; }

private:
	bool	m_isInitialized = false;

public:
	bool	GetInitiailized() { return m_isInitialized; }

private:
	list<CObject*> m_pItemList;
	int				m_iMaxItem = 3;

public:
	bool	AddItem(CObject* _pItem);
	bool	UseItem(int		_iItemNum);

// 맵이 초기화돼도 기억해야하는 정보
private:
	bool	m_isMantisComplete = false;
	bool	m_isGetWallJump = false;
	bool	m_isFinalBossComplete = false;

public:
	void	SetMantisComplete(bool _isCompleted) { m_isMantisComplete = _isCompleted; }
	void	SetFinalBossComplete(bool _isCompleted) { m_isFinalBossComplete = _isCompleted; }
	void	SetHaveWallJump(bool _isGet) { m_isGetWallJump = _isGet; }
	bool	GetMantisComplete() { return m_isMantisComplete; }
	bool	GetFinalBossComplete() { return m_isFinalBossComplete; }
	bool	GetHaveWallJump() { return m_isGetWallJump; }
	void	PlayerRestart();

private:
	bool	m_canWallJump = false;
	bool	m_isHaveKey = false;

public:
	bool	GetCanWallJump() { return m_canWallJump; }
	void	SetCanWallJump(bool _can) { m_canWallJump = _can; }

	bool	isHaveKey() { return m_isHaveKey; }
	void	SetHaveKey(bool _have) { m_isHaveKey = _have; }

private:
	bool	m_isBlockLeft = false;
	bool	m_isBlockRight = false;
};