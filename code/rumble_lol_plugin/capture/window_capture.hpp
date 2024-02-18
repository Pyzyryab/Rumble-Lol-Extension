#pragma once

#include <string>
#include <windows.h>
#include <opencv2/opencv.hpp>

class WindowCapture
{
	private:
		HWND hwnd;
		std::string window_name;

		void setup_bitmap(BITMAPINFOHEADER* bi, int width, int height);

	public:
		WindowCapture();
		WindowCapture(std::string window_name);

		/// Methods
		cv::Mat get_video_source();
		
		// TODO Future impl as a helper to retrieve available windows names
		void list_window_names();

		// Getters
		HWND get_hwnd();
};