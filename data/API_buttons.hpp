#pragma once

#include <vector>
#include <tuple>

#include "../helpers/EnumTypes.hpp"
#include "../core/league_client/LeagueClientButton.hpp"

using namespace std;

namespace RLE_data {

	/**
	* Helper that returns a vector of ClientButton pointers, filled with the concretes one that satisfies the
	* specified desired language
	*/
	vector<ClientButton*> get_buttons(const Language language)
	{

		/**
		* The available buttons to use with this API against the League of Legends client with the League
		*/
		vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> english_buttons{
			make_tuple("home", "home_button", LeagueClientScreenIdentifier::MainScreen),
			// Available on the main screen
			make_tuple("play", "play_button", LeagueClientScreenIdentifier::ChooseGame),
			make_tuple("tft", "tft_button", LeagueClientScreenIdentifier::TFT),
			make_tuple("clash", "clash_button", LeagueClientScreenIdentifier::Clash),
			make_tuple("profile", "profile_button", LeagueClientScreenIdentifier::Profile),
			make_tuple("collection", "collection_button", LeagueClientScreenIdentifier::Collection),
			make_tuple("loot", "loot_button", LeagueClientScreenIdentifier::Loot),
			make_tuple("your shop", "your_shop_button", LeagueClientScreenIdentifier::YourShop),
			make_tuple("store", "store_button", LeagueClientScreenIdentifier::Store)
		};

		vector<tuple<const char*, const char*, const LeagueClientScreenIdentifier>> spanish_buttons{
			// TODO Just change it for the spanish correct definitions
		};

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