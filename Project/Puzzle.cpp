#include "Puzzle.h"
#include "Cursor.h"
#include <array>

CUIPanel* CPuzzle::m_spPanel = nullptr;

CPuzzle::CPuzzle(void)
{
}

CPuzzle::~CPuzzle(void)
{
}

void CPuzzle::Initialize(CUIPanel* pPanel, const FieldData& fieldData, GameDifficulty diff)
{
    // ��Փx�̐ݒ�
    m_Defficulty = diff;

    // �p�l���̐ݒ�
    SetUIPanel(pPanel);
    
    // �p�Y���G���A�̊ȈՃA�N�Z�X�p
    const CRectangle puzzleArea = m_spPanel->GetRect(UIPanel_PuzzleArea);

    // �u���b�N�̃T�C�Y�v�Z
    const float sx = puzzleArea.GetWidth()  / StageBlockXMax;
    const float sy = puzzleArea.GetHeight() / StageBlockYMax;
    m_BlockSize = Vector2(sx, sy);

    // �u���b�N�̎�ސ����Փx�ɂ���ĕύX
    const int blockTypeMax = (m_Defficulty == GameDifficulty::Hard) ? (BlockType_Count) : (BlockType_Count - 1);

    // �u���b�N�̏�����
    for (int y = 0; y < StageBlockYMax; y++)
    {
        for (int x = 0; x < StageBlockXMax; x++)
        {
            // �u���b�N�����ʒu�v�Z
            const float px = puzzleArea.Left + x * sx;
            const float py = puzzleArea.Top  + y * sy;
            
            //m_BlockPositions[y][x] = Vector2(px, py);
            //m_FieldData[y][x] = fieldData[y][x];
            m_Blocks[y][x].Initialize(Vector2(px, py), m_BlockSize, fieldData[y][x]);
        }
    }
}

void CPuzzle::Update(CPuzzleCursor* pCursor)
{
    if (pCursor->GetState() == CursorState::Swap)
    {
        Vector2& prevPos = pCursor->GetPrevHoldPos();
        Vector2& nowPos  = pCursor->GetNowHoldPos();
        Vector2 diff{ 0, 0 };
        if (nowPos.x - prevPos.x < 0)
        {
            diff.x = -1;
        }
        else if (nowPos.x - prevPos.x > 0)
        {
            diff.x = 1;
        }
        
        CBlock& prevBlock = m_Blocks[(int)(prevPos.y)][(int)(prevPos.x)];
        CBlock& nextBlock = m_Blocks[(int)(prevPos.y)][(int)(prevPos.x + diff.x)];
        //BlockType& prevBlock = m_FieldData[(int)(prevPos.y)][(int)(prevPos.x)];
        //BlockType& nextBlock = m_FieldData[(int)(prevPos.y)][(int)(prevPos.x + diff.x)];

        // TODO : �X���b�v���u���b�N�N���X�Ɏ������Ă��
        // TODO : �������Ƃ���Ɠ���ւ���ƃu���b�N���Ŗ��
        BlockType temp = prevBlock.GetType();
        prevBlock.SetType(nextBlock.GetType());
        nextBlock.SetType(temp);

        pCursor->SetPrevHoldPos(prevPos + diff);
    }
    FieldUpdate();
}

void CPuzzle::Render(void)
{
    for (int y = 0; y < StageBlockYMax; y++)
    {
        for (int x = 0; x < StageBlockXMax; x++)
        {
            m_Blocks[y][x].Render();
            //CBlock::Render(CRectangle(m_BlockPositions[y][x], m_BlockPositions[y][x] + m_BlockSize), m_FieldData[y][x]);
        }
    }
}

void CPuzzle::RenderDebug(void)
{
}

void CPuzzle::SetUIPanel(CUIPanel * p)
{
    m_spPanel = p;
}

Vector2 CPuzzle::GetBlockSize(void) const
{
    return m_BlockSize;
}

Vector2 CPuzzle::ToFieldPos(const Vector2 & pos, Vector2* out)
{
    Vector2 offset = m_spPanel->GetRect(UIPanel_PuzzleArea).GetTopLeft();

    float temp = (pos.x - offset.x) / (m_spPanel->GetRect(UIPanel_PuzzleArea).GetWidth() / StageBlockXMax);
    int fieldX = MOF_CLIPING(static_cast<int>(temp), 0, StageBlockXMax - 1);

    temp = (pos.y - offset.y) / (m_spPanel->GetRect(UIPanel_PuzzleArea).GetHeight() / StageBlockYMax);
    int fieldY = MOF_CLIPING(static_cast<int>(temp), 0, StageBlockYMax - 1);

    // �t�B�[���h�G���A�ɒ��ׂ���W�l���������Ă��Ȃ��ꍇ�A�s�����W�l��Ԃ��B
    if (!m_spPanel->GetRect(UIPanel_PuzzleArea).CollisionPoint(pos))
    {
        if (out)
        {
            *out = Vector2(fieldX, fieldY);
        }
        return InvalidPos;
    }

    return Vector2(fieldX, fieldY);
}

