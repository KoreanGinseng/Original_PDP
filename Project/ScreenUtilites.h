#pragma once
#include "Mof.h"

// ********************************************************************************
/// <summary>
/// �X�N���[���֌W�ėp�N���X
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
    /// �C���X�^���X�̎擾
    /// </summary>
    /// <returns>�C���X�^���X</returns>
    /// <created>���̂���,2021/01/24</created>
    /// <changed>���̂���,2021/01/24</changed>
    // ********************************************************************************
    static CScreenUtilities& GetInstance(void);

    // ********************************************************************************
    /// <summary>
    /// ���j�^�[�𑜓x�̐ݒ�
    /// </summary>
    /// <param name="w">����</param>
    /// <param name="h">�c��</param>
    /// <created>���̂���,2021/01/24</created>
    /// <changed>���̂���,2021/01/24</changed>
    // ********************************************************************************
    void SetMonitorSize(int w, int h);

    // ********************************************************************************
    /// <summary>
    /// ���j�^�[�̕��擾
    /// </summary>
    /// <returns>��</returns>
    /// <created>���̂���,2021/01/24</created>
    /// <changed>���̂���,2021/01/24</changed>
    // ********************************************************************************
    int GetMonitorWidth(void);

    // ********************************************************************************
    /// <summary>
    /// ���j�^�[�̍����擾
    /// </summary>
    /// <returns>���j�^�[�̍���</returns>
    /// <created>���̂���,2021/01/24</created>
    /// <changed>���̂���,2021/01/24</changed>
    // ********************************************************************************
    int GetMonitorHeight(void);

private:

    // ********************************************************************************
    /// <summary>
    /// �ő���񐔂����߂�֐�
    /// </summary>
    /// <param name="n">�l�P</param>
    /// <param name="m">�l�Q</param>
    /// <returns>�ő����</returns>
    /// <created>���̂���,2021/01/24</created>
    /// <changed>���̂���,2021/01/24</changed>
    // ********************************************************************************
    int GCD(int n, int m);
};

#define g_ScreenUtilities CScreenUtilities::GetInstance()