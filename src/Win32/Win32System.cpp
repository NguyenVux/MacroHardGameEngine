#include "Win32System.h"
#include "DisplaySystem.h"
#include "../SystemLifeCycle.h"
Win32System::Win32System()
{
	m_displaySystem = std::make_shared<DisplaySystem>();
	m_lifeCycleSystem = std::make_shared<SystemLifeCycle>();
}
std::shared_ptr<IDisplaySystem> Win32System::GetDisplaySystem()
{
	return m_displaySystem;
}

std::shared_ptr<ISystemLifeCycle> Win32System::GetSystemLifeCycle()
{
	return m_lifeCycleSystem;
}
