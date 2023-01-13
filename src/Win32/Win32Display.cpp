#include "Win32Display.h"


extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



bool Win32Display::Init(std::string i_title,uint32_t width, uint32_t height) {
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = GetModuleHandle(nullptr);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground = 0;
    window_class.lpszClassName = TEXT("Learning OpenGL");
    if (!RegisterClass(&window_class)) {
        return false;
    }

    m_hwnd = CreateWindow(
        window_class.lpszClassName,
        i_title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        0,
        0,
        GetModuleHandle(nullptr),
        0);
    if (!m_hwnd) {
        return false;
    }
    m_DC = ::GetDC(m_hwnd);
    if (!m_DC) {
        return false;
    }
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

void Win32Display::Show() {
    ShowWindow(m_hwnd, SW_NORMAL);
}

HWND& const Win32Display::GetWindowHandle()
{
    return m_hwnd;
}

HDC& const Win32Display::GetDC()
{
    return m_DC;
}
