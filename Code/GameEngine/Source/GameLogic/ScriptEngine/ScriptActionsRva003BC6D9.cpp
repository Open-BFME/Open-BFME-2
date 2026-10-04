// cl: /Ireference/shims/bfme2_ascii /O1
//
// ?Rva003BC6D9Set@@YGXABVAsciiString@@0@Z @0x003BC6D9 86B: free stdcall grant-science mask loop.
// Evidence: ScienceType from rowed Rva001FF725Get 0x001FF725 with second arg then -1 check; mask from ScriptEngine::rva00357475 0x00357475 with (name,0) then PlayerList getEachPlayerFromMask 0x002A7BC9 loop reaching Player::grantScience 0x002AD85E; globals TheScienceStore 0x009FE0E0 g_Va009FE16C ThePlayerList; ret 8; caller 0x003CD56B.

#include "ascii_string.h"

enum ScienceType { SCIENCE_INVALID = -1 };

class ScienceStore
{
public:
	ScienceType rva001FF725(const AsciiString &str) const;
};
extern ScienceStore *TheScienceStore;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *g_Va009FE16C;

class Player
{
public:
	bool grantScience(ScienceType science);
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC6D9Set(const AsciiString &playerName, const AsciiString &scienceName)
{
	ScienceType st = TheScienceStore->rva001FF725(scienceName);
	if (st == SCIENCE_INVALID)
		return;
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->grantScience(st);
	} while (mask != 0);
}

// Retail's call at 0x003BC6E6 reaches the rowed free function under this
// method spelling; bind it so the linked build resolves to the row.
#pragma comment(linker, "/alternatename:?rva001FF725@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z=?Rva001FF725Get@@YG?AW4ScienceType@@ABVAsciiString@@@Z")
