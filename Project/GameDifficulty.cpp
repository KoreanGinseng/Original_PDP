#include "GameDifficulty.h"

CGameDifficulty::CGameDifficulty(GameDifficulty diff)
{
    SetDifficulty(diff);
}

int CGameDifficulty::GetColorCount(void) const
{
    return m_ColorCount;
}

void CGameDifficulty::SetDifficulty(GameDifficulty diff)
{
    m_Difficulty = diff;
    switch (m_Difficulty)
    {
    case GameDifficulty::Easy:
        m_ColorCount = ColorCount_Easy;
        break;
    case GameDifficulty::Normal:
        m_ColorCount = ColorCount_Normal;
        break;
    case GameDifficulty::Hard:
        m_ColorCount = ColorCount_Herd;
        break;
    }
}
