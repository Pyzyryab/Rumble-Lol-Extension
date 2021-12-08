#pragma once

#include <string>
#include <vector>
#include <array>

#include "LeagueClientButton.hpp"
#include "../../helpers/EnumTypes.hpp"

/// <summary>
/// Represents any of the existing screens on the League of Legends client.
/// Used to store as much information it's necessary to complete the desired user request.
/// </summary>
class LeagueClientScreen
{
	private:
		// Stores the window's name as an enum variant
		LeagueClientScreenIdentifier identifier;

		// The current selected language of this API
		const Language &selected_language;

		// Dynamic container for store pointers to the client buttons objects
		std::vector<ClientButton*> client_buttons { };

	public:
		// Constructors
		LeagueClientScreen();
		LeagueClientScreen(const Language &language);

		// Destructor
		~LeagueClientScreen();
		
		// Getters
		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons();
		const Language& get_selected_language();

		// Setters
		void set_identifier(LeagueClientScreenIdentifier identifier);

		// Methods
		std::vector<ClientButton*> find_client_button(const std::string &user_input);
		
};
