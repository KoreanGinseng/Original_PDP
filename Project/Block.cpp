#include "Block.h"

CBlock::CBlock(void)
{
    Initialize(Vector2(0, 0), Vector2(0, 0), BlockType_None);
}

CBlock::CBlock(const CBlock & obj)
{
    m_Rect = obj.m_Rect;
    m_Type = obj.m_Type;
}

CBlock::CBlock(CBlock && obj) noexcept
{
    m_Rect = m_Rect;
    m_Type = obj.m_Type;
}


CBlock::CBlock(const Vector2 & pos, const Vector2& size, BlockType type)
{
    Initialize(pos, size, type);
}

CBlock::~CBlock(void)
{
}

void CBlock::Initialize(const Vector2 & pos, const Vector2& size, BlockType type)
{
    SetPos(pos);
    SetSize(size);
    SetType(type);

    std::shared_ptr<CAnimationData> pAnimData = CAnimAsset::GetAsset(AnimKey::EFC_Bomb);
    SpriteAnimationCreate* pAnim = pAnimData->GetAnim();
    m_BombMotion.Create(pAnim, pAnimData->GetAnimationCount());
    m_pBombTexture = CTextureAsset::GetAsset(TextureKey::EFC_Bomb);
}

void CBlock::Update(void)
{
    if (m_bBomb)
    {
        m_BombMotion.AddTimer(CUtilities::GetFrameSecond());
    }

    if (m_State != m_PrevState)
    {

    }

    if (m_State == State::Delete && m_BombMotion.IsEndMotion())
    {
        m_State = State::Ghost;
    }

    m_PrevState = m_State;
}

void CBlock::Render(void)
{
    if (m_Type == BlockType_None || m_State == State::Ghost)
    {
        return;
    }

    CRectangle inRect{ m_Rect };
    float ratio = 0.05f;
    inRect.Expansion(m_Rect.GetWidth() * -ratio, m_Rect.GetHeight() * -ratio);

    std::function<MofU32(MofU32, MofU32)> addColorFunc = [](MofU32 base, MofU32 add)
    {
        MofS32 base_r = (MOF_RED_KEY   & base) >> 16;
        MofS32 base_g = (MOF_GREEN_KEY & base) >> 8;
        MofS32 base_b = (MOF_BLUE_KEY  & base) >> 0;

        MofS32 add_r = (MOF_RED_KEY   & add) >> 16;
        MofS32 add_g = (MOF_GREEN_KEY & add) >> 8;
        MofS32 add_b = (MOF_BLUE_KEY  & add) >> 0;

        MofS32 r = MOF_MIN(255, base_r + add_r);
        MofS32 g = MOF_MIN(255, base_g + add_g);
        MofS32 b = MOF_MIN(255, base_b + add_b);

        return MOF_XRGB(r, g, b);
    };
    std::function<MofU32(MofU32, MofU32)> subColorFunc = [](MofU32 base, MofU32 sub)
    {
        MofS32 base_r = (MOF_RED_KEY   & base) >> 16;
        MofS32 base_g = (MOF_GREEN_KEY & base) >> 8;
        MofS32 base_b = (MOF_BLUE_KEY  & base) >> 0;

        MofS32 sub_r = (MOF_RED_KEY   & sub) >> 16;
        MofS32 sub_g = (MOF_GREEN_KEY & sub) >> 8;
        MofS32 sub_b = (MOF_BLUE_KEY  & sub) >> 0;

        MofS32 r = MOF_MAX(255, base_r - sub_r);
        MofS32 g = MOF_MAX(255, base_g - sub_g);
        MofS32 b = MOF_MAX(255, base_b - sub_b);

        return MOF_XRGB(r, g, b);
    };

    MofU32 baseColor  = BlockColor[(int)m_Type];
    MofU32 darkColor  = subColorFunc(baseColor, MOF_COLOR_HWHITE);
    MofU32 lightColor = addColorFunc(baseColor, MOF_COLOR_HWHITE);

    // 中央
    CGraphicsUtilities::RenderFillRect(m_Rect, MOF_COLOR_CWHITE);
    CGraphicsUtilities::RenderFillRect(inRect, baseColor);

    {
        //// 左
        //CGraphicsUtilities::RenderFillQuad(
        //    m_Rect.GetTopLeft(), m_Rect.GetBottomLeft(), inRect.GetTopLeft(), inRect.GetBottomLeft(),
        //    lightColor, lightColor, lightColor, lightColor
        //);

        //// 上
        //CGraphicsUtilities::RenderFillQuad(
        //    m_Rect.GetTopLeft(), inRect.GetTopLeft(), m_Rect.GetTopRight(), inRect.GetTopRight(),
        //    lightColor, lightColor, lightColor, lightColor
        //);

        //// 右
        //CGraphicsUtilities::RenderFillQuad(
        //    inRect.GetTopRight(), inRect.GetBottomRight(), m_Rect.GetTopRight(), m_Rect.GetBottomRight(),
        //    darkColor, darkColor, darkColor, darkColor
        //);

        //// 下
        //CGraphicsUtilities::RenderFillQuad(
        //    inRect.GetBottomLeft(), m_Rect.GetBottomLeft(), inRect.GetBottomRight(), m_Rect.GetBottomRight(),
        //    darkColor, darkColor, darkColor, darkColor
        //);
    }

    // 枠線
    CGraphicsUtilities::RenderRect(m_Rect, MOF_COLOR_BLACK);

    // 爆発アニメーションの再生
    if (m_bBomb)
    {
        m_pBombTexture->Render(m_Rect, m_BombMotion.GetSrcRect());
    }
}

void CBlock::Render(const CRectangle & rect, BlockType type)
{
    if (type == BlockType_None)
    {
        return;
    }

    CRectangle inRect{ rect };
    float ratio = 0.05f;
    inRect.Expansion(rect.GetWidth() * -ratio, rect.GetHeight() * -ratio);

   

    MofU32 baseColor = BlockColor[(int)type];

    // 中央
    CGraphicsUtilities::RenderFillRect(rect, MOF_COLOR_CWHITE);
    CGraphicsUtilities::RenderFillRect(inRect, baseColor);

    // 枠線
    CGraphicsUtilities::RenderRect(rect, MOF_COLOR_BLACK);
}

void CBlock::SetPos(const Vector2 & pos)
{
    m_Rect.SetPosition(pos);
}

void CBlock::SetSize(const Vector2 & size)
{
    m_Rect.SetWidth(size.x);
    m_Rect.SetHeight(size.y);
}

void CBlock::SetType(BlockType type)
{
    m_Type = type;
}

bool CBlock::IsDelete(void) const
{
    return m_State == State::Delete || m_State == State::Ghost;
}

BlockType CBlock::GetType(void) const
{
    if (IsDelete())
    {
        return BlockType::BlockType_None;
    }
    return m_Type;
}

CRectangle CBlock::GetRect(void) const
{
    return m_Rect;
}

void CBlock::Delete(void)
{
    m_State = State::Delete;
    m_bBomb = true;
}

void CBlock::operator=(const CBlock & obj)
{
    m_Rect = obj.m_Rect;
    m_Type = obj.m_Type;
}
