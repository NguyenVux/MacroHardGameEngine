#pragma once
#include "IDisplay.h"
#include <memory>

enum class CreateDisplayErrorCode {
	CannotCreateDisplay
};

using CreateDisplayError = MHTL::error<CreateDisplayErrorCode>;
using CreateDisplayResult = MHTL::result<std::unique_ptr<IDisplay>, CreateDisplayError>;

class IDisplaySystem {
private:
	//struct AccessKey;
public:
	enum class GraphicAPI {
		OPENGL
	};

	virtual CreateDisplayResult CreateDisplay(GraphicAPI i_api) = 0;
};