#include <algorithm>
#include "RumbleLeague.hpp"

using namespace std;

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
	: autoaccept_behaviour{ autoaccept_behaviour },
	debug_mode{ debug_mode },
	previous_league_client_screen{ nullptr },
	game_lobby_candidate{ LeagueClientScreenIdentifier::SummonersBlindLobby }
{ 
	this->set_cpp_language(language_id);	
	current_league_client_screen = new LeagueClientScreen(this->language);

	// Increment the number of instances created
	++RumbleLeague::instances_counter;
	cout << "Number of active RumbleLeague instances = " << RumbleLeague::instances_counter << endl;
	// TODO Generate exception if are more than one instance
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
	/**
	 * Rumble League has two type of posible pathways:
	 * 1 - Click buttons by voice control. This will be called a "click button" action. 
	 *     It's a really simple action. User provides a command by voice, that should match a button 
	 *     identifier, and Rumble tries to find the button on the screen. If finds it, it makes a click 
	 * 	   on the button on the position where it has been finded.
	 * 
	 * 2 - A compound action. This action will be the precursor of the future neural networks that will 
	 * 	   composite the "Rumble's brain", capable of perform complex actions like pick and ban champs, 
	 * 	   autoaccept games without need to track screen changes and not needing to create procedural 
	 * 	   complex code to achieve the result... etc.
	 * 
	 * 	   For now an action will be a predefined group of "click button" secuences and writing on the
	 *     screen to pick/ban champs or talk with chat. 
	 */

	const std::vector<string> actions_keywords { "want to play ranked",  }; // TODO Changes this line for some serious code
	
	// 1st - Decide if it's an action or a simple click on a button
	std::vector<std::string> splitted_input;
	splitted_input = StringHelper::split_by_delimiter(user_input, ' ', splitted_input);

	for (const auto& word : splitted_input) {
		bool has_action_keyword {
			std::find(actions_keywords.begin(), actions_keywords.end(), word) != actions_keywords.end() 
		};

		if (has_action_keyword) {
			// run action
		} else {
			// Get a list with the client buttons that could possible be the desired user action
			auto matched_client_buttons = this->current_league_client_screen->find_client_button(splitted_input);

			if (matched_client_buttons.size() > 0)
			{
				cout << "\n *************************" << endl;
				for (auto button : matched_client_buttons) {
					cout << "Founded a button candidate: " << button->identifier << endl;
				}

				// TODO Pending the NLP implementation
				const ClientButton* const& button = matched_client_buttons[0];
				cout << "[WARNING] Taking -> " << button->identifier << " <- as the first element matched. "
					"This is because there is not NLP implemented yet." << endl;

				// Calls the member method to perform a desired action based on the matched button.
				this->manage_screen_data(button);

				// TODO Implement the Action factory to really decide what element should be actioned
				// So action could be a member, and with the factory dynamically choose the implementor subclass
				// that encapsulates certain behaviour
				Action* action = new ClickScreenButton(button);
				action->run_action();
				// So, for now, we should free resources
				delete action;
				
				// Special behaviour (Under testing and development)
				if (this->autoaccept_behaviour && this->current_league_client_screen->get_identifier()
					== LeagueClientScreenIdentifier::AcceptDecline)
				{
					cout << "Generating a recursive call for the autoaccept behaviour " << endl;
					// Recursive call for generate the autoaccept match when the screen spawns
					this->play("accept"); // TODO the value should be passed by language
				}
				return "Action completed successfully";
			}	// TODO The return of this method are what actually Rumble talks back to the user, or answers
				// to the user as a response to the command, so every action could potentially have multiple answers
				// and randomly (or not) choose something if talking mode is enabled?
			else 
			{
				return "No match was found for your query";
			}
		}
		// Prevents to leak memory and clean up resources
		cv::destroyAllWindows();
	}

}

/*
* Access the pointer that points to the instance of the LeagueClientScreen member
* after matching a user input and performs some action to updates the value of the
* identifier property, that mimics what it's the current screen on what the 
* League of Legends client are
*/
void RumbleLeague::manage_screen_data(const ClientButton* const& client_button)
{
	/** Updates the pointer to the LeagueClientScreen with the enum value that identifies what screen comes
	* next after pressing any button on the screen.
	*/
	switch (client_button->next_screen)
	{
		case LeagueClientScreenIdentifier::ChooseGame:
			/**
			* When the user it's selecting a game mode to play, the way to go to the lobby screen it's by clicking
			* the "Confirm button". This kind of actions inside the ChooseGame screen break the sense of that any requested action
			* calls a button with a concrete identifier, and that butoon has a variable that points to the next screen.
			* So, we can just simply check when the user it's selecting a game mode, and save the type of game that desires
			* to play in a variable that tracks what button it's being called by voice command.
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
			this->current_league_client_screen->set_identifier(client_button->next_screen);

		default:
			// Any voice command that presses a button that leads to a screen change
			this->current_league_client_screen->set_identifier(client_button->next_screen);
	}

	cout << "[INFO] Current screen -> " <<
		this->current_league_client_screen->get_identifier() << " <- " << endl;
}


// TODO Should be transformed into a config class
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
