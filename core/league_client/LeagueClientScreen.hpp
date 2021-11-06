#pragma once

#include <string>
#include <vector>
#include <array>

#include "LeagueClientButton.hpp"
#include "../../helpers/EnumTypes.hpp"

/// <summary>
/// **Base class** that represents any of the existing screens on the League of Legends client.
/// Used to store as much information it's necessary to complete the desired user request.
/// </summary>
class LeagueClientScreen
{
	private:
		// Stores the window's name as an enum variant
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Base;

		// The current selected language of this API
		const Language& selected_language;

		// Dynamic container for store pointers to the client buttons objects
		std::vector<ClientButton*> client_buttons { };

	public:
		// Factory static method 
		static LeagueClientScreen* factory_screen(const LeagueClientScreenIdentifier& screen_identifier);

		// Constructors
		LeagueClientScreen();
		LeagueClientScreen(const Language& language);

		// Destructor
		virtual ~LeagueClientScreen();
		
		// Getters
		virtual LeagueClientScreenIdentifier get_identifier();
		virtual std::vector<ClientButton*> get_client_buttons();
		virtual const Language& get_selected_language();

		// Methods
		std::vector<ClientButton*> find_client_button(const std::string& user_input);
		
};

class MainScreen : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::MainScreen;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons {};
	
	public:
		MainScreen();
		MainScreen(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};


class ChooseGame : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::ChooseGame;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		ChooseGame();
		ChooseGame(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};


class TFT : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::TFT;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		TFT();
		TFT(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};


class Clash : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Clash;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		Clash();
		Clash(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};

class Profile : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Profile;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		Profile();
		Profile(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};

class Collection : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Collection;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		Collection();
		Collection(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};

class Loot : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Loot;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		Loot();
		Loot(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};


class YourShop : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::YourShop;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		YourShop();
		YourShop(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};

class Store : public LeagueClientScreen
{
	private:
		static const LeagueClientScreenIdentifier identifier = LeagueClientScreenIdentifier::Store;
		const Language& selected_language;
		std::vector<ClientButton*> client_buttons{};

	public:
		Store();
		Store(const Language& language);

		LeagueClientScreenIdentifier get_identifier();
		std::vector<ClientButton*> get_client_buttons() override;
		virtual const Language& get_selected_language() override;

};
