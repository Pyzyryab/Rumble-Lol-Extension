#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

#include <rumble_lol_plugin/league_client/screen.hpp>
#include <rumble_lol_plugin/league_client/screen_identifier.hpp>
#include <rumble_lol_plugin/league_client/api_buttons.hpp>
#include <rumble_lol_plugin/helpers/string.hpp>

using namespace std;


/**
* Overloaded constructor.
*/
LeagueClientScreen::LeagueClientScreen(const Language& selected_language)
	: identifier {LeagueClientScreenIdentifier::MainScreen}, 
	selected_language {selected_language} 
{
	this->client_buttons = RLE_data::get_buttons(this->get_selected_language());
}
/**
* Default constructor.
* 
* The default constructor of the base class initializes the member reference variable to Language::English
* as a default value through the default constructor invokation.
*/
LeagueClientScreen::LeagueClientScreen()
	: LeagueClientScreen {Language::English} 
{
	this->client_buttons = RLE_data::get_buttons(this->get_selected_language());
}


/**
* Destructor for this class.
* 
* This destructor allows to fully safe delete all resources allocated via dynamic dispatch.
*/
LeagueClientScreen::~LeagueClientScreen()
{
	std::cout << "Destructor called on the screen of LeagueClientScreen: " << this->get_identifier() << std::endl;
}



/// <summary>
/// Matches an object instance keyword property (keywords are what identifies the actions available 
/// for a concrete LeagueClientScreen child type), returning the ClientButton container with the coincident ones
/// </summary>
/// <returns>
/// std::vector<ClientButton*>
/// </returns>
std::vector<ClientButton*> LeagueClientScreen::find_client_button(const std::string& user_input)
{
	std::vector<ClientButton*> matched_buttons {}; // TODO avoid pointers
	
	std::vector<std::string> splitted_input {
		StringHelper::split_by_delimiter(user_input, ' ', splitted_input)
	};

	// Outputing debug info to the console
	std::cout << "\nSplitted user input: " << std::endl;
	for (int i = 0; i < splitted_input.size(); i++)
		std::cout << "    N" << i + 1 << ": " << splitted_input[i] << std::endl;

	std::cout << "\nGetting data from: " << this->get_identifier() << std::endl;
	
	// Calls the method on the current selected child screen and recovers the client buttons pointers
	// associated with that screen
	std::vector<ClientButton*> buttons = this->get_client_buttons();

	for (const auto word : splitted_input) {
		
		//std::cout << "" << std::endl;
		//std::cout << "Comparing: " << word << std::endl;
		for (const auto button : buttons) {
			if (word.compare(button->identifier)) {
				std::cout << "\t Match founded!" << std::endl;
				matched_buttons.push_back(button); // Ensure that this is a copy
			}
		}
		
		// for (int i = 0; i < buttons.size(); i++) {
			
		// 	//std::cout << " with: " << buttons[i]->identifier << std::endl;
		// 	if (word.compare(buttons[i]->identifier))
		// 	// if ( strcmp(buttons[i]->identifier, word.c_str()) == 0 ) 
		// 	{
		// 		std::cout << "\t Match founded!" << std::endl;
		// 		matched_buttons.push_back(buttons[i]);
		// 	}
		// 	else 
		// 	{
		// 		//std::cout << "\t No match!" << std::endl;
		// 	}
		// }
	}
	return matched_buttons;
}


/**
* Getters
*/
LeagueClientScreenIdentifier LeagueClientScreen::get_identifier()
{
	return this->identifier;
}

std::vector<ClientButton*> LeagueClientScreen::get_client_buttons()
{
	return this->client_buttons;
}

const Language& LeagueClientScreen::get_selected_language()
{
	return this->selected_language;
}


/**
* Setters
*/
void LeagueClientScreen::set_identifier(LeagueClientScreenIdentifier identifier)
{
	this->identifier = identifier;
}