Vector2 CPuzzle::ToScreenPos(const Vector2 & pos)
{
    Vector2 offset = m_spPanel->GetRect(UIPanel_PuzzleArea).GetTopLeft();
    int screenX = pos.x * (m_spPanel->GetRect(UIPanel_PuzzleArea).GetWidth()  / StageBlockXMax);
    int screenY = pos.y * (m_spPanel->GetRect(UIPanel_PuzzleArea).GetHeight() / StageBlockYMax);
    return Vector2(screenX, screenY) + offset;
}

void CPuzzle::FieldUpdate(void)
{
    std::vector<std::vector<Vector2>> delPosArray;
    std::vector<std::vector<Vector2>> delPosArray2;
    bool bLine  = (LineCheck(delPosArray));
    bool bClumn = (ColumnCheck(delPosArray2));

    if(bLine)
    {
        for (const auto& it : delPosArray)
        {
            for (const auto& it2 : it)
            {
                m_Blocks[(int)it2.y][(int)it2.x].Delete();
            }
        }
    }

    if (bClumn)
    {
        for (const auto& it : delPosArray2)
        {
            for (const auto& it2 : it)
            {
                m_Blocks[(int)it2.y][(int)it2.x].Delete();
            }
        }
    }

    for (int y = 0; y < StageBlockYMax; y++)
    {
        for (int x = 0; x < StageBlockXMax; x++)
        {
            m_Blocks[y][x].Update();
        }
    }
}

bool CPuzzle::LineCheck(std::vector<std::vector<Vector2>>& outPosArray)
{
    // ���̃`�F�b�N
    using PII = std::pair<int, int>;
    std::array<std::vector<PII>, StageBlockYMax> runlength;

    // ������E�܂ő��点��B
    for (int y = 0; y < StageBlockYMax; y++)
    {
        runlength[y].push_back(PII(m_Blocks[y][0].GetType(), 1));
        for (int x = 1; x < StageBlockXMax; x++)
        {
            if (m_Blocks[y][x].GetType() != m_Blocks[y][x - 1].GetType())
            {
                runlength[y].push_back(PII(m_Blocks[y][x].GetType(), 1));
            }
            else
            {
                ((runlength[y])[runlength[y].size() - 1]).second++;
            }
        }
    }
    for (int y = 0; y < StageBlockYMax; y++)
    {
        int offset = 0;
        for (int x = 0; x < runlength[y].size(); x++)
        {
            // 3�}�b�`�ȏサ�Ă��邩
            int mutch = (runlength[y])[x].second;
            if ((runlength[y])[x].first != BlockType_None && mutch >= 3)
            {
                outPosArray.push_back(std::vector<Vector2>());
                for (int z = 0; z < mutch; z++)
                {
                    outPosArray[outPosArray.size() - 1].push_back(Vector2(offset + z, y));
                }
            }
            offset += mutch;
        }
    }

    return (outPosArray.size() > 0);
}

bool CPuzzle::ColumnCheck(std::vector<std::vector<Vector2>>& outPosArray)
{
    // �c�̃`�F�b�N
    using PII = std::pair<int, int>;
    std::array<std::vector<PII>, StageBlockXMax> runlength;

    // �ォ�牺�܂ő��点��B
    for (int x = 0; x < StageBlockXMax; x++)
    {
        runlength[x].push_back(PII(m_Blocks[0][x].GetType(), 1));
        for (int y = 1; y < StageBlockYMax; y++)
        {
            if (m_Blocks[y][x].GetType() != m_Blocks[y - 1][x].GetType())
            {
                runlength[x].push_back(PII(m_Blocks[y][x].GetType(),1));
            }
            else
            {
                ((runlength[x])[runlength[x].size() - 1]).second++;
            }
        }
    }
    for (int x = 0; x < StageBlockXMax; x++)
    {
        int offset = 0;
        for (int y = 0; y < runlength[x].size(); y++)
        {
            // 3�}�b�`�ȏサ�Ă��邩
            int mutch = (runlength[x])[y].second;
            if ((runlength[x])[y].first != BlockType_None && mutch >= 3)
            {
                outPosArray.push_back(std::vector<Vector2>());
                for (int z = 0; z < mutch; z++)
                {
                    outPosArray[outPosArray.size() - 1].push_back(Vector2(x, offset + z));
                }
            }
            offset += mutch;
        }
    }

    return (outPosArray.size() > 0);
}

void CPuzzle::Move(void)
{
}

void CPuzzle::Delete(void)
{
}

void CPuzzle::Drop(void)
{
}
