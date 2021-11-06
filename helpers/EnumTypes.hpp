#pragma once

// The availiable languages for the API as an enum type
enum class Language { English, Spanish };

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& Str, Language language) {
	switch (language) {
		case Language::English: return Str << "English"; break;
		case Language::Spanish: return Str << "Spanish"; break;
		default: return Str << "Unitialized attribute or corrupted data."; break;
	};
}


/// <summary>
/// The enum representation of the name of a League of Legends client. This is a convenient way of avoid
/// the use of raw char* or std::strings to match a property.
/// </summary>
enum class LeagueClientScreenIdentifier {
	Base, Unset, // Defaults
	
	// Control variant that allows to create the ability to recover the last screen when the action it's not linear
	PreviousScreen,
	// When the action does not leads to a screen change
	SameScreen,

	MainScreen,  // Client main screen. Home.
	ChooseGame,  // Play button
	TFT, Clash,
	Profile, Collection, Loot, YourShop, Store,
	// Lobbies
	GameLobby, // Generic one, a method will set the correct one based on the last user input before "GO"

	// Summoners Rift game modes
	SummonersBlindLobby, SummonersDraftLobby, SummonersRankedLobby, SummonersFlexLobby,
	// Aram
	AramLobby,
	// TFT
	TFT_NormalLobby, TFT_RankedLobby, TFT_HyperRollLobby,
	// URF
	UrfLobby,
	
	AcceptDecline, ChampSelect
};  // TODO Complete it.

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& Str, LeagueClientScreenIdentifier lcsi) {
	switch (lcsi) {
		case LeagueClientScreenIdentifier::Base: return Str << "Base"; break;
		case LeagueClientScreenIdentifier::PreviousScreen: return Str << "Previous screen"; break;
		case LeagueClientScreenIdentifier::SameScreen: return Str << "Same screen"; break;
		case LeagueClientScreenIdentifier::MainScreen: return Str << "Main screen"; break;
		case LeagueClientScreenIdentifier::ChooseGame: return Str << "Game selection"; break;
		case LeagueClientScreenIdentifier::AcceptDecline: return Str << "Accept / decline"; break;
		case LeagueClientScreenIdentifier::ChampSelect: return Str << "Champ select"; break;
		default: return Str << "No coincident one"; break;
	};
}