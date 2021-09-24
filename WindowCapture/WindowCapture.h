#pragma once

#include <string>

using namespace std;

class WindowCapture
{
private:
	string window_name;

public:
	// Class constructor
	WindowCapture(string window_name);

	//// Methods
	int get_screenshot();
	void list_window_names();
	int get_screen_position(int pos);

};
