#include "ReadCSV.h"
#include "ReadCSV.h"

// ********************************************************************************
/// <summary>
/// CSV�t�@�C���ǂݍ���
/// </summary>
/// <param name="pFile">�t�@�C����</param>
/// <returns>true : ����, false : ���s</returns>
/// <created>���̂���,2021/01/31</created>
/// <changed>���̂���,2021/01/31</changed>
// ********************************************************************************
bool CReadCSV::Load(LPCMofChar pFile)
{
    // �t�@�C���̓ǂݍ���
    std::ifstream istream(pFile);

    // �ǂݍ��ݎ��s
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
/// �f�[�^�̉��
/// </summary>
/// <created>���̂���,2021/01/31</created>
/// <changed>���̂���,2021/01/31</changed>
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
/// �f�[�^�̎擾
/// </summary>
/// <param name="line">�s</param>
/// <param name="column">��</param>
/// <returns>�f�[�^</returns>
/// <created>���̂���,2021/01/31</created>
/// <changed>���̂���,2021/01/31</changed>
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
/// �f�[�^�̎擾
/// </summary>
/// <param name="line">�s</param>
/// <returns>�s�f�[�^</returns>
/// <created>���̂���,2021/01/31</created>
/// <changed>���̂���,2021/01/31</changed>
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
/// �f�[�^�̎擾
/// </summary>
/// <returns>CSV�f�[�^</returns>
/// <created>���̂���,2021/01/31</created>
/// <changed>���̂���,2021/01/31</changed>
// ********************************************************************************
CReadCSV::CSVData & CReadCSV::GetCSVData(void)
{
    return m_Data;
}

CReadCSV::CSVData CReadCSV::GetCSVData(void) const
{
    return m_Data;
}
