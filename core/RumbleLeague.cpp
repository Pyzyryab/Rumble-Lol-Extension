#include "RumbleLeague.hpp"

using namespace std;
using namespace cv;

/** TODO -> Design path

	The decision tree design will follow two branches.
		**Direct decision** -> Like for example:
			- I want to play an Aram, so from the Main Screen of the client the rle will auto
			make all the necessary steps to perform an action.
			- I want to play a ranked as a jungler and midlaner, so the same but it will auto-select the summoner position
		**Simple decision** -> Every screen contains identifiers that will match all the posible movements from this screen to the next,
			so the example above will be:
			1� Wanna play / play
			2� Ranked solo / duo
			3� midlaner, jungler
			4� Here will be the find match
			5� Autoaccept game (automatic)
			6� Choose me "Zed"
			7� Ban "Vex, it's `fuc****` broken
			8� Change n� of rune pages? (Complicated, implies slide)
			9� Change summoners
			10� Select skin (by name, or move right left)
*/

// Initializacion of static non const members of the class
int RumbleLeague::instances_counter{ 0 };

/**
* 
* Constructors more critical part it's to create the internal user defined C++ objects
* { WindowCapture, RumbleLeagueVision } dependant objects of this class.
* They will by dispatched via dinamic memory allocation, storing them on the heap 
* and returning a pointer for each of them.
* Be careful that if we lose those pointers, we will be leaking memory.
* 
* Constructors implementation: 
* 1� -> The overloaded constructor are initializating the member variables through the C++ feature
* "constructor initialization list", which it's the real way of **initializate** any object property.
* This is because the compiler knows that at creation time, properties have to be initialized to the passed values.
* 
* 2� -> The no args constructor in this case, it's initializing he member variables
* throught the overloaded constructor (delegating constructor).
* In this way, objects are not properly initialized, because when the compiler reaches the body of a constructor, the object itself
* it's already initialized and already exists in memory, so there what it's really going on it's just an assingment to new values.
* Members that it's values are assigned on constructor body contains random garbage data before reach this point, and then are
* overwritten and assigned to new values, so that's why constructor initialization list it's really more efficient
* 
* We still have to assign the data of the "current_league_client_screen" member in the constructor body, 'cause until this
* point we don't have available what language (as an Enum variant) it's currently setted.
*/
RumbleLeague::RumbleLeague(const int language_id, const bool autoaccept_behaviour, const bool debug_mode)
	: window_capture{ new WindowCapture },
	rumble_vision{ new RumbleLeagueVision },
	autoaccept_behaviour{ autoaccept_behaviour },
	debug_mode{ debug_mode },
	previous_league_client_screen{ nullptr },
	game_lobby_candidate{ LeagueClientScreenIdentifier::SummonersBlindLobby }
{ 
	this->set_cpp_language(language_id);	
	current_league_client_screen = new LeagueClientScreen(this->language);

	// Increment the number of instances created
	++RumbleLeague::instances_counter;
	cout << "Number of active RumbleLeague instances = " << RumbleLeague::instances_counter << endl;
	
}

// No params constructor. Constructor delegation applied here.
// 1 it's the ID for the default language (English)
RumbleLeague::RumbleLeague() : RumbleLeague{ 1, true, false } {} 


// Destructor
RumbleLeague::~RumbleLeague()
{
	--RumbleLeague::instances_counter;
	cout << "Destructor for the class RumbleLeague has been called. ";
	cout << "Number of active RumbleLeague instances = " << RumbleLeague::instances_counter << endl;
}
 
/**
* The main interface method exposed to the Python API.
* It's receives the query that the user entered, parse it again and decides what type
* of action should be performed
*
* Returns a str with information to the Python API
*/
const char* RumbleLeague::play(const std::string& user_input)
{
	// TODO Very first -> Create the decision tree, to find by action, by button identifier... etc

	// 1�st -> Get a list with the posible client buttons that could possible be the desired user action
	auto matched_client_buttons = this->current_league_client_screen->find_client_button(user_input);

	if (matched_client_buttons.size() > 0)
	{

		/* 2 ->
			TODO Design a logical patter for when the matched keywords it's bigger than one...
			Should just take the first? Make a NLP processing? Just returning an string with a voice error message
			indicating that two petitions (or having two coincident results) can't(shouldn't) be processed at the same time?

			Maybe just the more coincident? or better above 80% coincident?
		*/

		/* 3 ->
			Perform an action against the League Client
		*/

		cout << "\n *************************" << endl;
		for (auto button : matched_client_buttons) {
			cout << "Founded a button candidate: " << button->identifier << endl;
		}

		const ClientButton* const& button = matched_client_buttons[0];
		cout << "[WARNING] Taking -> " << button->identifier << " <- as the first element matched. "
			"This is because there is not NLP implemented yet." << endl;

		// Calls the member method to perform a desired action based on the matched button.
		this->league_client_action(button);
		return "Action completed successfully";
	}
	else 
	{
		return "No match was found for your query";
	}

}

