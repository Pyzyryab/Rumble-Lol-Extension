#pragma once

#include <vector>
#include <iostream>

#include <rumble_lol_plugin/league_client/button.hpp>
#include <rumble_lol_plugin/league_client/screen_identifier.hpp>

using namespace std;


/**
 * @brief 
 * Place for store all the available data for the API.
 * 
 * TODO Notate how in the future, this should be replaced by a REST API data supplier, 
 * where we can retrieve data dynamically from every patch, every client aspect change
 * with posible new buttons etc.
 */
namespace RLE_data {

	/**
	 * Represents all the game lobbies available in the API, this means,
	 * every lobby screen that the user can access by voice control
	 */
	const size_t available_client_lobbies = 9;

	const LeagueClientScreenIdentifier lobbies [available_client_lobbies] {
		LeagueClientScreenIdentifier::SummonersBlindLobby,
		LeagueClientScreenIdentifier::SummonersDraftLobby,
		LeagueClientScreenIdentifier::SummonersRankedLobby,
		LeagueClientScreenIdentifier::SummonersFlexLobby,
		LeagueClientScreenIdentifier::AramLobby,
		LeagueClientScreenIdentifier::TFT_NormalLobby,
		LeagueClientScreenIdentifier::TFT_RankedLobby,
		LeagueClientScreenIdentifier::TFT_HyperRollLobby,
		LeagueClientScreenIdentifier::UrfLobby,
	};

