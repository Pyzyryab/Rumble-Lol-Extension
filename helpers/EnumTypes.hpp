#pragma once
#include <ostream>

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
	Base, // Default, just for initialization before the real init one
	// Represents an status, more than a screen, after the user closes the client or logged out
	ClientClosed,
	// Control variant that allows to create the ability to recover the last screen when the action it's not linear
	PreviousScreen,
	// When the action does not leads to a screen change
	SameScreen,
	// Special actions
	CancelAction,
	// Client main screen. Home.
	MainScreen,
	// NavBar options
	ChooseGame,  // Play button
	TFT, Clash,
	Profile, Collection, Loot, YourShop, Store,
	
	// Lobbies
	NoLobby, // Just fill the info about buttons that don't lead to a lobby
	GameLobby, // Generic one, a kind of wildcard to set the correct one based on the last user input before "GO (Confirm button)"
	// Summoners Rift game modes
	SummonersBlindLobby, SummonersDraftLobby, SummonersRankedLobby, SummonersFlexLobby,
	// Aram
	AramLobby,
	// TFT
	TFT_NormalLobby, TFT_RankedLobby, TFT_HyperRollLobby,
	// URF
	UrfLobby,
	// Training lobbies
	TutorialLobby, 
	PracticeTool,

	// Special screens or screens with special actions
	AcceptDecline, 
	ChampSelect
};

/// Overload the output stream operator for the LeagueClientScreenIdentifier custom type
inline std::ostream& operator<<(std::ostream& Str, LeagueClientScreenIdentifier lcsi) {
	switch (lcsi) {
		case LeagueClientScreenIdentifier::Base: return Str << "Base"; break;
		case LeagueClientScreenIdentifier::ClientClosed: return Str << "Client closed"; break;

		case LeagueClientScreenIdentifier::PreviousScreen: return Str << "Previous screen"; break;
		case LeagueClientScreenIdentifier::SameScreen: return Str << "Same screen"; break;

		case LeagueClientScreenIdentifier::MainScreen: return Str << "Main screen"; break;
		case LeagueClientScreenIdentifier::ChooseGame: return Str << "Game selection"; break;
		case LeagueClientScreenIdentifier::TFT: return Str << "TFT screen"; break;
		case LeagueClientScreenIdentifier::Clash: return Str << "Clash screen"; break;
		case LeagueClientScreenIdentifier::Profile: return Str << "Profile screen"; break;
		case LeagueClientScreenIdentifier::Collection: return Str << "Collection screen"; break;
		case LeagueClientScreenIdentifier::Loot: return Str << "Loot screen"; break;
		case LeagueClientScreenIdentifier::YourShop: return Str << "Your shop screen"; break;
		case LeagueClientScreenIdentifier::Store: return Str << "Store screen"; break;
		case LeagueClientScreenIdentifier::GameLobby: return Str << "Game Lobby identifier"; break;
		case LeagueClientScreenIdentifier::NoLobby: return Str << "No Lobby"; break;

		case LeagueClientScreenIdentifier::SummonersBlindLobby: return Str << "Summoners Rift Blind Pick option pointed"; break;
		case LeagueClientScreenIdentifier::SummonersDraftLobby: return Str << "Summoners Rift Draft Pick option pointed"; break;
		case LeagueClientScreenIdentifier::SummonersRankedLobby: return Str << "Summoners Ranked Solo / D�o option pointed"; break;
		case LeagueClientScreenIdentifier::SummonersFlexLobby: return Str << "Summoners Rift Ranked Flex option pointed"; break;
		case LeagueClientScreenIdentifier::AramLobby: return Str << "Aram option pointed"; break;
		case LeagueClientScreenIdentifier::TFT_NormalLobby: return Str << "TFT Normal option pointed"; break;
		case LeagueClientScreenIdentifier::TFT_RankedLobby: return Str << "TFT Ranked option pointed"; break;
		case LeagueClientScreenIdentifier::TFT_HyperRollLobby: return Str << "TFT Hyper Roll option pointed"; break;
		case LeagueClientScreenIdentifier::UrfLobby: return Str << "URF option pointed"; break;

		case LeagueClientScreenIdentifier::AcceptDecline: return Str << "Accept / decline"; break;
		case LeagueClientScreenIdentifier::ChampSelect: return Str << "Champ select"; break;

		default: return Str << "No coincident one"; break;
	};
}