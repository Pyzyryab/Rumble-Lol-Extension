#include "RumbleVision.h"

using namespace std;
using namespace cv;


Point RumbleLeagueVision::find(Mat* video_src, Mat templ, double threshold, bool debug_mode)
{
    // Const data for this method
    const char* image_window = "Source Image";
    const char* result_window = "Result window";
    const int match_method = TM_SQDIFF_NORMED;
    const int img_matrix_type = CV_8UC4;
    
    // Deferencing the video and bring it's value
    Mat img = *video_src;

    // The resulting matrix with the desired image
    Mat result;
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create(result_rows, result_cols, img_matrix_type);

    // Runs the OPENCV matching algorithm, storing the data into result
    cv::matchTemplate(img, templ, result, match_method);


    // Given a matrix, finds the best and worst (this is dependant on match method)
    Point matchLoc; Point minLoc; Point maxLoc;
    double minVal; double maxVal;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    // For the first two methods(TM_SQDIFF and MT_SQDIFF_NORMED) the best match are the lowest values.For all the others,
    // higher values represent better matches.So, we save the corresponding value in the matchLoc variable
    (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) ? matchLoc = minLoc : matchLoc = maxLoc;


    if (minVal < threshold)
    {
        rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), CV_RGB(0, 255, 0), cv::BORDER_CONSTANT);
        return matchLoc;
    }

    //TODO Threat this line as a debug flag controlled parameter?
   //imshow(image_window, img);

    return Point();
}

