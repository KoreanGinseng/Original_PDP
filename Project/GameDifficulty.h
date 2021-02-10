#pragma once
#include "Common.h"

constexpr int ColorCount_Easy   = 4;
constexpr int ColorCount_Normal = 5;
constexpr int ColorCount_Herd   = 6;

// ********************************************************************************
/// <summary>
/// “ïˆÕ“xƒNƒ‰ƒX
/// </summary>
// ********************************************************************************
class CGameDifficulty
{
private:

    GameDifficulty m_Difficulty;
    int            m_ColorCount;
    float          m_DefUpperSpeed;
    float          m_AntiAirTimeSecond;

public:

    CGameDifficulty(GameDifficulty diff);
    ~CGameDifficulty(void) = default;

    int GetColorCount(void) const;

    void SetDifficulty(GameDifficulty diff);
};

