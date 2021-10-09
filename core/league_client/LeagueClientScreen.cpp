#include "LeagueClientScreen.hpp"

LeagueClientScreen::LeagueClientScreen(LeagueClientScreenIdentifier identifier)
	: identifier{ identifier } {}

LeagueClientScreenIdentifier LeagueClientScreen::get_identifier()
{
	return this->identifier;
}

void LeagueClientScreen::set_identifier(const LeagueClientScreenIdentifier& identifier)
{
	this->identifier = identifier;
}
