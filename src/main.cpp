#include "Win32/GL/wglext.h"
#include <windows.h>
#include "Win32/OpenGLDisplayWin32.h"
#include <iostream>
#include <memory>
extern std::weak_ptr<IDisplay> EntryPoint();

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Win32Display* windowsExtraData = reinterpret_cast<Win32Display*>((LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (windowsExtraData == nullptr || windowsExtraData->GetWindowHandle() != hWnd)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
        break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main() {
    std::weak_ptr<IDisplay> display = ::EntryPoint();
    bool isNotExpired = !display.expired();
    if (isNotExpired)
    {
        std::shared_ptr<IDisplay> _display = display.lock();
        _display->Show();
    }
    bool running = true;
    while (running) {
        MSG msg;
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
    }
}