// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// LANAPI::OnGameStartTimer, retail 0x00248F6E (157B), vtable 0x00C3E680
// slot 44. Zero Hour's body (GameNetwork/LANAPICallbacks.cpp): the singular
// or plural "LAN:GameStartTimer*" label formatted with the seconds, sent to
// OnChat as a SYSTEM line. BFME2 deltas read off the target: the label comes
// from TheGameText's slot 17 (+0x44) as a pointer straight into
// UnicodeString::format (as ControlBarUpdateConstruction.cpp has it); OnChat
// is slot 40 (+0xA0) and takes both strings by reference; the local address
// comes from the virtual at slot 64 (+0x100, getLocalAddress) where Zero Hour
// reads m_localIP. LANCHAT_SYSTEM is 3 as upstream.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

#include "../../Include/GameNetwork/LANAPI.h"

void LANAPI::OnGameStartTimer(Int seconds)
{
	UnicodeString text;
	if (seconds == 1)
		text.format(TheGameText->fetchPtr("LAN:GameStartTimerSingular", 0), seconds);
	else
		text.format(TheGameText->fetchPtr("LAN:GameStartTimerPlural", 0), seconds);
	OnChat(L"SYSTEM", getLocalAddress(), text, LANCHAT_SYSTEM);
}
