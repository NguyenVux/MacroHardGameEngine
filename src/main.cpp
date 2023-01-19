#include "Win32/GL/wglext.h"
#include <windows.h>
#include "Win32/OpenGLDisplayWin32.h"
#include <iostream>
#include <memory>
#include <chrono>
extern void Update(std::chrono::duration<float> i_delta);
extern void EntryPoint();
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
    bool running = true;
    ::EntryPoint();
    std::chrono::time_point lastFrameTime = std::chrono::system_clock::now();
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
        std::chrono::time_point currentTime = std::chrono::system_clock::now();
        ::Update(currentTime - lastFrameTime);
        lastFrameTime = std::chrono::system_clock::now();
    }
}