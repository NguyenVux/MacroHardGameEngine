#pragma once
#include "Win32Display.h"

class OpenGLWin32Display : public Win32Display {
private:
	HGLRC m_renderingContenxt;

	void LoadGL();
public:
	OpenGLWin32Display(std::string i_className);
	bool Init(std::string i_title, uint32_t width, uint32_t height) override;
};