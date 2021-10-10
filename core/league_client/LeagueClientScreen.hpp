#pragma once

#include <string>
#include <vector>
#include <array>

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

		// The constants for defining the primitives arrays capacity
		static const size_t english_array_size = 1;
		static const size_t spanish_array_size = 1;

		// Identifier per language
		static constexpr const char* english_keywords[english_array_size] {};
		static constexpr const char* spanish_keywords[spanish_array_size] {};

	public:
		// Factory static method 
		static LeagueClientScreen* factory_screen(const LeagueClientScreenIdentifier& screen_identifier);

		// Constructors
		LeagueClientScreen();
		LeagueClientScreen(LeagueClientScreenIdentifier identifier);
		
		// Getters and Setters
		virtual LeagueClientScreenIdentifier get_identifier();
		virtual void set_identifier(const LeagueClientScreenIdentifier& identifier);

		virtual const char* const* get_english_keywords();
		virtual const char* const* get_spanish_keywords();

		virtual const size_t get_english_array_size();
		virtual const size_t get_spanish_array_size();

		// Methods
		virtual std::vector<std::string> matched_keywords(const std::string& user_input);
		
};

class MainScreen : public LeagueClientScreen
{
	private:
		static const size_t english_array_size = 10;
		static const size_t spanish_array_size = 9;

		static constexpr const char* english_keywords[english_array_size]{
			// Main screen, etc.
		};

		static constexpr const char* spanish_keywords[spanish_array_size] {
			"inicio", "pantalla principal", "tft", "clash", "perfil", "collección", "botín", "tu tienda", "tienda" // Pantalla principal
		};
	
	public:
		MainScreen();

		const char* const* get_english_keywords();
		const char* const* get_spanish_keywords();

		const size_t get_english_array_size();
		const size_t get_spanish_array_size();

};