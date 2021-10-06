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

		void setup_bitmap(BITMAPINFOHEADER* bi, int width, int height);

	public:
		WindowCapture();
		WindowCapture(string window_name);

		/// Methods
		Mat get_video_source();
		// TODO Future impl as a helper to retrieve available windows names
		void list_window_names();
};