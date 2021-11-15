#pragma once

#include <string>

#include "../../helpers/EnumTypes.hpp"

struct ClientButton
{
	const char* identifier;
	std::string image_path;
	// When clicked, informs about what screen will follows the current one
	const LeagueClientScreenIdentifier next_screen;
	const Language selected_language;
	// In case of the button belongs to a lobby, stores here what lobby will lead after press the "Confirm" button
	const LeagueClientScreenIdentifier lobby; 


	// Base constructor
	ClientButton(
		const char* identifier, 
		const char* image_path, 
		const LeagueClientScreenIdentifier lcsi, 
		const Language selected_language
	);

	// Overloaded constructor for design buttons that points towards lobby screens
	ClientButton(
		const char* identifier,
		const char* image_path,
		const LeagueClientScreenIdentifier lcsi,
		const Language selected_language,
		const LeagueClientScreenIdentifier lobby
	);
};
