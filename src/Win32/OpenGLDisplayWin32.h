#pragma once
#include "Win32Display.h"


class OpenGLWin32Display : Win32Display {
private:
	HGLRC m_renderingContenxt;
public:
	bool Init(std::string i_title, uint32_t width, uint32_t height) override;
};