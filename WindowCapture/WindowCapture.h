#pragma once

#include <string>
#include <windows.h>

using namespace std;

class WindowCapture
{
private:
	HWND hwnd;
	string window_name;

public:
	// Default constructor
	WindowCapture();

	WindowCapture(string window_name);


	// Methods
	int get_screenshot();
	void list_window_names();
	int get_screen_position(int pos);

};
