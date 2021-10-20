#pragma once

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comdlg32.lib")

#include <Windows.h>

class RumbleMotion
{
	public:
		void move_mouse_and_left_click(int x, int y);
};