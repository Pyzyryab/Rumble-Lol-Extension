#pragma once

#include <string>

#include <rumble_lol_plugin/league_client/screen_identifier.hpp>

/// Aggregate type for hold the metainformation of a clickable button
/// of the League of Legends game client
struct ClientButton
{
	std::string identifier; // TODO see if string view is viable
	std::string image_path;
	// When clicked, informs about what screen will follows the current one
	LeagueClientScreenIdentifier next_screen;
	Language selected_language;
	// In case of the button belongs to a lobby, stores here what lobby will lead after press the "Confirm" button
	LeagueClientScreenIdentifier lobby; 
};
