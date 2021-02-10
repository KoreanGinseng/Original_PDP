#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// CSV読み込みクラス
/// </summary>
// ********************************************************************************
class CReadCSV
{
public:

    using Data       = std::string;
    using LineData   = std::vector<Data>;
    using CSVData    = std::vector<LineData>;

protected:

    CSVData m_Data;

public:

    // ********************************************************************************
    /// <summary>
    /// CSVファイル読み込み
    /// </summary>
    /// <param name="pFile">ファイル名</param>
    /// <returns>true : 成功, false : 失敗</returns>
    /// <created>いのうえ,2021/01/31</created>
    /// <changed>いのうえ,2021/01/31</changed>
    // ********************************************************************************
    bool Load(LPCMofChar pFile);

    // ********************************************************************************
    /// <summary>
    /// データの解放
    /// </summary>
    /// <created>いのうえ,2021/01/31</created>
    /// <changed>いのうえ,2021/01/31</changed>
    // ********************************************************************************
    void Release(void);

    // ********************************************************************************
    /// <summary>
    /// データの取得
    /// </summary>
    /// <param name="line">行</param>
    /// <param name="column">列</param>
    /// <returns>データ</returns>
    /// <created>いのうえ,2021/01/31</created>
    /// <changed>いのうえ,2021/01/31</changed>
    // ********************************************************************************
    Data& GetData(int line, int column);
    Data GetData(int line, int column) const;

    // ********************************************************************************
    /// <summary>
    /// データの取得
    /// </summary>
    /// <param name="line">行</param>
    /// <returns>行データ</returns>
    /// <created>いのうえ,2021/01/31</created>
    /// <changed>いのうえ,2021/01/31</changed>
    // ********************************************************************************
    LineData& GetLine(int line);
    LineData GetLine(int line) const;
    
    // ********************************************************************************
    /// <summary>
    /// データの取得
    /// </summary>
    /// <returns>CSVデータ</returns>
    /// <created>いのうえ,2021/01/31</created>
    /// <changed>いのうえ,2021/01/31</changed>
    // ********************************************************************************
    CSVData& GetCSVData(void);
    CSVData GetCSVData(void) const;
};

