#include <iostream>

#include "WindowCapture/WindowCapture.h"
#include "RumbleVision/RumbleVision.h"
#include "RumbleMotion/RumbleMotion.hpp"

using namespace std;
using namespace cv;


/// <summary>
/// TODO -> Now main it's been working as the entry point of the program, simullating the main logic to later, transform and run this code as
/// part of the Rumble LoL Extension library a libray.
/// This library will be loaded directly into the Python interpreter as a normal one, like OPENCV, Godot API, or C's Numpy for ex.
/// </summary>
/// <returns></returns>
int main() {

	const char* window_name = "C++ Rumble AI League of Legends Extension";

	cout << "Hi there with OPENCV4 on C++" << endl;

	// Declares our helper to get the video source
	// BIG TODO -> On the named constructor, should implement a way to converse coordinates from a captured window,
	// ie, the League of Legends window, instead of capturing the whole screen. Second way it's the implemented right now,
	// because the match location also matches where the program should make the mouse click action.
	// The W2 lib has a method that converts the internal window coordinates(Client) to Screen coordinates 
	// -> ::ClientToScreen( hwndDesktop, mouse_click_point_ptr );
	WindowCapture windowCapture;

	// Rumble Vision. Tools for simulate vision skills for Rumble AI.
	RumbleLeagueVision rumbleLeagueVision;

	
	// TEMPLATE MATCHING
	// TODO Make the 
	cv::Mat img_to_find = cv::imread("encontrar_partida.jpg", COLOR_BGR2BGRA);
	Mat img_to_find_as_real_4channels;
	cvtColor(img_to_find, img_to_find_as_real_4channels, COLOR_BGR2BGRA); // TODO Explanation

	bool moved_once = false;
	int key = 0;
	while (key != 27) // 'ESC' key
	{
		Mat video_source = windowCapture.get_video_source();
		Mat* video_source_ptr = &video_source;
	
	    // Img finder. Matches the video source and the needle image and returns the point where the needle image is found inside the video source.
	    Point m_loc = rumbleLeagueVision.find(video_source_ptr, img_to_find_as_real_4channels);
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
	
		imshow(window_name, *video_source_ptr);
		key = waitKey(60); // you can change wait time
		
	}
		
	// Prevents to leak memory and clean up resources
	cv::destroyAllWindows();

	return 0;
}
