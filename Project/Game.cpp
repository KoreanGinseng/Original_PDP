#include "Game.h"
#include "FieldDataManager.h"

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// ‰Šú‰»ˆ—
    GameDifficulty& p1diff = GetData().p1_difficulty;
    GameDifficulty& p2diff = GetData().p2_difficulty;

    m_P1Difficulty.SetDifficulty(p1diff);
    m_P1Difficulty.SetDifficulty(p2diff);
    
    int fieldNo  = CUtilities::Random(g_FieldDataManager.GetFieldDataCount());
    FieldData p1 = g_FieldDataManager.GetFieldData(p1diff, fieldNo);
    ShuffleColor(m_P1Difficulty.GetColorCount(), p1);
    
    m_Puzzle.Initialize(&m_Panel, p1, p1diff); /*
  */Vector2 blockSize = m_Puzzle.GetBlockSize();
    
    Vector2 cursorPos;
    cursorPos.x = blockSize.x * 2 + m_Panel.GetRect(UIPanel_PuzzleArea).Left;
    cursorPos.y = blockSize.y * 5 + m_Panel.GetRect(UIPanel_PuzzleArea).Top;
    m_Cursor.Initialize(cursorPos, blockSize);
}

CGame::~CGame(void)
{
	// ‰ð•úˆ—
}

void CGame::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		ChangeScene(SceneName::Title);
	}

    m_Cursor.Update();

    m_Puzzle.Update(&m_Cursor);

}

void CGame::Render(void)
{
    for (int i = 0; i < UIPanel_Count; i++)
    {
        CGraphicsUtilities::RenderFillRect(m_Panel.GetRect((UIPanel)i), MOF_COLOR_BLACK);
    }

    m_Puzzle.Render();
    m_Cursor.Render();

    if (g_bDebug)
    {
        m_Puzzle.RenderDebug();
        m_Cursor.RenderDebug();
    }
}

void CGame::ShuffleColor(int colCnt, FieldData & inout)
{
    int rand = CUtilities::Random(colCnt);

    for (int y = 0; y < StageBlockYMax; y++)
    {
        for (int x = 0; x < StageBlockXMax; x++)
        {
            if (inout[y][x] == BlockType::BlockType_None)
            {
                continue;
            }
            int n = static_cast<int>(inout[y][x]);
            n = (n + rand) % colCnt;
            inout[y][x] = static_cast<BlockType>(n);
        }
    }
}
