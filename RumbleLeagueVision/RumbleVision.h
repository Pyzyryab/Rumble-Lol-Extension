#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;

class RumbleLeagueVision
{
	private:
		// pass

	public:

		/// <summary>
		///  Finds (if exists) an image inside another parent image.
		/// The method's job it's to find an image inside a VideoStream, directly taken from the Windows API
		/// and to return the left-upper coordinates where the match happens.
		/// </summary>
		/// <param name="img"></param>
		/// <param name="templ"></param>
		/// <param name="threshold"></param>
		/// <param name="debug_mode"></param>
		/// <returns></returns>
		Point find(Mat* video_src, Mat templ, double threshold = 0.95, bool debug_mode = false);
};