#pragma once
#include "MofSip.h"

// GLOBAL
extern bool g_bDebug;

// DEFINE
constexpr unsigned int StageBlockYMax = 12;
constexpr unsigned int StageBlockXMax =  6;

// ********************************************************************************
/// <summary>
/// �Q�[����Փx��
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
/// �u���b�N�̎��
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
/// �t�B�[���h�f�[�^
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

// �V�[���̃L�[
enum class SceneName
{
	Title,

	Game,

	Load,

};

// �e�V�[�����ʂ̃f�[�^
struct GameData
{
    GameDifficulty p1_difficulty{ GameDifficulty::Normal };
    GameDifficulty p2_difficulty{ GameDifficulty::Normal };
};

using MyApp = CSceneManager<SceneName, GameData>;

// �T�E���h�A�Z�b�g�p�L�[
enum class SoundKey
{

};

// �e�N�X�`���A�Z�b�g�p�L�[
enum class TextureKey
{
    EFC_Bomb,
};

// ���b�V���A�Z�b�g�p�L�[
enum class MeshKey
{

};

// ���b�V���A�Z�b�g�p�L�[
enum class FontKey
{

};

// �A�j���[�V�����A�Z�b�g�p�L�[
enum class AnimKey
{
    EFC_Bomb,
};

// �G�t�F�N�g�A�Z�b�g�p�L�[
enum class EffectKey
{

};

// �A�Z�b�g�̒u������( bool Load() �֐� �� Release() �֐�����������Ă���Η��p�\)
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