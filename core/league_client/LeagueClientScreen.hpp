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
	MainScreen, ChooseGame, AcceptDecline, ChampSelect
};  // TODO Complete. Should be on the global namespace?

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& Str, LeagueClientScreenIdentifier lcsi) {
	switch (lcsi) {
		case LeagueClientScreenIdentifier::MainScreen: return Str << "Main screen"; break;
		case LeagueClientScreenIdentifier::ChooseGame: return Str << "Game selection"; break;
		case LeagueClientScreenIdentifier::AcceptDecline: return Str << "Accept / decline"; break;
		case LeagueClientScreenIdentifier::ChampSelect: return Str << "Champ select"; break;
	};
}

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
		virtual std::vector<std::string> match_keywords(const std::string& user_input);
		
};

class MainScreen : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier league_client_screen_identifier =
			LeagueClientScreenIdentifier::MainScreen;

		static const size_t english_array_size = 10;
		static const size_t spanish_array_size = 10;

		static constexpr const char* english_keywords[english_array_size]{
			// Main screen, etc.
		};

		static constexpr const char* spanish_keywords[spanish_array_size] {
			"inicio", "jugar", "tft", "clash", "perfil", "collección", "botín", "tu tienda", "tienda" // Pantalla principal
		};
	
	public:
		MainScreen();

		LeagueClientScreenIdentifier get_identifier();

		const char* const* get_english_keywords();
		const char* const* get_spanish_keywords();

		const size_t get_english_array_size();
		const size_t get_spanish_array_size();

};


class ChooseGame : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier league_client_screen_identifier =
			LeagueClientScreenIdentifier::ChooseGame;

		static const size_t english_array_size = 10;
		static const size_t spanish_array_size = 10;

		static constexpr const char* english_keywords[english_array_size]{
			// Main screen, etc.
		};

		static constexpr const char* spanish_keywords[spanish_array_size]{
			"normal", "ranked", "aram", // Modos de partidas
		};

	public:
		ChooseGame();

		LeagueClientScreenIdentifier get_identifier();

		const char* const* get_english_keywords();
		const char* const* get_spanish_keywords();

		const size_t get_english_array_size();
		const size_t get_spanish_array_size();

};