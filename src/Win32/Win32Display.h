#pragma once
#include <Windows.h>
#include "IDisplay.h"
class Win32Display : public IDisplay {
protected:
	HWND m_hwnd;
	HDC m_DC;
	std::string m_className;
public:
	Win32Display(std::string i_className);
	bool Init(std::string i_title, uint32_t width, uint32_t height) override;
	void Show() override;
	void Present() override;
	HWND& const GetWindowHandle();
	HDC& const GetDC();
	virtual ~Win32Display();
};