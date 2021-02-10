#include "ReadCSV.h"
#include "ReadCSV.h"

// ********************************************************************************
/// <summary>
/// CSVファイル読み込み
/// </summary>
/// <param name="pFile">ファイル名</param>
/// <returns>true : 成功, false : 失敗</returns>
/// <created>いのうえ,2021/01/31</created>
/// <changed>いのうえ,2021/01/31</changed>
// ********************************************************************************
bool CReadCSV::Load(LPCMofChar pFile)
{
    // ファイルの読み込み
    std::ifstream istream(pFile);

    // 読み込み失敗
    if (!istream)
    {
        return false;
    }
    
    const int max_buff = 1024;
    char pstr[max_buff];

    int i = 0;
    m_Data.resize(1);
    istream.seekg(3, std::ios_base::beg);
    while (istream.getline(pstr, max_buff, ','))
    {
        std::string str(pstr);

        size_t find_len = str.find('\n');
        if (find_len != std::string::npos)
        {
            m_Data[i++].push_back(str.substr(0, find_len));
            m_Data.push_back(std::vector<std::string>());
            m_Data[i].push_back(str.substr(find_len + 1, str.length()));
            continue;
        }
        m_Data[i].push_back(pstr);
    }

    for (int j = 0; j < m_Data.size(); j++)
    {
        for (auto& it : m_Data[j])
        {
            MOF_PRINTLOG("%s,", it.c_str());
        }
        MOF_PRINTLOG("\n");
    }

    return true;
}

// ********************************************************************************
/// <summary>
/// データの解放
/// </summary>
/// <created>いのうえ,2021/01/31</created>
/// <changed>いのうえ,2021/01/31</changed>
// ********************************************************************************
void CReadCSV::Release(void)
{
    for (int i = 0; i < m_Data.size(); i++)
    {
        m_Data[i].clear();
    }
    m_Data.clear();
}

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
CReadCSV::Data & CReadCSV::GetData(int line, int column)
{
    return (m_Data[line])[column];
}

CReadCSV::Data CReadCSV::GetData(int line, int column) const
{
    return (m_Data[line])[column];
}

// ********************************************************************************
/// <summary>
/// データの取得
/// </summary>
/// <param name="line">行</param>
/// <returns>行データ</returns>
/// <created>いのうえ,2021/01/31</created>
/// <changed>いのうえ,2021/01/31</changed>
// ********************************************************************************
CReadCSV::LineData & CReadCSV::GetLine(int line)
{
    return (m_Data[line]);
}

CReadCSV::LineData CReadCSV::GetLine(int line) const
{
    return (m_Data[line]);
}

// ********************************************************************************
/// <summary>
/// データの取得
/// </summary>
/// <returns>CSVデータ</returns>
/// <created>いのうえ,2021/01/31</created>
/// <changed>いのうえ,2021/01/31</changed>
// ********************************************************************************
CReadCSV::CSVData & CReadCSV::GetCSVData(void)
{
    return m_Data;
}

CReadCSV::CSVData CReadCSV::GetCSVData(void) const
{
    return m_Data;
}
