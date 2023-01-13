#include "OpenGLDisplayWin32.h"


bool OpenGLWin32Display::Init(std::string i_title, uint32_t width, uint32_t height) {
	bool baseResult = Win32Display::Init(i_title, width, height);
	if (!baseResult)
	{
		return false;
	}

	m_renderingContenxt = wglCreateContext(m_DC);
	if (m_renderingContenxt == nullptr)
	{
		return false;
	}
	wglMakeCurrent(m_DC,m_renderingContenxt);

}