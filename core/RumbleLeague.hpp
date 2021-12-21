#pragma once

#include "opencv2/opencv.hpp"

#include "actions/ClickScreenButton.hpp"
#include "league_client/LeagueClientScreen.hpp"
#include "../helpers/StringHelper.hpp"
#include "../helpers/EnumTypes.hpp"


class RumbleLeague
{
	private:
		// Counter for the active RumbleLeague instances
		static int instances_counter;

		// Control flag to allow the Python's side determine when it's desired to see some useful logs
		// or even the OpenCV window showing how it's performing a match on the image
		bool debug_mode;

		// Represents the config option where the user desires the behaviour of automatically aceept a match
		// or if prefers to accept it / decline it by voice control
		bool autoaccept_behaviour;

		// The current selected language, as a C++ enum variant. This tracks the language that the main API it's using,
		// and acts as a flag for some common tree decision actions based on what the user it's quering.
		Language language;


		// The League of Legends client screen on which the user it's currently located
		LeagueClientScreen* current_league_client_screen;

		// The League of Legends client screen previous to the current one
		LeagueClientScreen* previous_league_client_screen;

		// Represents the user command voice to choose a match
		LeagueClientScreenIdentifier game_lobby_candidate;


		/*
		* Sets the language on this C++ library by taking the id of the language (provided via constructor from Rumble AI),
		* and converting it into an variant of the Language (enum) type in the implementation of this method
		*/
		void set_cpp_language(const int language_id);

		// Controls and updates in time data about the screens
		void manage_screen_data(const ClientButton* const& client_button);


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
		std::string play(const std::string& user_input);

};