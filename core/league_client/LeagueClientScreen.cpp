#include "LeagueClientScreen.hpp"
#include <algorithm>
#include <iostream>

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

// TODO Having the factory static method, constructors should be deleted?
LeagueClientScreen::LeagueClientScreen(LeagueClientScreenIdentifier identifier)
	: identifier{ identifier } {}

LeagueClientScreenIdentifier LeagueClientScreen::get_identifier()
{
	return this->identifier;
}

void LeagueClientScreen::set_identifier(const LeagueClientScreenIdentifier& identifier)
{
	this->identifier = identifier;
}

LeagueClientScreenIdentifier MainScreen::get_identifier()
{
	return league_client_screen_identifier;
}

LeagueClientScreenIdentifier ChooseGame::get_identifier()
{
	return league_client_screen_identifier;
}


/// <summary>
/// Matches an object instance keywords property (keywords are what identifies the actions available 
/// for a concrete LeagueClientScreen child type), returning the coincident ones
/// </summary>
/// <returns></returns>
std::vector<std::string> LeagueClientScreen::match_keywords(const std::string& user_input)
{
	std::vector<std::string> matched_keywords {};
	
	std::vector<std::string> splitted_input;
	splitted_input = StringHelper::split_by_delimiter(user_input, ' ', splitted_input);

	for (int i = 0; i < splitted_input.size(); i++)
		std::cout << "Splitted input at index " << i << ": " << splitted_input[i] << std::endl;

	const char* const* keywords = this->get_spanish_keywords();

	std::cout << "" << std::endl;
	for (const auto word : splitted_input) {
		std::cout << "" << std::endl;
		std::cout << "Comparing: " << word << std::endl;
		for (int i = 0; i < 7; i++) {
			std::cout << " with: " << keywords[i] << std::endl;
			if ( strcmp(keywords[i], word.c_str()) == 0 ) {
				std::cout << "\t Match founded!" << std::endl;
				matched_keywords.push_back(keywords[i]);
			}
		}
	}

	return matched_keywords;
}


/**
* Getters for the keyword identifiers
*/
const char* const* LeagueClientScreen::get_english_keywords()
{
	return english_keywords;
}

const char* const* MainScreen::get_english_keywords()
{
	return english_keywords;
}

const char* const* ChooseGame::get_english_keywords()
{
	return english_keywords;
}


const char* const* LeagueClientScreen::get_spanish_keywords()
{
	return spanish_keywords;
}

const char* const* MainScreen::get_spanish_keywords()
{
	return spanish_keywords;
}

const char* const* ChooseGame::get_spanish_keywords()
{
	return spanish_keywords;
}




/**
* Getters for the size of the arrays that contains the keyword identifiers
*/
const size_t LeagueClientScreen::get_english_array_size()
{
	return english_array_size;
}

const size_t LeagueClientScreen::get_spanish_array_size()
{
	return spanish_array_size;
}

const size_t MainScreen::get_english_array_size()
{
	return english_array_size;
}

const size_t MainScreen::get_spanish_array_size()
{
	return spanish_array_size;
}

const size_t ChooseGame::get_english_array_size()
{
	return english_array_size;
}

const size_t ChooseGame::get_spanish_array_size()
{
	return spanish_array_size;
}


/**
* Default constructors
*/
LeagueClientScreen::LeagueClientScreen() : identifier{ LeagueClientScreenIdentifier::MainScreen } {}

MainScreen::MainScreen() {}

ChooseGame::ChooseGame() {}

