#include "Cursor.h"
#include "Puzzle.h"

void CPuzzleCursor::Initialize(const Vector2 & pos, const Vector2 & blockSize)
{
    SetPos(pos);
    SetBlockSize(blockSize);
}

void CPuzzleCursor::Update(void)
{
    m_State = CursorState::Wait;
    // カーソルアニメーション以外はクリックされない限り更新しない
    if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
    {
        Vector2 mp;
        g_pInput->GetMousePos(mp);
        Vector2 fieldPos = CPuzzle::ToFieldPos(mp);
        if (fieldPos != InvalidPos)
        {
            Choice(mp);
            m_PrevHoldPos = fieldPos;
            m_State = CursorState::Choice;
            m_bHold = true;
        }
        return;
    }
    else if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
    {
        Vector2 mp;
        g_pInput->GetMousePos(mp);
        Vector2 outPos;
        Vector2 fieldPos = CPuzzle::ToFieldPos(mp, &outPos);
        if (m_bHold)
        {
            if (fieldPos == InvalidPos)
            {
                fieldPos.x = MOF_CLIPING(outPos.x, 0, StageBlockXMax - 1);
            }
            m_NowHoldPos = fieldPos;
            if (m_PrevHoldPos.x != m_NowHoldPos.x)
            {
                m_State = CursorState::Swap;
            }
        }
        return;
    }
    else if (g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
    {
        m_PrevHoldPos = Vector2(-1, -1);
        m_NowHoldPos = Vector2(-1, -1);
        m_bHold = false;
    }
}

void CPuzzleCursor::Render(void)
{
    RenderCursor(m_Pos);
    if (m_BasePos == BasePosCursor::Left)
    {
        RenderCursor(m_Pos + Vector2(m_BlockSize.x, 0));
    }
    else if (m_BasePos == BasePosCursor::Right)
    {
        RenderCursor(m_Pos - Vector2(m_BlockSize.x, 0));
    }
}

void CPuzzleCursor::RenderDebug(void)
{
    CGraphicsUtilities::RenderString(10, 10, "カーソル基準位置 : %s", (m_BasePos == BasePosCursor::Left) ? "左" : "右");
}

void CPuzzleCursor::SetPos(const Vector2 & pos)
{
    m_Pos = pos;
}

void CPuzzleCursor::SetBlockSize(const Vector2 & size)
{
    m_BlockSize = size;
}

void CPuzzleCursor::SetPrevHoldPos(const Vector2 & pos)
{
    m_PrevHoldPos = pos;
}

Vector2 CPuzzleCursor::GetPos(void) const
{
    return m_Pos;
}

Vector2 CPuzzleCursor::GetNowHoldPos(void) const
{
    return m_NowHoldPos;
}

void CPuzzleCursor::AfterSwap(void)
{
    m_PrevHoldPos = m_NowHoldPos;
}

Vector2 CPuzzleCursor::GetPrevHoldPos(void) const
{
    return m_PrevHoldPos;
}

BasePosCursor CPuzzleCursor::GetBaseCursor(void) const
{
    return m_BasePos;
}

CursorState CPuzzleCursor::GetState(void) const
{
    return m_State;
}

void CPuzzleCursor::RenderCursor(const Vector2 & pos)
{
    Vector2 renderPos = pos;
    const float ratio = 0.05f;
    const float lengthRatio = 0.15f;
    renderPos -= m_BlockSize * ratio;

    CRectangle rect[] =
    {
        { renderPos, renderPos + Vector2(m_BlockSize.x * lengthRatio * 2, m_BlockSize.y * lengthRatio) },
        { renderPos, renderPos + Vector2(m_BlockSize.x * lengthRatio    , m_BlockSize.y * lengthRatio * 2) },
    };

    for (const auto& itr : rect)
    {
        CGraphicsUtilities::RenderFillRect(itr, MOF_COLOR_WHITE);
    }

    renderPos.x = pos.x;
    renderPos.x += m_BlockSize.x + m_BlockSize.x * ratio;

    for (auto& itr : rect)
    {
        itr.SetPosition(renderPos - Vector2(itr.GetWidth(), 0));
        CGraphicsUtilities::RenderFillRect(itr, MOF_COLOR_WHITE);
    }

    renderPos = pos;
    renderPos.x -= m_BlockSize.x * ratio;
    renderPos.y += m_BlockSize.y + m_BlockSize.y * ratio;

    for (auto& itr : rect)
    {
        itr.SetPosition(renderPos - Vector2(0, itr.GetHeight()));
        CGraphicsUtilities::RenderFillRect(itr, MOF_COLOR_WHITE);
    }

    renderPos.x = pos.x + m_BlockSize.x + m_BlockSize.x * ratio;

    for (auto& itr : rect)
    {
        itr.SetPosition(renderPos - Vector2(itr.GetWidth(), itr.GetHeight()));
        CGraphicsUtilities::RenderFillRect(itr, MOF_COLOR_WHITE);
    }
}

void CPuzzleCursor::Choice(const Vector2& pos)
{
    Vector2 fieldPos = CPuzzle::ToFieldPos(pos);
    Vector2 nowFieldPos = CPuzzle::ToFieldPos(m_Pos);

    if (m_BasePos == BasePosCursor::Left)
    {
        if (fieldPos.x == (StageBlockXMax - 1) || fieldPos.x == (nowFieldPos.x + 1))
        {
            m_BasePos = BasePosCursor::Right;
        }
    }
    else if (m_BasePos == BasePosCursor::Right)
    {
        if (fieldPos.x == 0 || fieldPos.x == (nowFieldPos.x - 1))
        {
            m_BasePos = BasePosCursor::Left;
        }
    }

    m_Pos = CPuzzle::ToScreenPos(fieldPos);
}
