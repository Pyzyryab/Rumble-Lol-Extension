#pragma once

#include <string>
#include <vector>

#include "../../helpers/StringHelper.cpp"

/// <summary>
/// The enum representation of the name of a League of Legends client. This is a convenient way of avoid
/// the use of raw char* or std::strings to match a property.
/// </summary>
enum class LeagueClientScreenIdentifier {
	MainScreen, ChooseGame, FindGame, AcceptDecline, ChampSelect
};  // TODO Complete. Should be on the global namespace?

/// <summary>
/// **Base class** that represents any of the existing screens on the League of Legends client.
/// Used to store as much information it's necessary to complete the desired user request.
/// </summary>
class LeagueClientScreen
{
	private:
		// Stores the window's name as an enum variant
		LeagueClientScreenIdentifier identifier;

		// Identifier per language
		static constexpr const char* english_keywords[1] {};
		static constexpr const char* spanish_keywords[1] {};

	public:
		// Factory static method 
		static LeagueClientScreen* factory_screen(const LeagueClientScreenIdentifier& screen_identifier);

		// Constructors
		LeagueClientScreen();
		LeagueClientScreen(LeagueClientScreenIdentifier identifier);
		
		// Methods
		virtual LeagueClientScreenIdentifier get_identifier();
		virtual void set_identifier(const LeagueClientScreenIdentifier& identifier);
		virtual std::vector<std::string> matched_keywords(const std::string& user_input);

		// Getters for the keywords
		virtual const char* const* get_english_keywords();
		virtual const char* const* get_spanish_keywords();
		
};

class MainScreen : public LeagueClientScreen
{
	private:
		static constexpr const char* english_keywords[10]{
			// Main screen
		};

		static constexpr const char* spanish_keywords[9]{
			"inicio", "pantalla principal", "tft", "clash", "perfil", "collección", "botín", "tu tienda", "tienda" // Pantalla principal
		};
	
	public:
		MainScreen();

		const char* const* get_english_keywords();
		const char* const* get_spanish_keywords();

};