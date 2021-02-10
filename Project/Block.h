#pragma once
#include "Common.h"

//! ブロックの色
constexpr MofU32 BlockColor[] = 
{
    MOF_XRGB(255,   0,   0),
    MOF_XRGB(  0, 255,   0),
    MOF_XRGB( 64,  64, 255),
    MOF_XRGB(255, 255,   0),
    MOF_XRGB(255,   0, 255),
    MOF_XRGB(  0,   0, 128),
};

// ********************************************************************************
/// <summary>
/// ブロッククラス
/// </summary>
// ********************************************************************************
class CBlock
{
private:

    // ********************************************************************************
    /// <summary>
    /// ブロックの状態
    /// </summary>
    // ********************************************************************************
    enum class State
    {
        None,        //! 常
        
        Wait,        //! 落ちる待機
        Swap,        //! 入れ替えなう
        FallDown,    //! 落ちてるなう
        Delete,      //! 消えてるなう
        Ghost,       //! 消えた後の存在

    } m_PrevState, m_State;

    CRectangle                m_Rect;

    BlockType                 m_Type;

    CSpriteMotionController   m_BombMotion;

    std::shared_ptr<CTexture> m_pBombTexture;

    bool                      m_bBomb{ false };

public:

    CBlock(void);

    CBlock(const CBlock& obj);

    CBlock(CBlock&& obj) noexcept;
    
    CBlock(const Vector2& pos, const Vector2& size, BlockType type);

    virtual ~CBlock(void);

    void Initialize(const Vector2& pos, const Vector2& size, BlockType type);

    void Update(void);

    void Render(void);

    static void Render(const CRectangle& rect, BlockType type);

    void SetPos(const Vector2& pos);

    void SetSize(const Vector2& size);

    void SetType(BlockType type);

    bool IsDelete(void) const;

    BlockType GetType(void) const;

    CRectangle GetRect(void) const;

    void Delete(void);

    void operator= (const CBlock& obj);
};

