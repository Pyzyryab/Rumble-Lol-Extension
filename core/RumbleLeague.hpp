#pragma once

#pragma comment(lib, "C:\\vcpkg\\installed\\x64-windows\\lib\\opencv_core.lib")
#pragma comment(lib, "C:\\vcpkg\\installed\\x64-windows\\lib\\opencv_highgui.lib")
#pragma comment(lib, "C:\\vcpkg\\installed\\x64-windows\\lib\\opencv_imgproc.lib")
#pragma comment(lib, "C:\\vcpkg\\installed\\x64-windows\\lib\\opencv_imgcodecs.lib")

#include "opencv2/opencv.hpp"

#include "../motion/RumbleMotion.hpp"
#include "../gision/RumbleVision.h"
#include "../window_capture/WindowCapture.h"
#include "league_client/LeagueClientScreen.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/EnumTypes.hpp"


class RumbleLeague
{
	private:
		// The title of the opencv generated window that shows the matching results if it's active (debug mode)
		static constexpr const char* titlebar_window_name = "C++ Rumble AI League of Legends Extension";

		// The current Rumble AI user selected language. This extension uses the same criteria as the parent app for
		// recognize and work with a language. It's used receive a value throught a constructor parameter and
		// transform it into a C++ enum variant
		int language_id;

		// Control flag to allow the Python's side determine when it's desired to see some useful logs
		// or even the OpenCV window showing how it's performing a match on the image
		bool debug_mode;

		// The current selected language, as a C++ enum variant. This tracks the language that the main API it's using,
		// and acts as a flag for some common tree decision actions based on what the user it's quering.
		Language language;


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

		// The League of Legends client screen on which the user it's currently located
		LeagueClientScreen* current_league_client_screen;

		// The League of Legends client screen previous to the current one
		LeagueClientScreen* previous_league_client_screen;

		// Represents the user command voice to choose a match
		LeagueClientScreenIdentifier game_lobby_candidate;


		/// Private methods. Should act as a helper for parse info or performs internal operations

		// Sets the language on this C++ library by taking the id of the language (provided via constructor from Rumble AI),
		// and converting it into an variant of the Language (enum) type in the implementation of this method
		void set_cpp_language();

		// Sets the correct lobby screen when the "GO" button it's called. Go button leads to a lobby screen, but we had to know what
		// lobby it's the right one. The reason it's that the selection of the game mode doesn't lead to change the screen of what 
		// this->current_league_screem it's pointing to. 
		void set_correct_lobby_screen();


		// Sets the image that will be the needle to detect against the video stream
		void set_needle_image(const ClientButton* const& client_button, cv::Mat& needle_image);


	public:
		// Constructors
		RumbleLeague();
		RumbleLeague(const int language_id, const bool debug_mode);
		// TODO Implement the copy and the move constructors

		// TODO Implement the destructor, and log some useful details that will help to decide an option about concurrent tasks on Python's side

		// The entry point for the Python API
		const char* play(const std::string& user_input);

		void league_client_action(const ClientButton* const& client_button);

};