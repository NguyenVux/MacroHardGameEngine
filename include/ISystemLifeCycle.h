#pragma once
#include "signal.h"


class ISystemLifeCycle {
protected:
	struct AccessKey;
public:
	MHTL::public_signal_t<void(float delta_t), AccessKey> sig_onUpdate;
	virtual void Update(float delta) = 0;
};