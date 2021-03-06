#include "Title.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// 初期化処理
}

CTitle::~CTitle(void)
{
	// 解放処理
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		ChangeScene(SceneName::Game);
	}
}

void CTitle::Render(void)
{
	CGraphicsUtilities::RenderString(0, 0, "Title");
}