/**
* Moves the mouse and make a click on the location on the League of Legends Client.
* Changes the pointer value what points to instance of the LeagueClientScreen child for the new one after matching a user input,
* and performs some action 
*/
void RumbleLeague::league_client_action(const ClientButton* const& client_button)
{
	// Controls when an even should be awaited (until appears on screen) or not.
	bool wait_event{ false };

	// Tracks the lastest screen seen before the current one
	this->previous_league_client_screen = this->current_league_client_screen;
	cout << "[INFO] Previous screen -> " <<
		this->previous_league_client_screen->get_identifier() << " <- " << endl;

	/** Updates the pointer to the LeagueClientScreen with the enum value that identifies what screen comes
	* next after pressing any button
	*/
	switch (client_button->next_screen)
	{
		case LeagueClientScreenIdentifier::ChooseGame:
			/**
			* When the user it's selecting a game mode to play, the way to go to the lobby screen it's by clicking
			* the "Confirm button". This kind of actions inside the ChooseGame screen break the sense of that any requested action
			* calls a button with a concrete identifier, and that butoon has a variable that points to the next screen.
			* So, we can just simply check when the user it's selecting a game mode, and save the type of game that he/she desires
			* to play in a variable that tracks what button it's pressing (by voice command).
			* If the user finally goes to the lobby screen (by selecting the "Confirm" button) we just simply retrieve that
			* game lobby candidate and pointing again the member variable that tracks it to the correct game lobby.
			* Note that many of the game modes has different game lobbies wih different possible actions
			*/
			if (client_button->lobby != LeagueClientScreenIdentifier::NoLobby)
			{
				this->game_lobby_candidate = client_button->lobby;
				cout << "[INFO] Game lobby candidate -> " << this->game_lobby_candidate << " <- " << endl;
			}

			this->current_league_client_screen->set_identifier(
				client_button->next_screen
			);

			break;

		case LeagueClientScreenIdentifier::GameLobby:
			this->current_league_client_screen->set_identifier(this->game_lobby_candidate);
			break;

		case LeagueClientScreenIdentifier::CancelAction:
			if (this->current_league_client_screen->get_identifier() != LeagueClientScreenIdentifier::AcceptDecline)
				this->current_league_client_screen->set_identifier(LeagueClientScreenIdentifier::MainScreen);
			else
				this->current_league_client_screen->set_identifier(this->game_lobby_candidate);
			break;

		case LeagueClientScreenIdentifier::ChampSelect:
			wait_event = true;
			this->current_league_client_screen->set_identifier(client_button->next_screen);

		default:
			// Any voice command that presses a button that leads to a screen change
			this->current_league_client_screen->set_identifier(client_button->next_screen);
	}

	cout << "[INFO] Current screen -> " <<
		this->current_league_client_screen->get_identifier() << " <- " << endl;


	// Sets the needle image for what we are looking for
	Mat needle_image;
	this->set_needle_image(client_button->image_path, needle_image);

	// Change this for a fn pointer or callback inside the button
	if (!wait_event)
	{
		this->click_event(needle_image);
	}
	else
	{
		
		this->wait_event(needle_image);
	}

	// Special behaviour (Under testing and development)
	if (this->autoaccept_behaviour && this->current_league_client_screen->get_identifier()
		== LeagueClientScreenIdentifier::AcceptDecline)
	{
		cout << "Generating a recursive call for the autoaccept behaviour " << endl;
		// Recursive call for generate the autoaccept match when the screen spawns
		this->play("accept");
	}

	// Prevents to leak memory and clean up resources
	cv::destroyAllWindows();
}

Point RumbleLeague::click_event(const cv::Mat& needle_image)
{
	Mat video_source = this->window_capture->get_video_source();
	Mat* video_source_ptr = &video_source;

	// Img finder. Matches the video source and the needle image and returns the point where the needle image is found inside the video source.
	Point m_loc = this->rumble_vision->find(video_source_ptr, needle_image, RumbleLeague::threshold_rate, this->debug_mode);

	if (m_loc.x != 0 && m_loc.y != 0)
	{
		std::cout << "MATCH LOCATION -> " << m_loc << std::endl;

		RumbleMotion* rumble_motion = new RumbleMotion();
		rumble_motion->move_mouse_and_left_click(m_loc.x, m_loc.y);
		delete rumble_motion;
	}

	return m_loc;
}


void RumbleLeague::wait_event(const cv::Mat& needle_image)
{
	int key = 0;
	while (key != 27) // 'ESC' key
	{
		if (this->click_event(needle_image) != Point{ 0, 0 }) { break; }
		key = waitKey(60); // you can change wait time. Need a large value when the find game it's detected?
	}
}


/**
* Helpers private methods
*/

void RumbleLeague::set_needle_image(const std::string& image_path, Mat& needle_image)
{
	cv::Mat img_to_find = cv::imread(image_path, cv::IMREAD_COLOR);
	cvtColor(img_to_find, needle_image, COLOR_BGR2BGRA);
}

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
