#pragma once
#include "ISystemLifeCycle.h"

class SystemLifeCycle : public ISystemLifeCycle
{
	void Update(float delta) override;
};
