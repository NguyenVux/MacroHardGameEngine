#pragma once
#include <string>

class IDisplay {
public:
	virtual void Show() = 0;
	virtual bool Init(std::string i_title, uint32_t width, uint32_t height) = 0;
};