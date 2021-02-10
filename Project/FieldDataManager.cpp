#include "FieldDataManager.h"

bool CFieldDataManager::Load(void)
{
    // TODO : 今全部読んでるけど、将来的にはflyweightパターンありだよ。

    CReadCSV readcsv;

    std::string file_easy[] =
    {
        "field_0.csv",
    };

    for (const auto& it : file_easy)
    {
        if (!readcsv.Load(it.c_str()))
        {
            return false;
        }
        m_EasyFieldDataArray.push_back(ToFieldData(readcsv.GetCSVData()));
        readcsv.Release();
    }

    std::string file_normal[] =
    {
        "field_1.csv",
    };

    for (const auto& it : file_normal)
    {
        if (!readcsv.Load(it.c_str()))
        {
            return false;
        }
        m_NormalFieldDataArray.push_back(ToFieldData(readcsv.GetCSVData()));
        readcsv.Release();
    }
    std::string file_hard[] =
    {
        "field_2.csv",
    };

    for (const auto& it : file_hard)
    {
        if (!readcsv.Load(it.c_str()))
        {
            return false;
        }
        m_HardFieldDataArray.push_back(ToFieldData(readcsv.GetCSVData()));
        readcsv.Release();
    }

    return true;
}

std::vector<FieldData>& CFieldDataManager::GetFieldDataArray(GameDifficulty diff)
{
    switch (diff)
    {
    case GameDifficulty::Easy:
        return m_EasyFieldDataArray;
    case GameDifficulty::Normal:
        return m_NormalFieldDataArray;
    case GameDifficulty::Hard:
        return m_HardFieldDataArray;
    default:
        throw;
    }
}

FieldData & CFieldDataManager::GetFieldData(GameDifficulty diff, int n)
{
    return GetFieldDataArray(diff)[n];
}

int CFieldDataManager::GetFieldDataCount(void)
{
    return m_EasyFieldDataArray.size();
}

CFieldDataManager & CFieldDataManager::GetInsctance(void)
{
    static CFieldDataManager instance;
    return instance;
}

FieldData CFieldDataManager::ToFieldData(const CReadCSV::CSVData & data)
{
    FieldData fieldData;

    for (int i = 0; i < StageBlockYMax; i++)
    {
        for (int j = 0; j < StageBlockXMax; j++)
        {
            fieldData[i][j] = static_cast<BlockType>(std::atoi(data[i][j].c_str()));
        }
    }

    return fieldData;
}
