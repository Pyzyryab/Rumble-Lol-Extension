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
#include "../helpers/StringHelper.cpp"


class RumbleLeague
{
	private:
		// The title of the opencv generated window that shows the matching results if it's active (debug mode)
		static constexpr const char* titlebar_window_name = "C++ Rumble AI League of Legends Extension";

		// The current Rumble AI user selected language. This extension uses the same criteria as the parent app for
		// recognize and work with a language. It's used receive a value throught a constructor parameter and
		// transform it into a C++ enum variant
		int language_id;
		// The availiable languages as an enum type
		enum class Language { English, Spanish };
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

		// A map to store all the available League of Legends screen instances of the classes that represents them.
		// Think about the map's signature, it will be <const char*, LeagueClientScreen*>,
		// containing all the childrens of the LeagueClientScreen class. It's literally a map with a matched keyword as a key, that it's contained
		// on one of the array of keywords of the instance stored as a value, with a raw pointer to that instance.
		// It's really important to underestand what are the values stored with the new operator, and that it's because the new operator
		// always returns a pointer to the new allocated object, and that's exactly what we need, a container of polymorphic objects.
		// Simply note how this class just stores a pointer to the base class, and they behaves at the desired class at runtime.
		// Note that also the map needs a custom comparator to find a value by the key with the .find() method, because the key type it's
		// const char*, or simply an array of pointers to inmutable strings, so if we use the .find() method with some string value, it will just
		// compare memory locations, no string values.
		const std::map<const char*, LeagueClientScreen*, StringHelper::cmp_str> available_league_client_screens {
			std::make_pair("start", new MainScreen), // TODO SPLIT BY LANGUAGE THE MAP
			std::make_pair("inicio", new MainScreen),
			std::make_pair("jugar", new ChooseGame),
			std::make_pair("play", new ChooseGame)
		};


		/// Private methods. Should act as a helper for parse info or performs internal operations

		// Sets the language on this C++ library by taking the id of the language (provided via constructor from Rumble AI),
		// and converting it into an variant of the Language (enum) type in the implementation of this method
		void set_cpp_language();


	public:
		// Constructors
		RumbleLeague();
		RumbleLeague(const int language_id);
		// TODO Implement the copy and the move constructors

		// The entry point for the Python API
		void play(const std::string& user_input);

		void league_client_action(const ClientButton* const& client_button);

		void set_needle_image(const ClientButton* const& client_button, cv::Mat& needle_image);
};