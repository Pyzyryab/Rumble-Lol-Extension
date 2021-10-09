#include "RumbleLeague.hpp"

using namespace std;
using namespace cv;

/// <summary>
/// 
/// Constructors more critical part it's to create the internal user defined C++ objects
/// { WindowCapture, RumbleLeagueVision } dependant objects of this class.
/// They will by dispatched via dinamic memory allocation, storing them on the heap 
/// and returning a pointer for each of them.
/// Be careful that if we lose those pointers, we will be leaking memory.
/// 
/// Constructors implementation: 
/// 1º -> The overloaded constructor are initializating the member variables through the C++ feature
/// "constructor initialization list", which it's the real way of **initializate** any object property.
/// This is because the compiler knows that at creation time, properties have to be initialized to the passed values.
/// 
/// 2º -> The default constructor, or better, the no args constructor in this case, it's initializing the member
/// variables shown below, and **assign** the window_capture and rumble_vision members to a new object of it's type.
/// In this way, objects are not properly initialized, because when the compiler reaches the body of a constructor, the object itself
/// it's already initialized and already exists in memory, so there what it's really going on it's just an assingment to new values.
/// Members that it's values are assigned on constructor body contains random garbage data before reach this point, and then are
/// overwritten and assigned to new values, so that's why constructor initialization list it's really more efficient
/// 
/// </summary>
RumbleLeague::RumbleLeague(const int language_id)
	: window_capture{ new WindowCapture },
	rumble_vision{ new RumbleLeagueVision },
	current_league_client_screen{ LeagueClientScreen::MainScreen }
{ 
	this->set_cpp_language(language_id);
}

RumbleLeague::RumbleLeague()
	: RumbleLeague{ 1 }
{
	this->window_capture = new WindowCapture();
	this->rumble_vision = new RumbleLeagueVision();
	this->current_league_client_screen = LeagueClientScreen::MainScreen;
	this->set_cpp_language(language_id);
}


/// The main interface method exposed to the Python API.
/// It's receives the query that the user entered, parse it again and decides what type
/// of action should be performed
/// 
/// TODO insted of void, should return something meaninful to Python, in order to talk with the user
/// if something goes wrong, of if the user tries to be smarter that Rumble ;)
void RumbleLeague::league_client_action(const std::string& user_input)
{
	if (this->language == Language::English) {}
		// TODO Pending implementation, because hoxe sábado vou comer Raxo a Muros.
		// Son as 14:20, fai un sol que nin Dios e non me apetece estar na casa.
		// Saludos, picadores!
}

//void do_things() {
// 
//	// 1º Select what it's the needle image based on the input
//	// 
//	// TEMPLATE MATCHING
//	cv::Mat img_to_find = cv::imread("../assets/SP/boton_jugar.jpg", COLOR_BGR2BGRA);
//	Mat img_to_find_as_real_4channels;
//	cvtColor(img_to_find, img_to_find_as_real_4channels, COLOR_BGR2BGRA); // TODO Explanation
//
//	bool moved_once = false;
//	int key = 0;
//	while (key != 27) // 'ESC' key
//	{
//		Mat video_source = this->window_capture->get_video_source();
//		Mat* video_source_ptr = &video_source;
//
//		//// Img finder. Matches the video source and the needle image and returns the point where the needle image is found inside the video source.
//		Point m_loc = this->rumble_vision->find(video_source_ptr, img_to_find_as_real_4channels);
//		std::cout << "MATCH LOCATION -> " << m_loc << std::endl;
//
//		// If match location
//		// If statement for debug purposes. This one should be replaced for a method call that parses the input query from the user voice
//		// and decides what event should run
//		if (m_loc.x != 0 && m_loc.y != 0 && moved_once == false) // Moved once just acts as a control flag to only run this one time, or 
//		// the mouse will be perma moving towards the match coordinates
//		{
//			RumbleMotion* rumble_motion = new RumbleMotion();
//			rumble_motion->move_mouse_and_left_click(m_loc.x, m_loc.y);
//			moved_once = true;
//			delete rumble_motion;
//		}
//
//		cv::imshow(window_name, *video_source_ptr);
//		key = waitKey(60); // you can change wait time
//	}
//
//	// Prevents to leak memory and clean up resources
//	cv::destroyAllWindows();
//}


/**
*  Methods that performs the actions against the League Client
*/
void RumbleLeague::play_game()
{
	// TODO pending impl
}



/**
* Helpers private methods
*/

void RumbleLeague::set_cpp_language(const int language_id)
{
	// Switch statement prefered here 'cause potentially the API could be translated to more languages.
	// Obviously, the default case always should be setted to a default language (English in this case),
	// even if it's already an option. This is 'cause if it's selected first, the compiler don't have to check
	// the another alternatives.
	switch (language_id)
	{
	case 1:
		this->language = Language::English;
		break;
	case 2:
		this->language = Language::Spanish;
		break;
	// ... case N
	default:
		this->language = Language::English;
		break;
	}
}
