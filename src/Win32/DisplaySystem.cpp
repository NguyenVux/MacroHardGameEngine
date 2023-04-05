#include "DisplaySystem.h"
#include "OpenGLDisplayWin32.h"
CreateDisplayResult DisplaySystem::CreateDisplay(GraphicAPI i_api)
{
	if (i_api == GraphicAPI::OPENGL)
	{
		CreateDisplayResult result(std::move(std::make_unique<OpenGLWin32Display>("main")));
		return result;
	}
}
