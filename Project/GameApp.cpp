/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
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
bool        g_bDebug{ false }; //! デバッグ用フラグ

// 起動時に読み込みを行う関数。
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
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// 素材フォルダの指定
	CUtilities::SetCurrentDirectory("Resource");

	// 各シーンの追加と、フェード色の設定。
	m_SceneManager
		.Add<CTitle>(SceneName::Title)
		.Add<CGame>(SceneName::Game)
		.Add<CLoad>(SceneName::Load)
		.SetFadeColor(MOF_COLOR_WHITE);

	// 読み込み関数の登録。
	CLoad::SetLoadFunc("StartLoad", StartLoad);

	// 読み込みシーンで実行する読み込み関数の指定。
	CLoad::SetLoadFuncName("StartLoad");

	// 読み込みが終わったあとの次のシーン。
	CLoad::SetNextScene(SceneName::Game);

	// 開始シーンの設定。
	m_SceneManager.Initialize(SceneName::Load);

#ifdef _DEBUG
        g_bDebug = true;
#endif

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

#ifdef _DEBUG
    // F1キーでデバッグモードの切り替え
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

	// 各シーンの更新。
	if (!m_SceneManager.Update())
	{
		// シーン更新中にエラーが発生した場合の処理。
		PostQuitMessage(1);
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);

	// 各シーンの描画。
	if (!m_SceneManager.Render())
	{
		// シーン描画中にエラーが発生した場合の処理。
		PostQuitMessage(2);
	}

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	// 各アセットの解放。
	CFontAsset::Release();
	CMeshAsset::Release();
	CAnimAsset::Release();
	CSoundAsset::Release();
	CEffectAsset::Release();
	CTextureAsset::Release();

	return TRUE;
}