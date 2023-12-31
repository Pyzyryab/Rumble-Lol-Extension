#pragma once

#include <string>

#include <rumble_lol_plugin/league_client/screen_identifier.hpp>

/// Aggregate type for hold the meta-information of a clickable button
/// of the League of Legends game client
struct ClientButton
{
	std::string identifier; // TODO see if string view is viable
	std::string image_path;
	// When clicked, informs about what screen will follow the current one
	LeagueClientScreenIdentifier next_screen;
	Language selected_language;
	// In case of the button belongs to a lobby, stores here what lobby will lead after press the "Confirm" button
	LeagueClientScreenIdentifier lobby; 
};

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& oss, ClientButton rhs) {
	return oss << "ClientButton[\n" 
		<< "	Identifier: " << rhs.identifier << "\n"
		<< "	Path: " << rhs.image_path << "\n"
		<< "	Next Screen: " << rhs.next_screen << "\n"
		<< "	Language: " << rhs.selected_language << "\n"
		<< "	Lobby: " << rhs.lobby << "\n"
		<< "]\n";
}
