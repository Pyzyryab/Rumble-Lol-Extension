#pragma once

namespace Constants
{
    // The title of the opencv generated window that shows the matching results if it's active (debug mode)
    static constexpr const char* TITLEBAR_WINDOW_NAME = "C++ Rumble AI League of Legends Extension";


    /*
    * The amount of precision required to filter the image to find against a source. 
    * Due to the match method used on the OpenCV library for this project, the lower the number, the higher precision should
    * be required to a cv::Mat result to be considered as a match comparing images.
    */ 
    static constexpr double THRESHOLD_RATE = 0.05;

    // Controls where the program it's under debug and testing mode
    static constexpr bool DEBUG_MODE = true;
};