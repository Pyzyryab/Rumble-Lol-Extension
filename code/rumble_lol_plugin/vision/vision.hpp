#pragma once

#include "opencv2/opencv.hpp"

class RumbleLeagueVision
{
	private:
		// pass

	public:
		/** 
		 * Finds (if exists) an image inside another parent image.
		 * The method's job it's to find an image inside a VideoStream, directly taken from the Windows API
		 * and to return the left-upper coordinates where the match happens. 
		*/
		cv::Point find(cv::Mat* video_src, cv::Mat templ, double threshold = 0.05, bool debug_mode = false);
};