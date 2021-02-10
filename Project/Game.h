#pragma once
#include "Common.h"
#include "Block.h"
#include "UIPanel.h"
#include "Puzzle.h"
#include "Cursor.h"
#include "GameDifficulty.h"

class CGame : public MyApp::CScene
{
private:

    CPuzzle         m_Puzzle;

    CUIPanel        m_Panel;

    CGameDifficulty m_P1Difficulty{ GameDifficulty::Normal };

    CGameDifficulty m_P2Difficulty{ GameDifficulty::Normal };

    CPuzzleCursor   m_Cursor;

public:
	
	explicit CGame(const CGame::InitData& init);

	virtual ~CGame(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) override;

private:

    void ShuffleColor(int colCnt, FieldData& inout);
};