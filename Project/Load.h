#pragma once
#include "sip/LoadBase.h"

class CLoad : public CLoadBase
{
public:

	CLoad(const CLoad::InitData& init);

	virtual ~CLoad(void);

	virtual void Update(void) override;

	virtual void Render(void) override;
};

