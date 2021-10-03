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
	wchar_t const *desired_window { StrHelper::to_wstring(this->window_name).c_str() }; 
	this->hwnd = FindWindowW(
		NULL,
		desired_window
	);

	std::cout << "Current window name: " << desired_window << std::endl;
}


// TODO Methods impl pending

/// Creates a cv:Mat object from a Windows window handler
Mat WindowCapture::hwnd2mat()
{
    HDC deviceContext = GetDC(this->hwnd);
    HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);
    SetStretchBltMode(memoryDeviceContext, COLORONCOLOR);

    RECT windowRect;
    GetClientRect(this->hwnd, &windowRect);

    int height = windowRect.bottom;
    int width = windowRect.right;

    HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

    SelectObject(memoryDeviceContext, bitmap);

    // Copy data into bitmap
    BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);


    // Specify format by using bitmapinfoheader!
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER *bi_ptr = &bi;
    this->setup_bitmap(bi_ptr, width, height);

    // Creates a new matrix to store the final result of 8 bit unsigned ints 4 Channels -> RGBA
    cv::Mat mat = cv::Mat(height, width, CV_8UC4); 

    // Transform data and store into mat.data
    GetDIBits(memoryDeviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*) bi_ptr, DIB_RGB_COLORS);

    // Clean up!
    DeleteObject(bitmap);
    DeleteDC(memoryDeviceContext);  // Delete, not release!
    ReleaseDC(hwnd, deviceContext);

    return mat;
}


/// Sets up the info of the newly bitmap
void setup_bitmap(BITMAPINFOHEADER *bi, int width, int height)
{
    (*bi).biSize = sizeof(BITMAPINFOHEADER);
    (*bi).biWidth = width;
    (*bi).biHeight = -height;
    (*bi).biPlanes = 1;
    (*bi).biBitCount = 32;
    (*bi).biCompression = BI_RGB;
    (*bi).biSizeImage = 0;  // Because no compression
    (*bi).biXPelsPerMeter = 0; 
    (*bi).biYPelsPerMeter = 0; 
    (*bi).biClrUsed = 0; 
    (*bi).biClrImportant = 0;
}


// TODO As a helper?
void WindowCapture::list_window_names()
{
	// Pending
}
