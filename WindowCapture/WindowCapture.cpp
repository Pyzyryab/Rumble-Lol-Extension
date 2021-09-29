#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "WindowCapture.h"
#include "../Helpers/StrHelper.cpp"

using namespace std;
using namespace cv;

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
Mat hwnd2mat(HWND hwnd)
{
    HDC deviceContext = GetDC(hwnd);
    HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

    RECT windowRect;
    GetClientRect(hwnd, &windowRect);

    int height = windowRect.bottom;
    int width = windowRect.right;

    HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

    SelectObject(memoryDeviceContext, bitmap);

    // Copy data into bitmap
    BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);


    // Specify format by using bitmapinfoheader!
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;  // because no compression
    bi.biXPelsPerMeter = 0; 
    bi.biYPelsPerMeter = 0; 
    bi.biClrUsed = 0; 
    bi.biClrImportant = 0;

    cv::Mat mat = cv::Mat(height, width, CV_8UC4); // 8 bit unsigned ints 4 Channels -> RGBA

    // transform data and store into mat.data
    GetDIBits(memoryDeviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // Clean up!
    DeleteObject(bitmap);
    DeleteDC(memoryDeviceContext);  // Delete, not release!
    ReleaseDC(hwnd, deviceContext);

    return mat;
}

void WindowCapture::list_window_names()
{
	// Pending
}

int WindowCapture::get_screen_position(int pos)
{
	return 0;
}
