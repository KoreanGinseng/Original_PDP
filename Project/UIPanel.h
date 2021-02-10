#pragma once
#include "Mof.h"

constexpr float UI_MarginRatio      = 0.05f;

constexpr float UI_ScoreBoardRatioW = 1.0f - (UI_MarginRatio * 2);
constexpr float UI_ScoreBoardRatioH = 0.2f;

constexpr float UI_PuzzleAreaRatioW = 0.6f;
constexpr float UI_PuzzleAreaRatioH = 1.0f - (UI_MarginRatio * 2 + UI_ScoreBoardRatioH);

constexpr float UI_ButtonAreaRatioW = 1.0f - (UI_PuzzleAreaRatioW + UI_MarginRatio + UI_MarginRatio * 2);
constexpr float UI_ButtonAreaRatioH = UI_PuzzleAreaRatioH;

enum UIPanel
{
    UIPanel_ScoreBoard,
    UIPanel_PuzzleArea,
    UIPanel_ButtonArea,

    UIPanel_Count,
};

// ********************************************************************************
/// <summary>
/// UIパネルクラス
/// </summary>
// ********************************************************************************
class CUIPanel
{
private:

    CRectangle m_Rect[UIPanel_Count];

public:

    CUIPanel(void);

    ~CUIPanel(void);

    CRectangle GetRect(UIPanel n) const;
};

