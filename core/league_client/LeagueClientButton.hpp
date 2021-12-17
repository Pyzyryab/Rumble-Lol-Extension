#pragma once

#include <string>

#include "../../helpers/EnumTypes.hpp"

struct ClientButton
{
	char* identifier;
	std::string image_path;
	// When clicked, informs about what screen will follows the current one
	LeagueClientScreenIdentifier next_screen;
	// Used to create the path where the needle image that identifies a desired button on a screen lives
	Language selected_language;
	// In case of the button belongs to a lobby, stores here what lobby will lead after press the "Confirm" button
	LeagueClientScreenIdentifier lobby; 
	// Control when the program should indefinitly wait for the button to appears on the screen or already should be
	// there and must be available to click
	bool is_waiting_button;


	// Base constructor
	ClientButton(
		const char* identifier, 
		const char* image_path, 
		const LeagueClientScreenIdentifier next_screen, 
		const Language selected_language,
		const bool is_waiting_button
	);

	// Overloaded constructor for design buttons that points towards lobby screens
	ClientButton(
		const char* identifier,
		const char* image_path,
		const LeagueClientScreenIdentifier lobby,
		const LeagueClientScreenIdentifier next_screen,
		const Language selected_language,
		const bool is_waiting_button
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
