#include "SystemLifeCycle.h"

void SystemLifeCycle::Update(float delta)
{
	MHTL::access<AccessKey>(sig_onUpdate).emit(delta);
}
