#pragma once
#include "IDisplaySystem.h"
class DisplaySystem: public IDisplaySystem
{
	// Inherited via IDisplaySystem
	virtual CreateDisplayResult CreateDisplay(GraphicAPI i_api) override;
};
