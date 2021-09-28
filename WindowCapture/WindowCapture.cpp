#include <iostream>
#include <string>

#include "WindowCapture.h"
#include "../Helpers/StrHelper.cpp"

/*
	Find the handle for the window we want to capture.
    If no window name is given (by using the default constructor), 
	it will capture the entire screen.
*/

/// <summary>
///  Default constructor
/// </summary>
WindowCapture::WindowCapture()
{
	this->hwnd = GetDesktopWindow();
}

/// <summary>
/// Finds the window with the provided name on the parameter
/// </summary>
/// <param name="window_name"></param>
WindowCapture::WindowCapture(std::string window_name)
{
	// TODO Handle the exception if no window it's founded
	this->window_name = window_name;
	wchar_t const *desired_window { StrHelper::to_wstring(this->window_name).c_str() };  // TODO Pending to debug the posible dangling pointer?
	this->hwnd = FindWindowW(
		NULL,
		desired_window
	);

	std::cout << "Current window name: " << desired_window << std::endl;
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
