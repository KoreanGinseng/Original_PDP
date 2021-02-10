#include "UIPanel.h"
#include "ScreenUtilites.h"

CUIPanel::CUIPanel(void)
{
    const float w = g_ScreenUtilities.GetMonitorWidth();
    const float h = g_ScreenUtilities.GetMonitorHeight();
    const float margin = MOF_MIN(w, h) * UI_MarginRatio;
    
    m_Rect[UIPanel_ScoreBoard].Left = margin;
    m_Rect[UIPanel_ScoreBoard].Top  = margin;
    m_Rect[UIPanel_ScoreBoard].SetWidth (w * UI_ScoreBoardRatioW);
    m_Rect[UIPanel_ScoreBoard].SetHeight(h * UI_ScoreBoardRatioH);

    m_Rect[UIPanel_PuzzleArea].Left = margin;
    m_Rect[UIPanel_PuzzleArea].Top  = m_Rect[UIPanel_ScoreBoard].Bottom + margin;
    m_Rect[UIPanel_PuzzleArea].SetWidth (w * UI_PuzzleAreaRatioW);
    m_Rect[UIPanel_PuzzleArea].SetHeight(h * UI_PuzzleAreaRatioH);

    m_Rect[UIPanel_ButtonArea].Left = m_Rect[UIPanel_PuzzleArea].Right + margin;
    m_Rect[UIPanel_ButtonArea].Top  = m_Rect[UIPanel_PuzzleArea].Top;
    m_Rect[UIPanel_ButtonArea].SetWidth (w * UI_ButtonAreaRatioW);
    m_Rect[UIPanel_ButtonArea].SetHeight(h * UI_ButtonAreaRatioH);
}

CUIPanel::~CUIPanel(void)
{
}

CRectangle CUIPanel::GetRect(UIPanel n) const
{
    return m_Rect[n];
}
