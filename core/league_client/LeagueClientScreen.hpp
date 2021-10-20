#pragma once

#include <string>
#include <vector>
#include <array>

#include "LeagueClientButton.cpp"
//#include "../../helpers/StringHelper.cpp"

/// <summary>
/// The enum representation of the name of a League of Legends client. This is a convenient way of avoid
/// the use of raw char* or std::strings to match a property.
/// </summary>
enum class LeagueClientScreenIdentifier {
	Base, MainScreen, ChooseGame, AcceptDecline, ChampSelect
};  // TODO Complete it.

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& Str, LeagueClientScreenIdentifier lcsi) {
	switch (lcsi) {
		case LeagueClientScreenIdentifier::Base: return Str << "Base"; break;
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
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Base;

		// The constants for defining the primitives arrays capacity
		static const size_t buttons_array_size = 1;

		// Identifier per language
		std::vector<ClientButton*> english_client_buttons { new ClientButton("no virtual", "base class") };
		std::vector<ClientButton*> spanish_client_buttons { new ClientButton("no virtual", "base class") };

	public:
		// Factory static method 
		static LeagueClientScreen* factory_screen(const LeagueClientScreenIdentifier& screen_identifier);

		// Constructors
		LeagueClientScreen();
		//LeagueClientScreen(LeagueClientScreenIdentifier identifier);
		
		// Getters and Setters
		virtual LeagueClientScreenIdentifier get_identifier();
		/*No setter needed nowadays!
			virtual void set_identifier(const LeagueClientScreenIdentifier& identifier);
		*/

		virtual std::vector<ClientButton*> get_english_client_buttons();
		virtual std::vector<ClientButton*> get_spanish_client_buttons();

		virtual const size_t get_buttons_array_size();

		// Methods
		std::vector<ClientButton*> find_client_button(const std::string& user_input);
		
};

class MainScreen : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::MainScreen;

		static const size_t buttons_array_size = 10;

		std::vector<ClientButton*> english_client_buttons {
			new ClientButton("play", "play_button"),
			new ClientButton("home", "home_button"),
			new ClientButton("tft", "tft_button"),
			new ClientButton("clash", "clash_button"),
			new ClientButton("profile", "profile_button"),
			new ClientButton("collection", "collection_button"),
			new ClientButton("loot", "loot_button"),
			new ClientButton("your_shop", "your_shop_button"),
			new ClientButton("shop", "shop_button")

		};

		std::vector<ClientButton*> spanish_client_buttons {
			new ClientButton("jugar", "boton_jugar"),
			new ClientButton("clash", "boton_clash")
		};
	
	public:
		MainScreen();

		LeagueClientScreenIdentifier get_identifier();

		std::vector<ClientButton*> get_english_client_buttons() override;
		std::vector<ClientButton*> get_spanish_client_buttons() override;

		const size_t get_buttons_array_size();

};


class ChooseGame : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::ChooseGame;

		static const size_t buttons_array_size = 10;

		std::vector<ClientButton*> english_client_buttons {
			new ClientButton("normal", "normal")
		};

		std::vector<ClientButton*> spanish_client_buttons {
			new ClientButton("normal", "normal"),
			new ClientButton("ranked", "ranked")
		};

	public:
		ChooseGame();

		LeagueClientScreenIdentifier get_identifier();

		std::vector<ClientButton*> get_english_client_buttons() override;
		std::vector<ClientButton*> get_spanish_client_buttons() override;

		const size_t get_buttons_array_size();

};