#include <string.h>
#include <ostream>
#include <iostream>

#include "LeagueClientButton.hpp"
#include "../../helpers/EnumTypes.hpp"
 

ClientButton::ClientButton(const char* identifier, const char* image_path, const LeagueClientScreenIdentifier next_screen, const Language selected_language)
	: identifier{ identifier }, image_path{ image_path }, next_screen{ next_screen }, selected_language{ selected_language }
{
	std::string base_path {};
	std::string image_extension { ".jpg" };

	switch (selected_language)
	{
		case Language::English:
			base_path = "../assets/EN/";
			break;
		case Language::Spanish:
			base_path = "../assets/SP/";
			break;
		default:
			base_path = "../assets/EN/";
			break;
	};

	base_path.append(image_path).append(image_extension);
	this->image_path = base_path;
}

