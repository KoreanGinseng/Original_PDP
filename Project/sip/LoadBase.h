#pragma once
#include "../Common.h"

using LoadFunction = std::function<bool(void)>;

class CLoadThread : public CThread
{
private:

	bool                      m_bSuccess = false;

	bool                      m_bEnd = false;

	LoadFunction              m_Func;

public:

	CLoadThread(void) : CThread() {}

	~CLoadThread(void) {}

	virtual void Run(void) override
	{
		m_bSuccess = false;
		m_bEnd     = false;

		m_bSuccess = m_Func();

		m_bEnd     = true;
	}

	// �X���b�h�Ŏ��s����ǂݍ��݊֐��̓o�^�B
	void SetFunc(const LoadFunction& func)
	{
		m_Func = func;
	}

	const bool IsSuccess(void) const noexcept
	{
		return m_bSuccess;
	}

	const bool IsEnd(void) const noexcept
	{
		return m_bEnd;
	}
};

class CLoadBase : public MyApp::CScene
{
private:

	CLoadThread                                            m_Thread;

	static std::string                                     m_LoadFuncName;
	
	static SceneName                                       m_NextKey;

	static std::unordered_map<std::string, LoadFunction>   m_LoadFuncMap;

public:

	CLoadBase(const CLoadBase::InitData& init);

	virtual ~CLoadBase(void);

	virtual void Update(void) override;

	virtual void Render(void) override = 0;

	// �ǂݍ��݊֐��̓o�^�B
	static void SetLoadFunc(const std::string& key, const LoadFunction& func);

	// �ǂݍ��݂��I��������Ƃ̎��̃V�[���̐ݒ�B
	static void SetNextScene(const SceneName& next);

	// �o�^����Ă���֐�����A�ǂݍ��݂��s���֐��̎w��B
	static void SetLoadFuncName(const std::string& key);
};

