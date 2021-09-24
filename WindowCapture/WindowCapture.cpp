#include <iostream>
#include <string>

#include "WindowCapture.h"


WindowCapture::WindowCapture(std::string window_name)
{
	this -> window_name = window_name;

	std::cout << window_name << std::endl;
}

// TODO Methods impl pending

int WindowCapture::get_screenshot()
{
	return 0;
}

void WindowCapture::list_window_names()
{
	// Pending
}

int WindowCapture::get_screen_position(int pos)
{
	return 0;
}
