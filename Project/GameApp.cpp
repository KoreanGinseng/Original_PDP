/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "FieldDataManager.h"

// SCENE
#include    "Title.h"
#include    "Game.h"
#include    "Load.h"

// GLOBAL
bool        g_bDebug{ false }; //! �f�o�b�O�p�t���O

// �N�����ɓǂݍ��݂��s���֐��B
bool StartLoad(void)
{
    if (!g_FieldDataManager.Load())
    {
        return false;
    }

    if (!CAnimAsset::Load(AnimKey::EFC_Bomb, "bomb.anim"))
    {
        return false;
    }

    if (!CTextureAsset::Load(TextureKey::EFC_Bomb, AnimAsset(AnimKey::EFC_Bomb)->GetTextureFileName().c_str()))
    {
        return false;
    }

	return true;
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// �f�ރt�H���_�̎w��
	CUtilities::SetCurrentDirectory("Resource");

	// �e�V�[���̒ǉ��ƁA�t�F�[�h�F�̐ݒ�B
	m_SceneManager
		.Add<CTitle>(SceneName::Title)
		.Add<CGame>(SceneName::Game)
		.Add<CLoad>(SceneName::Load)
		.SetFadeColor(MOF_COLOR_WHITE);

	// �ǂݍ��݊֐��̓o�^�B
	CLoad::SetLoadFunc("StartLoad", StartLoad);

	// �ǂݍ��݃V�[���Ŏ��s����ǂݍ��݊֐��̎w��B
	CLoad::SetLoadFuncName("StartLoad");

	// �ǂݍ��݂��I��������Ƃ̎��̃V�[���B
	CLoad::SetNextScene(SceneName::Game);

	// �J�n�V�[���̐ݒ�B
	m_SceneManager.Initialize(SceneName::Load);

#ifdef _DEBUG
        g_bDebug = true;
#endif

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();

#ifdef _DEBUG
    // F1�L�[�Ńf�o�b�O���[�h�̐؂�ւ�
    if (g_pInput->IsKeyPush(MOFKEY_F1))
    {
        g_bDebug = !g_bDebug;
    }
    if (g_pInput->IsKeyPush(MOFKEY_F3))
    {
        float w = g_pGraphics->GetTargetWidth();
        float h = g_pGraphics->GetTargetHeight();
        g_pMainWindow->SetScreenSize(h, w);
        CGraphicsUtilities::SetScreenSize(h, w);
    }
#endif

	// �e�V�[���̍X�V�B
	if (!m_SceneManager.Update())
	{
		// �V�[���X�V���ɃG���[�����������ꍇ�̏����B
		PostQuitMessage(1);
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	// �e�V�[���̕`��B
	if (!m_SceneManager.Render())
	{
		// �V�[���`�撆�ɃG���[�����������ꍇ�̏����B
		PostQuitMessage(2);
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	// �e�A�Z�b�g�̉���B
	CFontAsset::Release();
	CMeshAsset::Release();
	CAnimAsset::Release();
	CSoundAsset::Release();
	CEffectAsset::Release();
	CTextureAsset::Release();

	return TRUE;
}