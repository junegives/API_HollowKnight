#pragma once

class CSoundMgr
{
public:
	static CSoundMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSoundMgr;
		}

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Release();

public:
	void PlaySound(TCHAR* pSoundKey, EChannelID eID, float fVolume);
	void PlayBGM(TCHAR* pSoundKey, float fVolume);
	void StopSound(EChannelID eID);
	void StopAll();
	void SetChannelVolume(EChannelID eID, float fVolume);

private:
	void LoadSoundFile();

private:
	static CSoundMgr* m_pInstance;

	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[(int)EChannelID::ENUM_END];

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
};

