#pragma once

#pragma comment(lib, "C:/opencv/build/x64/vc16/lib/opencv_world480.lib")

#include <opencv2/opencv.hpp>

#include <rumble_lol_plugin/motion/motion.hpp>
// #include <rumble_lol_plugin/writer/writer.hpp>
#include <rumble_lol_plugin/vision/vision.hpp>
#include <rumble_lol_plugin/capture/window_capture.hpp>
#include <rumble_lol_plugin/league_client/screen.hpp>
#include <rumble_lol_plugin/league_client/screen_identifier.hpp>
#include <rumble_lol_plugin/helpers/string.hpp>


class RumbleLeague
{
	private:
		// The title of the opencv generated window that shows the matching results if it's active (debug mode)
		static constexpr const char* titlebar_window_name = "C++ Rumble AI League of Legends Extension";

		// Counter for the active RumbleLeague instances
		static int instances_counter;

		/*
		* The amount of precision required to filter the image to find against a source. 
		* Due to the match method used on the OpenCV library for this project, the lower the number, the higher precision should
		* be required to a cv::Mat result to be considered as a match comparing images.
		*/ 
		static constexpr double threshold_rate = 0.05;

		// Control flag to allow the Python's side determine when it's desired to see some useful logs
		// or even the OpenCV window showing how it's performing a match on the image
		bool debug_mode;

		// Represents the config option where the user desires the behaviour of automatically aceept a match
		// or if prefers to accept it / decline it by voice control
		bool autoaccept_behaviour;

		// The current selected language, as a C++ enum variant. This tracks the language that the main API it's using,
		// and acts as a flag for some common tree decision actions based on what the user it's quering.
		Language language;


		/*
		* Declares our helper to get the video source
		* BIG TODO -> On the named constructor, should implement a way to converse coordinates from a captured window,
		* ie, the League of Legends window, instead of capturing the whole screen. Second way it's the implemented right now,
		* because the match location also matches where the program should make the mouse click action.
		* The W2 lib has a method that converts the internal window coordinates(Client) to Screen coordinates 
		* -> ::ClientToScreen( hwndDesktop, mouse_click_point_ptr );
		*/
		WindowCapture* window_capture;

		/*
		* Rumble Vision.Tools for simulate vision skills for Rumble AI.The main goal of this object
		* it's to interface the "find" method, that will locate the images of the League Client on the screen
		* that will match the image that we need to perform an action
		*/
		RumbleLeagueVision* rumble_vision;

		// The League of Legends client screen on which the user it's currently located
		LeagueClientScreen* current_league_client_screen;

		// The League of Legends client screen previous to the current one
		LeagueClientScreen* previous_league_client_screen;

		// Represents the user command voice to choose a match
		LeagueClientScreenIdentifier game_lobby_candidate;


		/// Private methods. Should act as a helper for parse info or performs internal operations

		/*
		* Sets the language on this C++ library by taking the id of the language (provided via constructor from Rumble AI),
		* and converting it into an variant of the Language (enum) type in the implementation of this method
		*/
		void set_cpp_language(const int language_id);

		/*
		* Designed to encapsulate the final behaviour of a move and click action on the RumbleLeague object.
		* This method receives a needle image and inmedialy tries to found it on the video source, 
		* WITHOUT waiting for the image to appear on the screen. This method it's intented to use in basic situations
		* on click buttons that always are on the screen (basically, all buttons) with the exception of those who 
		* has to be awaited to found them. One example is the "Accept" game button or the "Decline" game button.
		* For actions like this, please, refer to the ::wait_event() member method.
		*/
		cv::Point click_event(const cv::Mat& needle_image);

		// Awaits until a event or a desired button to clicks appears on the screen and performs a click action against him
		void wait_event(const cv::Mat& needle_image);

		// Sets the image that will be the needle to detect against the video stream
		void set_needle_image(const std::string& image_path, cv::Mat& needle_image);

		// Executes an internal action of this API
		void league_client_action(const ClientButton& client_button);


	public:
		// Constructors
		RumbleLeague();
		RumbleLeague(const int language_id, bool autoaccept_behaviour, const bool debug_mode);

		// Copy constructor
		RumbleLeague(const RumbleLeague &source);

		// Move constructor
		RumbleLeague(const RumbleLeague &&source);

		// Destructor
		~RumbleLeague();

		// The entry point for the Python API
		const char* play(const std::string& user_input);

};