	/**
	* The available buttons to use with this API against the League of Legends client with the League
	*/
	vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> english_buttons {
		// Navbar buttons
		make_tuple("home", "home_button", LeagueClientScreenIdentifier::MainScreen),
		make_tuple("play", "play_button", LeagueClientScreenIdentifier::ChooseGame),
		make_tuple("tft", "tft_button", LeagueClientScreenIdentifier::TFT),
		make_tuple("clash", "clash_button", LeagueClientScreenIdentifier::Clash),
		make_tuple("profile", "profile_button", LeagueClientScreenIdentifier::Profile),
		make_tuple("collection", "collection_button", LeagueClientScreenIdentifier::Collection),
		make_tuple("loot", "loot_button", LeagueClientScreenIdentifier::Loot),
		make_tuple("your shop", "your_shop_button", LeagueClientScreenIdentifier::YourShop),
		make_tuple("store", "store_button", LeagueClientScreenIdentifier::Store),
		
		// Choose Game options
		make_tuple("summoners", "summoners_rift", LeagueClientScreenIdentifier::SummonersBlindLobby),
		make_tuple("aram", "aram", LeagueClientScreenIdentifier::AramLobby),
		make_tuple("tft", "teamfight_tactics", LeagueClientScreenIdentifier::TFT_NormalLobby),
		make_tuple("urf", "urf", LeagueClientScreenIdentifier::UrfLobby),

		// Ranked and draft modes position picker
		make_tuple("primary", "primary", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("secondary", "secondary", LeagueClientScreenIdentifier::GameLobby),
		
		// Roles
		make_tuple("top", "top_role", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("jungler", "jungler_role", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("mid", "mid_role", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("bot", "bot_role", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("support", "support_role", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("fill", "autofill_role", LeagueClientScreenIdentifier::GameLobby),

		// Summoner's Rift buttons
		make_tuple("blind", "blind_pick", LeagueClientScreenIdentifier::SummonersBlindLobby),
		make_tuple("draft", "draft_pick", LeagueClientScreenIdentifier::SummonersDraftLobby),
		make_tuple("ranked", "ranked_solo_duo", LeagueClientScreenIdentifier::SummonersRankedLobby),
		make_tuple("flex", "flex", LeagueClientScreenIdentifier::SummonersFlexLobby),
		
		// Aram buttons aren't necessary, there is just one option
		
		// TFT Buttons 
		make_tuple("normal", "tft_normal", LeagueClientScreenIdentifier::TFT_NormalLobby),
		make_tuple("ranked", "tft_ranked", LeagueClientScreenIdentifier::TFT_RankedLobby),
		make_tuple("hyper", "tft_hyper_roll", LeagueClientScreenIdentifier::TFT_HyperRollLobby),

		// Urf buttons aren't necessary, there is just one option

		// Training. Contains the "start now" from tutorial and "start game" from the practice tool
		make_tuple("training", "training", LeagueClientScreenIdentifier::ChooseGame),
		make_tuple("tutorial", "tutorial", LeagueClientScreenIdentifier::TutorialLobby),
		make_tuple("practice", "practice", LeagueClientScreenIdentifier::PracticeTool),
		make_tuple("start", "start", LeagueClientScreenIdentifier::GameLobby),
		// TODO Pending implement the add bot functionality, or a handler to the same modal
		// Join button from the team making screen
		make_tuple("join", "join_game", LeagueClientScreenIdentifier::GameLobby),

		// Find Game - Cancel queue - Confirm action
		make_tuple("find", "find_game", LeagueClientScreenIdentifier::AcceptDecline),
		make_tuple("accept", "accept_match", LeagueClientScreenIdentifier::ChampSelect),
		make_tuple("decline", "decline_match", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("go", "confirm_button", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("cancel", "cancel_button", LeagueClientScreenIdentifier::CancelAction),

		// Champ select buttons
		make_tuple("finder", "search_bar", LeagueClientScreenIdentifier::ChampSelect),
		make_tuple("editor", "runes_editor", LeagueClientScreenIdentifier::ChampSelect),
		make_tuple("picker", "runes_picker", LeagueClientScreenIdentifier::ChampSelect),
		make_tuple("lock", "lock_in", LeagueClientScreenIdentifier::ChampSelect),

		// Binary decision modals
		make_tuple("exit", "exit", LeagueClientScreenIdentifier::ClientClosed),
		make_tuple("sign out", "sign_out", LeagueClientScreenIdentifier::ClientClosed),
		make_tuple("yes", "yes", LeagueClientScreenIdentifier::ClientClosed),
		make_tuple("no", "no", LeagueClientScreenIdentifier::ClientClosed),
		make_tuple("close", "close", LeagueClientScreenIdentifier::ClientClosed),
	};

	vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> spanish_buttons{
		// TODO Just change it for the spanish correct definitions
	};

	std::string add_assets_route(const std::string& image_path, const Language language = Language::English) {
		std::string base_path{ "../assets/" };
		std::string image_extension{ ".jpg" };

		switch (language)
		{
			case Language::English:
				base_path.append("EN");
				break;
			case Language::Spanish:
				base_path.append("SP");
				break;
			default:
				base_path.append("EN");
		};

		base_path.append("/").append(image_path).append(image_extension);
		return base_path;
	}



	/**
	* Helper that returns a vector of ClientButton aggregates
	*/
	vector<ClientButton> get_buttons(const Language language, const bool debug = false)
	{
		vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> desired_group_buttons{};
		vector<ClientButton> api_buttons;

		// Selects the buttons based on the language. Moves them to a new container to avoid dangling references caused by std::tuple
		switch (language)
		{
			case Language::English:
				for (auto &element : english_buttons)
					desired_group_buttons.push_back(element); // TODO emplace_back them all
				break;
			case Language::Spanish:
				for (auto &element : spanish_buttons)
					desired_group_buttons.push_back(element);
				break;
			default:
				for (auto &element : english_buttons)
					desired_group_buttons.push_back(element);
		};


		// Creates a new button object, storing in a vector a raw pointer to the instance
		for (auto &tuple : desired_group_buttons) {
			
			const LeagueClientScreenIdentifier* lcsi = std::find(
				std::begin(lobbies), std::end(lobbies), std::get<2>(tuple)
			);

			const auto identifier = std::get<0>(tuple);
			const auto path = add_assets_route(std::get<1>(tuple), language);

			if (lcsi != std::end(lobbies)) {
				const auto but = ClientButton {
						identifier,
						path,
						LeagueClientScreenIdentifier::ChooseGame, 
						language, 
						std::get<2>(tuple)
					};
				cout << "Generated button: " << but << endl;
				api_buttons.push_back(
					but
				);
			} else {
				const auto but = ClientButton {
						identifier, 
						path,
						std::get<2>(tuple),
						language,
						LeagueClientScreenIdentifier::NoLobby,
					};
				cout << "Generated button [ELSE]: " << but << endl;
				api_buttons.push_back(
					but
				);
			}
		}

		if (debug) {
			for (ClientButton& button : api_buttons) {
				cout << "Button with identifier: " << button.identifier
					<< "; with path: " << button.image_path << endl;
				cout << "\tpointing to: " << button.next_screen
					<< " and belongs to: " << button.lobby << endl;
			}
		}

		return api_buttons;	
	}


	// ClientButton::ClientButton(
	// 	const char* identifier,
	// 	const char* image_path,
	// 	const LeagueClientScreenIdentifier next_screen,
	// 	const Language selected_language,
	// 	const LeagueClientScreenIdentifier lobby
	// )
	// 	: identifier{ const_cast<char*>(identifier)  }, 
	// 	image_path{ image_path }, 
	// 	next_screen{ next_screen }, 
	// 	selected_language{ selected_language },
	// 	lobby{ lobby }
	
}