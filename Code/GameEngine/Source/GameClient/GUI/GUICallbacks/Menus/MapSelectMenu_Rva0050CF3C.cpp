// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?Rva0050CF3CStartHeadlessLanGame@@YAXXZ, retail 0x0050CF3C..0x0050D099
// (349 bytes). MapSelectMenu.cpp's local LAN game host: its sole caller is
// doGameStart (0x0050D099, call at 0x0050D0D0) when the headless client
// count at 0x00E045C8 is non-zero. It creates or resets TheLAN, binds it to
// 127.0.0.1, stores the pending map in the LAN preferences and writes them,
// trims the preferred user name to ten characters, sets it, requests the
// locations and an unnamed game, then starts that many headless clients.
//
// Donor: Open-BFME-1 GameEngine/Source/Common/BfmeAltAAV.cpp (bfmeAltAAV,
// same sequence; BFME 1 trims to twelve characters and sets the map key by
// subscript). Target facts: LANAPI is 0x60 bytes with its ctor pinned at
// 0x00449AB8; vslots reset 9 / init 1 / SetLocalIP 52 / RequestSetName 29 /
// RequestLocations 15 / RequestGameCreate 27 come from the call sites; the
// map setter 0x0044DD83 / write 0x0044D50D / user name 0x0044D330 and the
// LANPreferences ctor 0x0044D2F5 are rowed in GameModePreferences.cpp; the
// pending map is the AsciiString at TheWritableGlobalData+0xAC0.

#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;

AsciiString AsciiStringToQuotedPrintable(AsciiString original);

#include "../../../../../Include/Common/GameModePreferences.h"

class LANPreferences : public GameModePreferences
{
public:
	LANPreferences(Int mode);
	virtual ~LANPreferences();
};

#include "../../../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

#include "../../../../../Include/Common/GameEngine.h"

extern GameEngine *TheGameEngine;

#include "../../../../../Include/GameNetwork/LANAPI.h"

extern LANAPI *TheLAN;

// MapSelectMenu's headless client count, VA 0x00E045C8 (RVA 0x00A045C8, .data's
// zero tail past raw end 0x009DE008). MapSelectMenu.cpp owns that object under
// this name -- the combo-box write and the startHeadlessClients read are two
// different split-out units of the original TU, so it cannot be file-private
// there -- and the address-derived spelling this unit carried was its private
// view of the same object.
extern Int mapSelectHeadlessCount;

void Rva0050CF3CStartHeadlessLanGame(void)
{
	if (TheLAN == 0)
		TheLAN = new LANAPI;
	else
		TheLAN->reset();

	TheLAN->init();
	TheLAN->SetLocalIP(AsciiString("127.0.0.1"));

	LANPreferences pref(0);
	pref.rva0044DD83(AsciiStringToQuotedPrintable(TheWritableGlobalData->field0AC0));
	pref.write();

	UnicodeString userName = pref.rva0044D330();
	while (userName.getLength() > 10)
		userName.removeLastChar();

	TheLAN->RequestSetName(userName);
	TheLAN->RequestLocations();
	TheLAN->RequestGameCreate(UnicodeString(L""), false);
	TheGameEngine->startHeadlessClients(mapSelectHeadlessCount);
}
