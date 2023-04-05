#pragma once
#include "IDisplaySystem.h"
#include "ISystemLifeCycle.h"
#include <memory>
class ISystem {
protected:
	std::shared_ptr<IDisplaySystem> m_displaySystem;
	std::shared_ptr<ISystemLifeCycle> m_lifeCycleSystem;
public:
	virtual std::shared_ptr<IDisplaySystem> GetDisplaySystem() = 0;
	virtual std::shared_ptr<ISystemLifeCycle> GetSystemLifeCycle() = 0;

};