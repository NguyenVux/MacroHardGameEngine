#include "Win32Display.h"


extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



Win32Display::Win32Display(std::string i_className):
    m_DC(nullptr),
    m_hwnd(nullptr)
{
    m_className = i_className;
}

DisplayInitResult Win32Display::Init(std::string i_title,uint32_t width, uint32_t height) {
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = GetModuleHandle(nullptr);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground = 0;
    window_class.lpszClassName = m_className.c_str();
    if (!RegisterClass(&window_class)) {
        return DisplayInitError(DisplayInitErrorCode::CannotInitDisplay, "Failed to Create WNDCLASS");
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
        return DisplayInitError(DisplayInitErrorCode::CannotInitDisplay, "Failed to Create Window handle");
    }
    m_DC = ::GetDC(m_hwnd);
    if (!m_DC) {
        return DisplayInitError(DisplayInitErrorCode::CannotInitDisplay, "Failed to get Device Context");
    }
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
    return (DisplayInitResult());
}

void Win32Display::Show() {
    ShowWindow(m_hwnd, SW_NORMAL);
}

void Win32Display::Present()
{
}

HWND const Win32Display::GetWindowHandle()
{
    return m_hwnd;
}

HDC const Win32Display::GetDC()
{
    return m_DC;
}

Win32Display::~Win32Display()
{
    ReleaseDC(m_hwnd, m_DC);
    //DestroyWindow(m_hwnd);
}
