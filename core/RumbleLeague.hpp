#include "../motion/RumbleMotion.hpp"
#include "../vision/RumbleVision.h"
#include "../window_capture/WindowCapture.h"

class RumbleLeague
{
private:
	const char* window_name = "C++ Rumble AI League of Legends Extension";

	// Declares our helper to get the video source
	// BIG TODO -> On the named constructor, should implement a way to converse coordinates from a captured window,
	// ie, the League of Legends window, instead of capturing the whole screen. Second way it's the implemented right now,
	// because the match location also matches where the program should make the mouse click action.
	// The W2 lib has a method that converts the internal window coordinates(Client) to Screen coordinates 
	// -> ::ClientToScreen( hwndDesktop, mouse_click_point_ptr );
	WindowCapture* window_capture;

	// Rumble Vision. Tools for simulate vision skills for Rumble AI.
	// The main goal of this object it's to provide the "find" method, will locate the images
	// of the League Client on the screen
	RumbleLeagueVision* rumble_vision;

	// The current Rumble AI user selected language
	// TODO Create it as an enum variant --> If no language it's provided via constructor, a language must be setted

public:
	RumbleLeague();
	RumbleLeague(const std::string&);

	void league_client_action();
};