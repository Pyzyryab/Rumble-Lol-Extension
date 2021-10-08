#include "RumbleLeague.hpp"

using namespace std;
using namespace cv;

/// <summary>
/// The main goals of the default constructor it's to create the objects on which depends.
/// They will by dispatched via dinamic memory allocation, storing them on the heap and saving on the stack
/// the pointers that are pointing to them.
/// 
/// Be careful that if we lose those pointers, will leak memory.
/// </summary>
RumbleLeague::RumbleLeague()
{
	this->window_capture = new WindowCapture();
	this->rumble_vision = new RumbleLeagueVision();
}

RumbleLeague::RumbleLeague(const std::string&)
{
	this->window_capture = new WindowCapture();
	this->rumble_vision = new RumbleLeagueVision();
}


/// The main method to perform BOT actions against the League of Legends client
void RumbleLeague::league_client_action()
{
	// TEMPLATE MATCHING
	cv::Mat img_to_find = cv::imread("../assets/SP/boton_jugar.jpg", COLOR_BGR2BGRA);
	Mat img_to_find_as_real_4channels;
	cvtColor(img_to_find, img_to_find_as_real_4channels, COLOR_BGR2BGRA); // TODO Explanation

	bool moved_once = false;
	int key = 0;
	while (key != 27) // 'ESC' key
	{
		Mat video_source = this->window_capture->get_video_source();
		Mat* video_source_ptr = &video_source;

		//// Img finder. Matches the video source and the needle image and returns the point where the needle image is found inside the video source.
		Point m_loc = this->rumble_vision->find(video_source_ptr, img_to_find_as_real_4channels);
		std::cout << "MATCH LOCATION -> " << m_loc << std::endl;

		// If match location
		// If statement for debug purposes. This one should be replaced for a method call that parses the input query from the user voice
		// and decides what event should run
		if (m_loc.x != 0 && m_loc.y != 0 && moved_once == false) // Moved once just acts as a control flag to only run this one time, or 
		// the mouse will be perma moving towards the match coordinates
		{
			RumbleMotion* rumble_motion = new RumbleMotion();
			rumble_motion->move_mouse_and_left_click(m_loc.x, m_loc.y);
			moved_once = true;
			delete rumble_motion;
		}

		cv::imshow(window_name, *video_source_ptr);
		key = waitKey(60); // you can change wait time
	}

	// Prevents to leak memory and clean up resources
	cv::destroyAllWindows();

}
