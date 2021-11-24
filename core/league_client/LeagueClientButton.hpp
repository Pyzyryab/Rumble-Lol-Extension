#pragma once

#include <string>

#include "../../helpers/EnumTypes.hpp"

struct ClientButton
{
	char* identifier;
	std::string image_path;
	// When clicked, informs about what screen will follows the current one
	LeagueClientScreenIdentifier next_screen;
	Language selected_language;
	// In case of the button belongs to a lobby, stores here what lobby will lead after press the "Confirm" button
	LeagueClientScreenIdentifier lobby; 


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

	// Copy constructor
	ClientButton(const ClientButton &source);

	// Move constructor
	ClientButton(ClientButton &&source) noexcept;

	// Destructor
	~ClientButton();

	// Copy assignment operator overload
	ClientButton &operator=(const ClientButton &rhs);

	// Move assignment operator overload
	ClientButton &operator=(ClientButton &&rhs);
};
