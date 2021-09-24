#pragma once

#include <string>
#include <windows.h>

using namespace std;

class WindowCapture
{
private:
	int width;
	int height;
	HWND hwnd;
	string window_name;

public:
	// Class constructor
	WindowCapture(string window_name);

	//// Methods
	int get_screenshot();
	void list_window_names();
	int get_screen_position(int pos);

};
