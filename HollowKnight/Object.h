#pragma once

class CObject abstract
{
public:
	CObject() = default;
	virtual ~CObject() = default;

public:
	virtual void Initialize()		= 0;
	virtual int Update()			= 0;
	virtual void LateUpdate()		= 0;
	virtual void Render(HDC _hdc)	= 0;
	virtual void Release()			= 0;

public:
	/*
	* OnCollided()
	* �ٸ� ������Ʈ�� �浹���� ��, ȣ���մϴ�.
	* 
	* @param CObject*: �� ������Ʈ�� �浹�� �ٸ� ������Ʈ�� �������Դϴ�.
	*/
	virtual void OnCollided(CObject* _pObject);
	virtual void OnCollided(CObject* _pObject, EDirection _eDirection);
	void		Move_Frame();

public:
	EObjectType GetObjectType() const { return m_eObjectType; }
	void SetObjectType(EObjectType _eObjectType) { m_eObjectType = _eObjectType; }

	ERenderID GetRenderID() const { return m_eRender; }
	void SetRenderID(ERenderID _eRenderID) { m_eRender = _eRenderID; }

	Vector GetPosition() const { return m_tPosition; }
	void SetPosition(Vector _tPosition) { m_tPosition = _tPosition; }

	float GetRadius() const { return m_fRadius; }
	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

	float GetDegree() const { return m_fDegree; }
	void SetDegree(float _fDegree) { m_fDegree = _fDegree; }

	float GetSpeed() const { return m_fSpeed; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	bool GetIsDead() const { return m_bDead; }
	void SetIsDead(bool _bDead) { m_bDead = _bDead; }

	Vector GetSize() const { return m_tSize; }
	void SetSize(Vector _tSize) { m_tSize = _tSize; }

	bool isOnGravity() const { return m_onGravity; }
	void SetOnGravity(bool _bOn) { m_onGravity = _bOn; }

	CObject* GetHitBox() { return m_cHitBox; }
	bool	GetCanCollision() { return m_bCanCollision; }
	void	SetCanCollision(bool _bCanCollision) { m_bCanCollision = _bCanCollision; }

	void setFrameKey(TCHAR* _pFrameKey, int _End, int _Speed);
	TCHAR* getFrameKey() { return m_pFrameKey; }
	void SetVisible(bool _isVisible) { m_isVisible = _isVisible; }
	bool GettVisible() { return m_isVisible; }


protected:
	// ������Ʈ�� Ÿ��
	EObjectType m_eObjectType = EObjectType::ENUM_END;

	// ������Ʈ�� ����, ���� ����
	Vector m_tSize{ 0.0f, 0.0f };

	// ������Ʈ�� ��� ��ǥ
	Vector m_tPosition{ 0.0f, 0.0f };

	// ������Ʈ�� ������
	float m_fRadius = 0.0f;

	// ������Ʈ�� �ӵ�
	float m_fSpeed = 0.0f;

	// ������Ʈ�� ����
	float m_fDegree = 0.0f;

	bool m_bDead = false;

	FRAME			m_tFrame;
	ERenderID		m_eRender;
	CObject*		m_pTarget;
	EDirection		m_eDir;
	TCHAR*	m_pFrameKey;

protected:
	Vector		m_tVel;
	Vector		m_tGravity = { 0.0f, -9.8f };
	float		m_fDt = 0.f;
	CObject*	m_cHitBox;
	bool		m_isVisible;
	bool		m_onGravity = true;
	bool		m_bCanCollision = true;
};

