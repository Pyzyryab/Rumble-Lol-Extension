#pragma once

/// <summary>
/// The enum representation of the name of a League of Legends client. This is a convenient way of avoid
/// the use of raw char* or std::strings to match a property.
/// </summary>
enum class LeagueClientScreenIdentifier {
	MainScreen, ChooseGame, FindGame, AcceptDecline, ChampSelect
};  // TODO Complete. Should be on the global namespace?

/// <summary>
/// **Base class** that represents any of the existing screens on the League of Legends client.
/// Used to store as much information it's necessary to complete the desired user request.
/// </summary>
class LeagueClientScreen
{
	public:
		// Constructor
		LeagueClientScreen(LeagueClientScreenIdentifier identifier);
		
		// Methods
		LeagueClientScreenIdentifier get_identifier();
		void set_identifier(const LeagueClientScreenIdentifier& identifier);

	private:
		// Stores the window's name as an enum variant
		LeagueClientScreenIdentifier identifier;
};