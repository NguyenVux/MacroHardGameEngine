#pragma once
#include "Win32Display.h"



enum class LoadGLErrorCode {
	OpenGLNotSupported
};

using LoadGLError = MHTL::error<LoadGLErrorCode>;
using LoadGLResult = MHTL::result<void,LoadGLError>;
class OpenGLWin32Display : public Win32Display {
private:
	HGLRC m_renderingContenxt;
	LoadGLResult LoadGL();
public:
	OpenGLWin32Display(std::string i_className);
	virtual ~OpenGLWin32Display();
	DisplayInitResult Init(std::string i_title, uint32_t width, uint32_t height) override;
	void Present() override;
};