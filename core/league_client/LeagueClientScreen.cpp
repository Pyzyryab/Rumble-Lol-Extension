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

/// <summary>
/// Matches an object instance keywords property (keywords are what identifies the actions available 
/// for a concrete LeagueClientScreen child type), returning the coincident ones
/// </summary>
/// <returns></returns>
std::vector<std::string> LeagueClientScreen::matched_keywords(const std::string& user_input)
{
	std::vector<std::string> matched_keywords{};
	std::vector<std::string> splitted_input = StringHelper::split_by_delimiter(user_input, ' ', matched_keywords);

	for (const auto word : splitted_input)
	{
		// TODO pending to decide if member methods should be std::vector<string> or remains as const char*
		//if (std::binary_search(this->spanish_keywords.begin(), this->spanish_keywords.end(), word))
		for (int i = 0; i < sizeof(this->spanish_keywords); i++)
			if (word.data() == this->spanish_keywords[i])
				matched_keywords.push_back(word);
		std::cout << "Matched keywords: " << word << std::endl;

		return matched_keywords;
	}

	return matched_keywords;
}

const char* const* LeagueClientScreen::get_english_keywords()
{
	return english_keywords;
}

const char* const* MainScreen::get_english_keywords()
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

/**
* Default constructors
*/
LeagueClientScreen::LeagueClientScreen() : identifier{ LeagueClientScreenIdentifier::MainScreen } {}
MainScreen::MainScreen() {}