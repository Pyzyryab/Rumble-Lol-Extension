#include <string.h>
#include <ostream>
#include <iostream>

#include "LeagueClientButton.hpp"
#include "../../helpers/EnumTypes.hpp"
 

/// Four parameters delegating constructor
ClientButton::ClientButton(
	const char* identifier, 
	const char* image_path, 
	const LeagueClientScreenIdentifier next_screen, 
	const Language selected_language,
	const bool is_waiting_button
)
	: ClientButton::ClientButton { 
		identifier, 
		image_path, 
		LeagueClientScreenIdentifier::NoLobby,
		next_screen, 
		selected_language,
		is_waiting_button
	} {}


/// Normal use-case constructor
ClientButton::ClientButton(
	const char* identifier,
	const char* image_path,
	const LeagueClientScreenIdentifier lobby,
	const LeagueClientScreenIdentifier next_screen,
	const Language selected_language,
	const bool is_waiting_button
)
	: identifier { const_cast<char*>(identifier) }, 
	image_path { image_path },
	lobby { lobby }, 
	next_screen { next_screen }, 
	selected_language { selected_language },
	is_waiting_button { is_waiting_button }
{
	std::string base_path{ "../assets/" };
	std::string image_extension{ ".jpg" };

	switch (selected_language)
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
	this->image_path = base_path;
}

// Copy constructor
ClientButton::ClientButton(const ClientButton &source)
	// Shallow copy for non pointer variables
	: image_path { source.image_path },
	lobby { source.lobby }, 
	next_screen { source.next_screen }, 
	selected_language { source.selected_language },
	is_waiting_button { source.is_waiting_button }
{
	// Deep copy of the raw char* pointer
	identifier = new char[ strlen(source.identifier) + 1 ];
	strcpy(identifier, source.identifier);

	std::cout << "[Warning]  - Copy constructor called for " << identifier << std::endl;
}

// Move constructor
ClientButton::ClientButton(ClientButton &&source) noexcept
	: identifier { source.identifier },
	image_path { source.image_path },
	next_screen { source.next_screen },
	selected_language { source.selected_language },
	lobby { source.lobby},
	is_waiting_button { source.is_waiting_button }
{
	// Now we null the raw pointer that contains the moved data from the another resource
	source.identifier = nullptr;
	std::cout << "[Info] - Move constructor called for " << identifier << std::endl;
}

// Destructor 
ClientButton::~ClientButton()
{
	// Just debugging if we are correctly using the move constructor.
	if (identifier != nullptr)
	{
		std::cout << "Destructor freeing data for " << identifier << std::endl;
	}
	else 
	{
		std::cout << "Destructor freeing data for nullptr" << std::endl;
	}
}

// Copy assigment operator overload
ClientButton& ClientButton::operator=(const ClientButton &rhs)
{
	std::cout << "Using copy assignment" << std::endl;
	if (this == &rhs)
		return *this;

	this->identifier = new char[ std::strlen(rhs.identifier) + 1 ];
	std::strcpy( this->identifier, rhs.identifier );

	image_path = rhs.image_path;
	next_screen = rhs.next_screen;
	selected_language = rhs.selected_language;
	lobby = rhs.lobby;
	is_waiting_button = rhs.is_waiting_button;

	return *this;
}

// Move assignment operator overload
ClientButton& ClientButton::operator=(ClientButton &&rhs)
{
	std::cout << "Using move assignment" << std::endl;
	if (this == &rhs)
		return *this;

	delete [] this->identifier;

	// Moving the data and nulling the source
	identifier = rhs.identifier;
	rhs.identifier = nullptr;

	image_path = rhs.image_path;
	next_screen = rhs.next_screen;
	selected_language = rhs.selected_language;
	lobby = rhs.lobby;
	is_waiting_button = rhs.is_waiting_button;

	return *this;
}