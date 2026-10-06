// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00445086 (184 B, jump table of 13 slots at 0x0044513E after it):
// the debug name of a LAN lobby client state, returned by value and
// defaulting to "Unknown state". No direct caller, so the owner is unknown
// and the name is the address's.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/GUI/
// Rva00517720ClientStateName.cpp (f57439f7f4), whose twelve state strings
// retail references here in the same order (0x00C3E274..0x00C3E194).
// Target facts: retail's table has 13 slots and slot 11 goes to the default
// exit, so BFME2 inserted a state before CS_GAME_STARTED that has no name
// case; the strings are set through the rowed StringBase<char>::set 0x000055F5.

#include "ascii_string.h"

enum Rva00445086ClientState
{
	CS_INIT,
	CS_LOBBY_ACTIVE,
	CS_HOST_SETUP_REQUEST,
	CS_HOST_SETUP_WAIT,
	CS_HOST_SETUP_ACTIVE,
	CS_HOST_START_REQUEST,
	CS_HOST_START_WAIT,
	CS_JOIN_SETUP_REQUEST,
	CS_JOIN_SETUP_WAIT,
	CS_JOIN_ACTIVE,
	CS_JOIN_ACCEPT_WAIT,
	CS_UNNAMED_11, // target-only state: its table slot takes the default exit
	CS_GAME_STARTED,
};

AsciiString Rva00445086ClientStateName(Rva00445086ClientState state)
{
	AsciiString name("Unknown state");
	switch (state)
	{
		case CS_INIT: name = "CS_INIT"; break;
		case CS_LOBBY_ACTIVE: name = "CS_LOBBY_ACTIVE"; break;
		case CS_HOST_SETUP_REQUEST: name = "CS_HOST_SETUP_REQUEST"; break;
		case CS_HOST_SETUP_WAIT: name = "CS_HOST_SETUP_WAIT"; break;
		case CS_HOST_SETUP_ACTIVE: name = "CS_HOST_SETUP_ACTIVE"; break;
		case CS_HOST_START_REQUEST: name = "CS_HOST_START_REQUEST"; break;
		case CS_HOST_START_WAIT: name = "CS_HOST_START_WAIT"; break;
		case CS_JOIN_SETUP_REQUEST: name = "CS_JOIN_SETUP_REQUEST"; break;
		case CS_JOIN_SETUP_WAIT: name = "CS_JOIN_SETUP_WAIT"; break;
		case CS_JOIN_ACTIVE: name = "CS_JOIN_ACTIVE"; break;
		case CS_JOIN_ACCEPT_WAIT: name = "CS_JOIN_ACCEPT_WAIT"; break;
		case CS_GAME_STARTED: name = "CS_GAME_STARTED"; break;
	}
	return name;
}
