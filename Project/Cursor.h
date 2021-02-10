#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// カーソルの基準位置
/// </summary>
// ********************************************************************************
enum class BasePosCursor
{
    Left,
    Right,
};

// ********************************************************************************
/// <summary>
/// カーソルの状態
/// </summary>
// ********************************************************************************
enum class CursorState
{
    Wait,
    Choice,
    Swap,
};

// ********************************************************************************
/// <summary>
/// カーソルクラス
/// </summary>
// ********************************************************************************
class CPuzzleCursor
{
private:

    Vector2       m_Pos         { 0, 0 };
    Vector2       m_BlockSize   { 0, 0 };
                                
    BasePosCursor m_BasePos     { BasePosCursor::Left };
                                
    CursorState   m_State       { CursorState::Wait };
    Vector2       m_PrevHoldPos { -1, -1 };
    Vector2       m_NowHoldPos  { -1, -1 };

    bool          m_bHold       { false };

public:

    void Initialize(const Vector2& pos, const Vector2& blockSize);

    void Update(void);

    void Render(void);
    void RenderDebug(void);

    void SetPos(const Vector2& pos);
    void SetBlockSize(const Vector2& size);
    void SetPrevHoldPos(const Vector2& pos);

    Vector2 GetPos(void) const;
    Vector2 GetPrevHoldPos(void) const;
    Vector2 GetNowHoldPos(void) const;
    void AfterSwap(void);

    BasePosCursor GetBaseCursor(void) const;
    CursorState GetState(void) const;

private:

    void RenderCursor(const Vector2& pos);

    void Choice(const Vector2& pos);
};

