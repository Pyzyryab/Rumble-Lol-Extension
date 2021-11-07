#pragma once

#include <vector>
#include <tuple>

#include "../helpers/EnumTypes.hpp"
#include "../core/league_client/LeagueClientButton.hpp"

using namespace std;

namespace RLE_data {

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
		
		// Summoner's Rift buttons
		make_tuple("blind", "blind_pick", LeagueClientScreenIdentifier::SummonersBlindLobby),
		make_tuple("draft", "draft_pick", LeagueClientScreenIdentifier::AramLobby),
		make_tuple("ranked", "ranked_solo_duo", LeagueClientScreenIdentifier::SummonersRankedLobby),
		make_tuple("flex", "flex", LeagueClientScreenIdentifier::SummonersFlexLobby),
		
		// Aram buttons aren't necessary, there is just one option
		
		// TFT Buttons 
		make_tuple("normal", "tft_normal", LeagueClientScreenIdentifier::TFT_NormalLobby),
		make_tuple("ranked", "tft_ranked", LeagueClientScreenIdentifier::TFT_RankedLobby),
		make_tuple("hyper", "tft_hyper_roll", LeagueClientScreenIdentifier::TFT_HyperRollLobby),

		// Urf buttons aren't necessary, there is just one option
		
		// Find Game - Cancel queue - Confirm action
		make_tuple("find", "find_game", LeagueClientScreenIdentifier::AcceptDecline),
		make_tuple("go", "confirm_button", LeagueClientScreenIdentifier::GameLobby),
		make_tuple("cancel", "cancel_button", LeagueClientScreenIdentifier::MainScreen),
	};

	vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> spanish_buttons{
		// TODO Just change it for the spanish correct definitions
	};

	/**
	* Helper that returns a vector of ClientButton pointers, filled with the concretes one that satisfies the
	* specified desired language.
	* 
	* // TODO Complete the full description of what this method does, and why it's designed in this way
	*/
	vector<ClientButton*> get_buttons(const Language language)
	{

		vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> desired_group_buttons{};
		vector<ClientButton*> api_buttons;

		// Selectes the buttons based on the language. Moves them to a new container to avoid dangling references caused by std::tuple
		switch (language)
		{
			case Language::English:
				for (auto element : english_buttons)
					desired_group_buttons.push_back(element);
				break;
			case Language::Spanish:
				for (auto element : spanish_buttons)
					desired_group_buttons.push_back(element);
				break;
			default:
				for (auto element : english_buttons)
					desired_group_buttons.push_back(element);
		};


		// Creates a new button object, storing in a vector a raw pointer to the instance
		for (auto &tuple : desired_group_buttons) {
			api_buttons.push_back(
				new ClientButton(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple), language)
			);
		}

		return api_buttons;
	}


}