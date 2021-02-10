#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// CSV�ǂݍ��݃N���X
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
    /// CSV�t�@�C���ǂݍ���
    /// </summary>
    /// <param name="pFile">�t�@�C����</param>
    /// <returns>true : ����, false : ���s</returns>
    /// <created>���̂���,2021/01/31</created>
    /// <changed>���̂���,2021/01/31</changed>
    // ********************************************************************************
    bool Load(LPCMofChar pFile);

    // ********************************************************************************
    /// <summary>
    /// �f�[�^�̉��
    /// </summary>
    /// <created>���̂���,2021/01/31</created>
    /// <changed>���̂���,2021/01/31</changed>
    // ********************************************************************************
    void Release(void);

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
    Data& GetData(int line, int column);
    Data GetData(int line, int column) const;

    // ********************************************************************************
    /// <summary>
    /// �f�[�^�̎擾
    /// </summary>
    /// <param name="line">�s</param>
    /// <returns>�s�f�[�^</returns>
    /// <created>���̂���,2021/01/31</created>
    /// <changed>���̂���,2021/01/31</changed>
    // ********************************************************************************
    LineData& GetLine(int line);
    LineData GetLine(int line) const;
    
    // ********************************************************************************
    /// <summary>
    /// �f�[�^�̎擾
    /// </summary>
    /// <returns>CSV�f�[�^</returns>
    /// <created>���̂���,2021/01/31</created>
    /// <changed>���̂���,2021/01/31</changed>
    // ********************************************************************************
    CSVData& GetCSVData(void);
    CSVData GetCSVData(void) const;
};

