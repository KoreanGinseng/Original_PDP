#include "LoadBase.h"

std::string CLoadBase::m_LoadFuncName = "";

SceneName CLoadBase::m_NextKey;

std::unordered_map<std::string, LoadFunction> CLoadBase::m_LoadFuncMap;


CLoadBase::CLoadBase(const CLoadBase::InitData & init) :
	IScene(init)
{
	m_Thread.SetFunc(m_LoadFuncMap[m_LoadFuncName]);
	m_Thread.Start("GameLoadingThread");
}

CLoadBase::~CLoadBase(void)
{
	m_Thread.Release();
}

void CLoadBase::Update(void)
{
	// �X���b�h�œǂݍ��ݏ������I����ĂȂ���΂����ŏI���B
	if (!m_Thread.IsEnd())
	{
		return;
	}

	// �X���b�h�ǂݍ��݂��I����Ċ֐��Ŏ��s���Ă���ꍇ�A�A�v���P�[�V�����̏I���B
	if (!m_Thread.IsSuccess())
	{
		MessageBox(NULL, "�ǂݍ��݂Ɏ��s���܂����B", "�G���[", MB_ICONERROR | MB_OK);
		PostQuitMessage(3);
	}

	// �ǂݍ��݂������ŏI������ꍇ�A���̃V�[���֍s���B
	ChangeScene(m_NextKey);
}

void CLoadBase::Render(void)
{
}

void CLoadBase::SetLoadFunc(const std::string & key, const LoadFunction & func)
{
	m_LoadFuncMap[key] = func;
}

void CLoadBase::SetNextScene(const SceneName & next)
{
	m_NextKey = next;
}

void CLoadBase::SetLoadFuncName(const std::string & key)
{
	m_LoadFuncName = key;
}
