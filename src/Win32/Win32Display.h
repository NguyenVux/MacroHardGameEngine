#pragma once
#include <Windows.h>
#include "IDisplay.h"
class Win32Display : public IDisplay {
protected:
	HWND m_hwnd;
	HDC m_DC;
public:
	bool Init(std::string i_title, uint32_t width, uint32_t height) override;
	void Show() override;
	HWND& const GetWindowHandle();
	HDC& const GetDC();
};