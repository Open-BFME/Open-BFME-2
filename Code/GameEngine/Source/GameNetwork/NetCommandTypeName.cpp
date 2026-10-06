// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva005813D4Get@@YA?AVAsciiString@@H@Z, retail 0x005813D4, 471 bytes.
// Free function mapping NetCommandType int to its NETCOMMANDTYPE_* string.
// Identity from 2 callers at 0x004D5B7F 0x004D5BBC in 0x004D5B4C and the 29
// string literals in .rdata (FRAMEINFO 3 through SAVE_GAME 30, else UNKNOWN).
// Returns AsciiString by value: local set() at 0x000055F5, copy into hidden
// return pointer at 0x000365F0, local release at 0x00036410 with EH unwind.
#include "ascii_string.h"

AsciiString Rva005813D4Get(int type)
{
	AsciiString result;
	if (type == 3)
		result.set("NETCOMMANDTYPE_FRAMEINFO");
	else if (type == 5)
		result.set("NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY");
	else if (type == 6)
		result.set("NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY");
	else if (type == 4)
		result.set("NETCOMMANDTYPE_GAMECOMMAND");
	else if (type == 10)
		result.set("NETCOMMANDTYPE_PLAYERLEAVE");
	else if (type == 8)
		result.set("NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME");
	else if (type == 9)
		result.set("NETCOMMANDTYPE_REQUESTFRAMEDATA");
	else if (type == 7)
		result.set("NETCOMMANDTYPE_REQUESTPLAYERLEAVE");
	else if (type == 11)
		result.set("NETCOMMANDTYPE_DESTROYPLAYER");
	else if (type == 0)
		result.set("NETCOMMANDTYPE_ACKBOTH");
	else if (type == 1)
		result.set("NETCOMMANDTYPE_ACKSTAGE1");
	else if (type == 2)
		result.set("NETCOMMANDTYPE_ACKSTAGE2");
	else if (type == 12)
		result.set("NETCOMMANDTYPE_KEEPALIVE");
	else if (type == 13)
		result.set("NETCOMMANDTYPE_DISCONNECTCHAT");
	else if (type == 14)
		result.set("NETCOMMANDTYPE_CHAT");
	else if (type == 25)
		result.set("NETCOMMANDTYPE_DISCONNECTKEEPALIVE");
	else if (type == 26)
		result.set("NETCOMMANDTYPE_DISCONNECTPLAYER");
	else if (type == 27)
		result.set("NETCOMMANDTYPE_DISCONNECTVOTE");
	else if (type == 15)
		result.set("NETCOMMANDTYPE_PROGRESS");
	else if (type == 16)
		result.set("NETCOMMANDTYPE_LOADCOMPLETE");
	else if (type == 17)
		result.set("NETCOMMANDTYPE_TIMEOUTSTART");
	else if (type == 18)
		result.set("NETCOMMANDTYPE_WRAPPER");
	else if (type == 20)
		result.set("NETCOMMANDTYPE_HERO");
	else if (type == 19)
		result.set("NETCOMMANDTYPE_FILE");
	else if (type == 21)
		result.set("NETCOMMANDTYPE_FILEANNOUNCE");
	else if (type == 22)
		result.set("NETCOMMANDTYPE_FILEPROGRESS");
	else if (type == 28)
		result.set("NETCOMMANDTYPE_DISCONNECTFRAME");
	else if (type == 30)
		result.set("NETCOMMANDTYPE_SAVE_GAME");
	else
		result.set("UNKNOWN");
	return result;
}
