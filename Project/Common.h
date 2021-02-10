#pragma once
#include "MofSip.h"

// GLOBAL
extern bool g_bDebug;

// DEFINE
constexpr unsigned int StageBlockYMax = 12;
constexpr unsigned int StageBlockXMax =  6;

// ********************************************************************************
/// <summary>
/// ゲーム難易度列挙
/// </summary>
// ********************************************************************************
enum class GameDifficulty
{
    Easy,
    Normal,
    Hard,
};

// ********************************************************************************
/// <summary>
/// ブロックの種類
/// </summary>
// ********************************************************************************
enum BlockType
{
    BlockType_None = -1,
    BlockType_1,
    BlockType_2,
    BlockType_3,
    BlockType_4,
    BlockType_5,
    BlockType_6,

    BlockType_Count,
};

// ********************************************************************************
/// <summary>
/// フィールドデータ
/// </summary>
// ********************************************************************************
struct FieldData
{
    BlockType m_Field[StageBlockYMax][StageBlockXMax];

    BlockType* operator[](int n) noexcept { return m_Field[n]; }
    const BlockType* operator[](int n) const noexcept { return m_Field[n]; }

    BlockType& operator()(int y, int x) noexcept { return m_Field[y][x]; }
    const BlockType& operator()(int y, int x) const noexcept { return m_Field[y][x]; }
};

// シーンのキー
enum class SceneName
{
	Title,

	Game,

	Load,

};

// 各シーン共通のデータ
struct GameData
{
    GameDifficulty p1_difficulty{ GameDifficulty::Normal };
    GameDifficulty p2_difficulty{ GameDifficulty::Normal };
};

using MyApp = CSceneManager<SceneName, GameData>;

// サウンドアセット用キー
enum class SoundKey
{

};

// テクスチャアセット用キー
enum class TextureKey
{
    EFC_Bomb,
};

// メッシュアセット用キー
enum class MeshKey
{

};

// メッシュアセット用キー
enum class FontKey
{

};

// アニメーションアセット用キー
enum class AnimKey
{
    EFC_Bomb,
};

// エフェクトアセット用キー
enum class EffectKey
{

};

// アセットの置き換え( bool Load() 関数 と Release() 関数が実装されていれば利用可能)
using CSoundAsset   = CAssetBase<SoundKey  , CSoundBuffer  >;
using CTextureAsset = CAssetBase<TextureKey, CTexture      >;
using CMeshAsset    = CAssetBase<MeshKey   , CMeshContainer>;
using CFontAsset    = CAssetBase<FontKey   , CFontA        >;
using CAnimAsset    = CAssetBase<AnimKey   , CAnimationData>;
using CEffectAsset  = CAssetBase<EffectKey , CEffectBase   >;

#define SoundAsset(key)   CSoundAsset  ::GetAsset(key)
#define TextureAsset(key) CTextureAsset::GetAsset(key)
#define MeshAsset(key)    CMeshAsset   ::GetAsset(key)
#define FontAsset(key)    CFontAsset   ::GetAsset(key)
#define AnimAsset(key)    CAnimAsset   ::GetAsset(key)
#define EffectAsset(key)  CEffectAsset ::GetAsset(key)