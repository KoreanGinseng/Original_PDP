#include "ScreenUtilites.h"

// ********************************************************************************
/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�C���X�^���X</returns>
/// <created>���̂���,2021/01/24</created>
/// <changed>���̂���,2021/01/24</changed>
// ********************************************************************************
CScreenUtilities & CScreenUtilities::GetInstance(void)
{
    static CScreenUtilities instance;
    return instance;
}

// ********************************************************************************
/// <summary>
/// ���j�^�[�𑜓x�̐ݒ�
/// </summary>
/// <param name="w">����</param>
/// <param name="h">�c��</param>
/// <created>���̂���,2021/01/24</created>
/// <changed>���̂���,2021/01/24</changed>
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
/// ���j�^�[�̕��擾
/// </summary>
/// <returns>��</returns>
/// <created>���̂���,2021/01/24</created>
/// <changed>���̂���,2021/01/24</changed>
// ********************************************************************************
int CScreenUtilities::GetMonitorWidth(void)
{
    return m_MonitorX;
}

// ********************************************************************************
/// <summary>
/// ���j�^�[�̍����擾
/// </summary>
/// <returns>���j�^�[�̍���</returns>
/// <created>���̂���,2021/01/24</created>
/// <changed>���̂���,2021/01/24</changed>
// ********************************************************************************
int CScreenUtilities::GetMonitorHeight(void)
{
    return m_MonitorY;
}

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
int CScreenUtilities::GCD(int n, int m)
{
    if (m == 0) return n;
    return GCD(n, n % m);
}
