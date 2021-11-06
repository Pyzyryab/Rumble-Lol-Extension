#pragma once

#include <string>

#include "../../helpers/EnumTypes.hpp"

struct ClientButton
{
	const char* identifier;
	std::string image_path;
	//const LeagueClientScreenIdentifier belongs_to;  // The screen where the button belongs
	const LeagueClientScreenIdentifier next_screen; // When clicked, the screen that will follows the current one
	const Language selected_language;

	// Constructor
	ClientButton(
		const char* identifier, 
		const char* image_path, 
		const LeagueClientScreenIdentifier lcsi, 
		const Language selected_language
	);
};
