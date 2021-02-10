#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// スクリーン関係汎用クラス
/// </summary>
// ********************************************************************************
class CScreenUtilities
{
private:

    int     m_MonitorX{ 0 };
    int     m_MonitorY{ 0 };

    Vector2 m_Aspect  { 0, 0 };

    CScreenUtilities(void) = default;

public:

    ~CScreenUtilities(void) = default;

    // ********************************************************************************
    /// <summary>
    /// インスタンスの取得
    /// </summary>
    /// <returns>インスタンス</returns>
    /// <created>いのうえ,2021/01/24</created>
    /// <changed>いのうえ,2021/01/24</changed>
    // ********************************************************************************
    static CScreenUtilities& GetInstance(void);

    // ********************************************************************************
    /// <summary>
    /// モニター解像度の設定
    /// </summary>
    /// <param name="w">横幅</param>
    /// <param name="h">縦幅</param>
    /// <created>いのうえ,2021/01/24</created>
    /// <changed>いのうえ,2021/01/24</changed>
    // ********************************************************************************
    void SetMonitorSize(int w, int h);

    // ********************************************************************************
    /// <summary>
    /// モニターの幅取得
    /// </summary>
    /// <returns>幅</returns>
    /// <created>いのうえ,2021/01/24</created>
    /// <changed>いのうえ,2021/01/24</changed>
    // ********************************************************************************
    int GetMonitorWidth(void);

    // ********************************************************************************
    /// <summary>
    /// モニターの高さ取得
    /// </summary>
    /// <returns>モニターの高さ</returns>
    /// <created>いのうえ,2021/01/24</created>
    /// <changed>いのうえ,2021/01/24</changed>
    // ********************************************************************************
    int GetMonitorHeight(void);

private:

    // ********************************************************************************
    /// <summary>
    /// 最大公約数を求める関数
    /// </summary>
    /// <param name="n">値１</param>
    /// <param name="m">値２</param>
    /// <returns>最大公約数</returns>
    /// <created>いのうえ,2021/01/24</created>
    /// <changed>いのうえ,2021/01/24</changed>
    // ********************************************************************************
    int GCD(int n, int m);
};

#define g_ScreenUtilities CScreenUtilities::GetInstance()