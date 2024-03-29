#include "OpenGLDisplayWin32.h"
#include "GL/wglext.h"
#include <gl/GL.h>

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;


std::string GetLastErrorAsString()
{
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string();
	}

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);

	return message;
}


LoadGLResult OpenGLWin32Display::LoadGL()
{
	Win32Display dummyWindow("dummyWindow");
	dummyWindow.Init("title",300,300);
	PIXELFORMATDESCRIPTOR pfd{};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pixelFormatResult = ChoosePixelFormat(dummyWindow.GetDC(), &pfd);
	SetPixelFormat(dummyWindow.GetDC(), pixelFormatResult, &pfd);
	HGLRC dummyContext = wglCreateContext(dummyWindow.GetDC());
	wglMakeCurrent(dummyWindow.GetDC(), dummyContext);

	if(dummyContext == nullptr)
	{
		return (LoadGLError(LoadGLErrorCode::OpenGLNotSupported));
	}

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	wglMakeCurrent(dummyWindow.GetDC(), 0);
	wglDeleteContext(dummyContext);
	return (LoadGLResult());
}

OpenGLWin32Display::OpenGLWin32Display(std::string i_className) : 
	m_renderingContenxt(nullptr),
	Win32Display(i_className)
{

}

DisplayInitResult OpenGLWin32Display::Init(std::string i_title, uint32_t width, uint32_t height) {
	//Load OpenGL to load 2 funtion
	{
		LoadGLResult loadGlResult = LoadGL();
		if(loadGlResult != MHTL::success)
		{
			return DisplayInitError(DisplayInitErrorCode::CannotInitDisplay, loadGlResult.error().what());
		}
	}

	//Init Base win32 display
	{
		DisplayInitResult baseResult = Win32Display::Init(i_title, width, height);
		if (baseResult != MHTL::success)
		{
			return DisplayInitError(DisplayInitErrorCode::CannotInitDisplay, baseResult.error().what());
		}
	}

	int pixelFormatAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
		WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,         32,
		WGL_DEPTH_BITS_ARB,         24,
		WGL_STENCIL_BITS_ARB,       8,
		0
	};
	UINT formatCount;
	int formatArray;
	int pixelFormat = wglChoosePixelFormatARB(m_DC, pixelFormatAttribs, 0, 1, &formatArray, &formatCount);

	PIXELFORMATDESCRIPTOR pfd{};
	DescribePixelFormat(m_DC, formatArray, sizeof(pfd), &pfd);

	// Specify that we want to create an OpenGL 4.6 core profile context
	int gl46_attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};
	SetPixelFormat(m_DC, formatArray, &pfd);
	m_renderingContenxt = wglCreateContextAttribsARB(m_DC, 0, gl46_attribs);
	if (m_renderingContenxt == nullptr || true)
	{
		return (DisplayInitError(DisplayInitErrorCode::CannotInitDisplay,GetLastErrorAsString()));
	}
	wglMakeCurrent(m_DC,m_renderingContenxt);
	return (DisplayInitResult());
}

void OpenGLWin32Display::Present()
{
	if (m_renderingContenxt != nullptr)
	{
		SwapBuffers(m_DC);
	}
}

OpenGLWin32Display::~OpenGLWin32Display() {
	if (m_renderingContenxt != nullptr)
	{
		if (m_DC != nullptr)
		{
			wglMakeCurrent(m_DC, nullptr);
		}
		wglDeleteContext(m_renderingContenxt);
	}
	DestroyWindow(m_hwnd);
}