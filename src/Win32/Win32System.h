#pragma once
#include "ISystem.h"
class Win32System: public ISystem
{
public:
	Win32System();
	// Inherited via ISystem
	virtual std::shared_ptr<IDisplaySystem> GetDisplaySystem() override;
	virtual std::shared_ptr<ISystemLifeCycle> GetSystemLifeCycle() override;
};
