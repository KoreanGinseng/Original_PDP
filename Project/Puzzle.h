#pragma once
#include "Mof.h"
#include "UIPanel.h"
#include "Block.h"
#include "Common.h"

const Vector2 InvalidPos{ -1, -1 };

class CPuzzleCursor;

// ********************************************************************************
/// <summary>
/// パズルクラス
/// </summary>
// ********************************************************************************
class CPuzzle
{
private:

    GameDifficulty   m_Defficulty{ GameDifficulty::Easy };

    Vector2          m_BlockPositions[StageBlockYMax][StageBlockXMax];
    Vector2          m_BlockSize;
    FieldData        m_FieldData;
    CBlock           m_Blocks[StageBlockYMax][StageBlockXMax];

    static CUIPanel* m_spPanel;

public:

    CPuzzle(void);
    
    ~CPuzzle(void);

    void Initialize(CUIPanel* pPanel, const FieldData& fieldData, GameDifficulty diff);
    void Update(CPuzzleCursor* pCursor);
    void Render(void);
    void RenderDebug(void);

    void SetUIPanel(CUIPanel* p);

    Vector2 GetBlockSize(void) const;

    static Vector2 ToFieldPos(const Vector2& pos, Vector2* out = nullptr);
    static Vector2 ToScreenPos(const Vector2& pos);

private:

    void FieldUpdate(void);

    bool LineCheck(std::vector<std::vector<Vector2>>& outPosArray);
    bool ColumnCheck(std::vector<std::vector<Vector2>>& outPosArray);
    void Move(void);
    void Delete(void);
    void Drop(void);
};

