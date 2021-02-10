#pragma once
#include "Block.h"
#include "Common.h"
#include "ReadCSV.h"

// ********************************************************************************
/// <summary>
/// フィールドデータの管理クラス
/// </summary>
// ********************************************************************************
class CFieldDataManager
{
private:

    std::vector<FieldData> m_EasyFieldDataArray;
    std::vector<FieldData> m_NormalFieldDataArray;
    std::vector<FieldData> m_HardFieldDataArray;

public:

    bool Load(void);

    std::vector<FieldData>& GetFieldDataArray(GameDifficulty diff);

    FieldData& GetFieldData(GameDifficulty diff, int n);

    int GetFieldDataCount(void);

    static CFieldDataManager& GetInsctance(void);

private:

    explicit CFieldDataManager(void) = default;

    FieldData ToFieldData(const CReadCSV::CSVData& data);
};

#define g_FieldDataManager CFieldDataManager::GetInsctance()