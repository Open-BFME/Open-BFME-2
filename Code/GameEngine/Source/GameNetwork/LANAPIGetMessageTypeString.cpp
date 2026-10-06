// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// GetMessageTypeString, retail 0x00449CAA (416 bytes): the LAN message-type
// debug describer. Target evidence: the twenty "LANMessage::MSG_*" name and
// description literals its jump table (0x00449E4A, cases 0..19) pushes for
// "%s(%d) %s" are byte-identical to Zero Hour's and Open-BFME-1's
// GetMessageTypeString (BFME1 retail 0x00685910); the default case formats
// "Unknown Message type %d".
// Ported from Open-BFME-1 game/GameEngine/Source/GameNetwork/lanapi.cpp.
// BFME 2 difference: value 14 has no case (it falls to the default), so
// MSG_GAME_START_TIMER and the later types are numbered 15..19 here.
// Callees: AsciiString::format (0x00038150), the StringBase<char> copy
// constructor (0x000365F0) and releaseBuffer (0x00036410).
typedef unsigned int UnsignedInt;
#include "ascii_string.h"

AsciiString GetMessageTypeString(UnsignedInt type)
{
	AsciiString returnString;

	enum BFMEMessageType
	{
		BFME_MSG_REQUEST_LOCATIONS = 0,
		BFME_MSG_GAME_ANNOUNCE = 1,
		BFME_MSG_LOBBY_ANNOUNCE = 2,
		BFME_MSG_REQUEST_JOIN = 3,
		BFME_MSG_JOIN_ACCEPT = 4,
		BFME_MSG_JOIN_DENY = 5,
		BFME_MSG_REQUEST_GAME_LEAVE = 6,
		BFME_MSG_REQUEST_LOBBY_LEAVE = 7,
		BFME_MSG_REQUEST_HOST_LEAVE = 8,
		BFME_MSG_SET_ACCEPT = 9,
		BFME_MSG_MAP_AVAILABILITY = 10,
		BFME_MSG_CHAT = 11,
		BFME_MSG_ENABLE_MPSETUP_UI = 12,
		BFME_MSG_GAME_START = 13,
		BFME_MSG_GAME_START_TIMER = 15,
		BFME_MSG_GAME_OPTIONS = 16,
		BFME_MSG_INACTIVE = 17,
		BFME_MSG_REQUEST_GAME_INFO = 18,
		BFME_MSG_GAME_OPTIONS_PACKED = 19
	};

	switch (type)
	{
		case BFME_MSG_REQUEST_LOCATIONS:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_LOCATIONS", type, "Hey, where is everybody?");
			break;
		case BFME_MSG_GAME_ANNOUNCE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_GAME_ANNOUNCE", type, "Here I am, and here's my game info!");
			break;
		case BFME_MSG_LOBBY_ANNOUNCE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_LOBBY_ANNOUNCE", type, "Hey, I'm in the lobby!");
			break;
		case BFME_MSG_REQUEST_JOIN:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_JOIN", type, "Let me in!  Let me in!");
			break;
		case BFME_MSG_JOIN_ACCEPT:
			returnString.format("%s(%d) %s", "LANMessage::MSG_JOIN_ACCEPT", type, "Okay, you can join.");
			break;
		case BFME_MSG_JOIN_DENY:
			returnString.format("%s(%d) %s", "LANMessage::MSG_JOIN_DENY", type, "Go away!  We don't want any!");
			break;
		case BFME_MSG_REQUEST_GAME_LEAVE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_GAME_LEAVE", type, "The joiner wants to leave the game");
			break;
		case BFME_MSG_REQUEST_LOBBY_LEAVE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_LOBBY_LEAVE", type, "I'm leaving the lobby");
			break;
		case BFME_MSG_REQUEST_HOST_LEAVE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_HOST_LEAVE", type, "The host wants to leave the game");
			break;
		case BFME_MSG_SET_ACCEPT:
			returnString.format("%s(%d) %s", "LANMessage::MSG_SET_ACCEPT", type, "I'm cool with everything as is.");
			break;
		case BFME_MSG_MAP_AVAILABILITY:
			returnString.format("%s(%d) %s", "LANMessage::MSG_MAP_AVAILABILITY", type, "I do / do not, have the map.");
			break;
		case BFME_MSG_CHAT:
			returnString.format("%s(%d) %s", "LANMessage::MSG_CHAT", type, "Just spouting my mouth off");
			break;
		case BFME_MSG_ENABLE_MPSETUP_UI:
			returnString.format("%s(%d) %s", "LANMessage::MSG_ENABLE_MPSETUP_UI", type, "Enable/Disable your MP setup screen. Showns 'Continue the game' message box.");
			break;
		case BFME_MSG_GAME_START:
			returnString.format("%s(%d) %s", "LANMessage::MSG_GAME_START", type, "Hold on, we're starting!");
			break;
		case BFME_MSG_GAME_START_TIMER:
			returnString.format("%s(%d) %s", "LANMessage::MSG_GAME_START_TIMER", type, "The game will start in N seconds");
			break;
		case BFME_MSG_GAME_OPTIONS:
			returnString.format("%s(%d) %s", "LANMessage::MSG_GAME_OPTIONS", type, "Here's some info about the game.");
			break;
		case BFME_MSG_INACTIVE:
			returnString.format("%s(%d) %s", "LANMessage::MSG_INACTIVE", type, "I've alt-tabbed out.  Unaccept me cause I'm a poo-flinging monkey.");
			break;
		case BFME_MSG_REQUEST_GAME_INFO:
			returnString.format("%s(%d) %s", "LANMessage::MSG_REQUEST_GAME_INFO", type, "For direct connect, get the game info from a specific IP Address");
			break;
		case BFME_MSG_GAME_OPTIONS_PACKED:
			returnString.format("%s(%d) %s", "LANMessage::MSG_GAME_OPTIONS_PACKED", type, "Here's all the info about the game, from the host.");
			break;
		default:
			returnString.format("Unknown Message type %d", type);
	}
	return returnString;
}
