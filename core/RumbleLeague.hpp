#include "../motion/RumbleMotion.hpp"
#include "../vision/RumbleVision.h"
#include "../window_capture/WindowCapture.h"

class RumbleLeague
{
private:
	// The title of the opencv generated window that shows the matching results if it's active (debug mode)
	static constexpr const char* window_name = "C++ Rumble AI League of Legends Extension";

	// The current Rumble AI user selected language. This extension uses the same criteria as the parent app for
	// recognize and work with a language. It's used receive a value throught a constructor parameter and
	// transform it into a C++ enum variant
	int language_id;
	// The availiable languages as an enum type
	enum class Language { English, Spanish };
	// The current selected language, as a C++ enum variant. This tracks the language that the main API it's using,
	// and acts as a flag for some common tree decision actions based on what the user it's quering.
	Language language;

	
	// TODO Refactor this as a whole new class??
	// TODO Should be two classes, one for the client and one for the in game actions? (This is a different window)
	// The League of Legends client screen on which the user it's currently located
	enum class LeagueClientScreen { MainScreen, ChooseGame, FindGame, AcceptDecline, ChampSelect };  // TODO Complete or refactor
	LeagueClientScreen current_league_client_screen;


	/// BIG THING

	

	// Declares our helper to get the video source
	// BIG TODO -> On the named constructor, should implement a way to converse coordinates from a captured window,
	// ie, the League of Legends window, instead of capturing the whole screen. Second way it's the implemented right now,
	// because the match location also matches where the program should make the mouse click action.
	// The W2 lib has a method that converts the internal window coordinates(Client) to Screen coordinates 
	// -> ::ClientToScreen( hwndDesktop, mouse_click_point_ptr );
	WindowCapture* window_capture;

	// Rumble Vision. Tools for simulate vision skills for Rumble AI.The main goal of this object 
	// it's to interface the "find" method, that will locate the images of the League Client on the screen
	// that will match the image that we need to perform an action
	RumbleLeagueVision* rumble_vision;


	/// Private methods. Should act as a helper for parse info or performs internal operations

	// Sets the C++ language by taking the id of the language provided via constructor from Rumble AI, and converting it to the Language type.
	void set_cpp_language(const int language_id);


	public:
		RumbleLeague();
		RumbleLeague(const int language_id);

		// Main action ??
		void league_client_action(const std::string& user_input);


		void play_game();
};