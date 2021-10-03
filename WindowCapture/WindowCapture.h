#pragma once

#include <string>
#include <windows.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class WindowCapture
{
	private:
		HWND hwnd;
		string window_name;

		Mat hwnd2mat();
		void setup_bitmap(BITMAPINFOHEADER *bi, int width, int height);

		// TODO Future impl as a helper to retrieve available windows names
		void list_window_names();

	public:
		WindowCapture();
		WindowCapture(string window_name);

};
