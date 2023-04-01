#pragma once
#include <string>
#include "result.h"


enum class DisplayInitErrorCode {
	CannotInitDisplay
};

using DisplayInitError = MHTL::error<DisplayInitErrorCode>;
using DisplayInitResult = MHTL::result<void,DisplayInitError>;


class IDisplay {
public:
	virtual void Show() = 0;
	virtual void Present() = 0;
	virtual DisplayInitResult Init(std::string i_title, uint32_t width, uint32_t height) = 0;
};