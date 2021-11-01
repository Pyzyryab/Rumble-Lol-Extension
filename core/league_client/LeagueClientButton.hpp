#pragma once

#include <string>

#include "../../helpers/EnumTypes.hpp"

struct ClientButton
{
	const char* identifier;
	std::string image_path;
	const LeagueClientScreenIdentifier next_screen;
	const Language selected_language;

	// Constructor
	ClientButton(const char* identifier, const char* image_path, const LeagueClientScreenIdentifier lcsi, const Language selected_language);
};
