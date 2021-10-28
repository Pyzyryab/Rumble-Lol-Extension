#include "LeagueClientScreen.hpp"
#include <algorithm>
#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>


/**
* Default constructors
*/
LeagueClientScreen::LeagueClientScreen() {}

MainScreen::MainScreen() {}

ChooseGame::ChooseGame() {}

/**
* Virtual destructor for the base class.
* 
* This destructor allows to fully safe delete all resources allocated via dynamic dispatch.
* 
* If a given class instanciate a child of the LeagueClientScreen via pointer reference (polymorphsm) 
* the virtual destructor deletes the resources associated with the child class, not with the base (or parent) class.
*/
LeagueClientScreen::~LeagueClientScreen()
{
	std::cout << "Virtual destructor called for the child of LeagueClientScreen: " << this->get_identifier() << std::endl;
}



// This factory method is a static method of a class that returns an object of that class' type. 
// But unlike a constructor, the actual object it returns might be an instance of a subclass. 
// Another advantage of a factory method is that it can return existing instances multiple times.
LeagueClientScreen* LeagueClientScreen::factory_screen(const LeagueClientScreenIdentifier& screen_identifier)
{
	switch (screen_identifier)
	{
	case LeagueClientScreenIdentifier::MainScreen:
		return new MainScreen;
		break;
	case LeagueClientScreenIdentifier::ChooseGame:
		return new ChooseGame;
		break;
		// TODO Implement the other methods
	}

}

std::vector<std::string>& split_by_delimiter(const std::string& input, char delimiter, std::vector<std::string>& output)
{
	// construct a stream from the string 
	std::stringstream ss(input);

	std::string s;
	while (std::getline(ss, s, delimiter)) {
		output.push_back(s);
	}

	return output;
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
	std::vector<ClientButton*> matched_buttons {};
	
	std::vector<std::string> splitted_input;
	splitted_input = split_by_delimiter(user_input, ' ', splitted_input);

	// Outputing debug info to the console
	std::cout << "\nSplitted user input: " << std::endl;
	for (int i = 0; i < splitted_input.size(); i++)
		std::cout << "    N" << i + 1 << ": " << splitted_input[i] << std::endl;

	std::cout << "\nGetting data from: " << this->get_identifier() << std::endl;
	
	// TODO Get the correct language to get the correct array from the config struct
	std::vector<ClientButton*> buttons = this->get_english_client_buttons();

	for (const auto word : splitted_input) {
		std::cout << "" << std::endl;
		std::cout << "Comparing: " << word << std::endl;
		for (int i = 0; i < buttons.size(); i++) {
			std::cout << " with: " << buttons[i]->identifier << std::endl;
			if ( strcmp(buttons[i]->identifier, word.c_str()) == 0 ) {
				std::cout << "\t Match founded!" << std::endl;
				matched_buttons.push_back(buttons[i]);
			}
			else 
			{
				std::cout << "\t No match!" << std::endl;
			}
		}
	}

	return matched_buttons;
}

/**
* Getters for the LeagueClientScreenIdentifier identifiers
*/
LeagueClientScreenIdentifier LeagueClientScreen::get_identifier()
{
	return this->identifier;
}

LeagueClientScreenIdentifier MainScreen::get_identifier()
{
	return this->identifier;
}

LeagueClientScreenIdentifier ChooseGame::get_identifier()
{
	return this->identifier;
}


/**
* Getters for the keyword identifiers
*/
std::vector<ClientButton*> LeagueClientScreen::get_english_client_buttons()
{
	return this->english_client_buttons;
}

std::vector<ClientButton*> MainScreen::get_english_client_buttons()
{
	return this->english_client_buttons;
}

std::vector<ClientButton*> ChooseGame::get_english_client_buttons()
{
	return this->english_client_buttons;
}


std::vector<ClientButton*> LeagueClientScreen::get_spanish_client_buttons()
{
	return this->spanish_client_buttons;
}

std::vector<ClientButton*> MainScreen::get_spanish_client_buttons()
{
	return this->spanish_client_buttons;
}

std::vector<ClientButton*> ChooseGame::get_spanish_client_buttons()
{
	return this->spanish_client_buttons;
}

