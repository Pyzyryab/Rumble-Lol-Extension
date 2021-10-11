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
	current_league_client_screen{ LeagueClientScreen::factory_screen(LeagueClientScreenIdentifier::MainScreen) }
{ 
	this->set_cpp_language();
}

RumbleLeague::RumbleLeague()
	: RumbleLeague{ 1 }  // 1 it's the ID for the default language (English)
{
	this->window_capture = new WindowCapture();
	this->rumble_vision = new RumbleLeagueVision();
	this->current_league_client_screen = LeagueClientScreen::factory_screen(LeagueClientScreenIdentifier::MainScreen);
	
	this->set_cpp_language();
}


/// The main interface method exposed to the Python API.
/// It's receives the query that the user entered, parse it again and decides what type
/// of action should be performed
/// 
/// TODO insted of void, should return something meaninful to the Python API, in order to talk with the user
/// if something goes wrong, of if the user tries to be smarter that Rumble ;)
void RumbleLeague::league_client_action(const std::string& user_input)
{
	// TODO Change the implementor's method name
	// 1ºst -> Get a list with the user words that have relationship with the CURRENT active League of Legends client window
	auto matched_keywords = this->current_league_client_screen->matched_keywords(user_input);
	
	/* 2 ->
		TODO Design a logical patter for when the matched keywords it's bigger than one...
		Should just take the first? Make a NLP processing? Just returning an string with a voice error message
		indicating that two petitions can't be processed at the same time?

		Maybe just the more coincident? 80% coincident?
	*/

	// Debug
	std::cout << "\n *************************" << endl;
	for (auto word : matched_keywords)
		std::cout << "Matched keyword: " << word << endl;

	/** 3->Detect the desired client action ?
		A way of avoid using another switch?
		Probably a map to store a method call?
		Maybe the method internally should have a switch with the correct image to load?

		Or just one only method that gets the next window? ie. the matching word should have a LeagueClientScreenIdentifier associated
		This leads to probably better returning a LeagueClientScreenIdentifier, that will indicates the desired action and the next screen

		11/Oct/2021 1st idea. I'm tired of the job. Tomorrow I will travel from the north of Spain to the south of Portugal. 
		Just wanna try at least, one of the three ways that I thought about.

		The decision tree design will follow two branches.  
			**Direct decision** -> Like for example: 
				- I want to play an Aram, so from the Main Screen of the client the rle will auto
				make all the necessary steps to perform an action.
				- I want to play a ranked as a jungler and midlaner, so the same but it will auto-select the summoner position
			**Simple decision** -> Every screen contains identifiers that will match all the posible movements from this screen to the next,
				so the example above will be:
				1º Wanna play / play
				2º Ranked solo / duo
				3º midlaner, jungler
				4º Here will be the find match
				5º Autoaccept game (automatic)
				6º Choose me "Zed"
				7º Ban "Vex, it's `fuc****` broken
				8º Change nº of rune pages? (Complicated, implies slide)
				9º Change summoners
				10º Select skin (by name, or move right left)

		So, with this design patters, let's go ahead and implement a very basic approach to this task.

		WARNING! -> I can ensure that will be a lot of refactor of this first things, always found a better way of design a solution to a problem
		but, first make it work, then make it beautiful, then make it fast.

		Note: This formulation of this statement has been attributed to KentBeck; it has existed as part of the UnixWay for a long time.

		
		So, to acomplish this difficult task, several things have to happen.

		1º Something as to received the coincident match and find in some data structure, the coordinates in the screen and select the appropiated
		needle image to find those coordinates.

		Assuming that for example, let's try to just move to the match type select screen from the main screen.
		We will need to parse the input, (assuming that we will receive "play" as command),
		the method that parse it will return something that identifies that we need the image under the "../{language}/{image_name}.jpg" folder.
		Then, we will found that image on the screen, return the coordinates, and click on the image. Simple, right?

		Very important thing, when we move from one screen to another, we should manually manage to delete the instance of the current screen 
		identifier (remember that we only have a pointer to the instance, not an identifier, so it's a crucial thing), and manage to instanciate
		a new one and set it as the new current_league_client_screen.

		To start, then, we need a method that takes a string, and call the factory static methods that creates the correct instance based on 
		a LeagueClientScreenIdentifier. So it's really easy, after too much text, the first thing that we need it's just a method that 
		matches a string


		¡¡¡ LAST HOUR NOTE !!! Should, using a map, just use the LeagueClientScreen as the unique class? Avoiding have to right
		a lot of individual child classes?

		The options are, write child classes (inherited from LeagueClientScreen), with the basic data handcoded inside
		(the keywords, the variant of the LeagueClientScreenIdentifier...), or store that data on a map (or a switch statement)
		and recover it by it's identifier?

	*/
}

void change_screen(const std::string& match)
{
	// This map will be stored in another place, and called here, but for now...
	// Thinking about the map's signature, it can contains an <char*, LeagueClientScreen>
	const std::map<const char*, LeagueClientScreenIdentifier> screen_options{
		std::make_pair("play", LeagueClientScreenIdentifier::MainScreen)
	};

	// So, the first thing that the method will do, should be get the value from the unique key

	
	// Second should be call the factory method and create a new instance

	// Third will be reasing the memory where it's pointing the current_league_client_screen variable
	// to the new created object
}

//void do_things() {
// 
//	// TODO Select what it's the needle image based on the input
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

void RumbleLeague::set_cpp_language()
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
