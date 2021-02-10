#include "ScreenUtilites.h"

// ********************************************************************************
/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns>インスタンス</returns>
/// <created>いのうえ,2021/01/24</created>
/// <changed>いのうえ,2021/01/24</changed>
// ********************************************************************************
CScreenUtilities & CScreenUtilities::GetInstance(void)
{
    static CScreenUtilities instance;
    return instance;
}

// ********************************************************************************
/// <summary>
/// モニター解像度の設定
/// </summary>
/// <param name="w">横幅</param>
/// <param name="h">縦幅</param>
/// <created>いのうえ,2021/01/24</created>
/// <changed>いのうえ,2021/01/24</changed>
// ********************************************************************************
void CScreenUtilities::SetMonitorSize(int w, int h)
{
    m_MonitorX = w;
    m_MonitorY = h;
    const int gcd = GCD(w, h);
    m_Aspect.x = w / gcd;
    m_Aspect.y = h / gcd;
}

// ********************************************************************************
/// <summary>
/// モニターの幅取得
/// </summary>
/// <returns>幅</returns>
/// <created>いのうえ,2021/01/24</created>
/// <changed>いのうえ,2021/01/24</changed>
// ********************************************************************************
int CScreenUtilities::GetMonitorWidth(void)
{
    return m_MonitorX;
}

// ********************************************************************************
/// <summary>
/// モニターの高さ取得
/// </summary>
/// <returns>モニターの高さ</returns>
/// <created>いのうえ,2021/01/24</created>
/// <changed>いのうえ,2021/01/24</changed>
// ********************************************************************************
int CScreenUtilities::GetMonitorHeight(void)
{
    return m_MonitorY;
}

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
int CScreenUtilities::GCD(int n, int m)
{
    if (m == 0) return n;
    return GCD(n, n % m);
}
