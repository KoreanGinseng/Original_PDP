#include "Load.h"

CLoad::CLoad(const CLoad::InitData & init) :
	CLoadBase(init)
{
	// ����������
}

CLoad::~CLoad(void)
{
	// �������

}

void CLoad::Update(void)
{
	// �ǂݍ��ݒ��̍X�V�����B


	// �X���b�h�ł̓ǂݍ��ݐ���B
	CLoadBase::Update();
}

void CLoad::Render(void)
{
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	CGraphicsUtilities::RenderString(0, 0, "Loading");
}
