// cl: /Ireference/shims/bfme2_ascii /O1
//
// ?Rva003BC785Set@@YGXABVAsciiString@@00@Z @0x003BC785 106B: free stdcall science-availability mask loop.
// Evidence: mask from ScriptEngine::rva00357475 0x00357475 with (name,0); loop ThePlayerList getEachPlayerFromMask 0x002A7BC9 then Player::getScienceAvailabilityTypeFromString 0x002ABEC9 with third arg then ScienceStore::rva001FF725 0x001FF725 with second arg then Player::setScienceAvailability 0x002AD8C9; globals g_Va009FE16C ThePlayerList TheScienceStore; ret 12; caller 0x003CD5C2.

#include "ascii_string.h"

enum ScienceType { SCIENCE_INVALID = -1 };
enum ScienceAvailabilityType { SCIENCE_AVAILABILITY_INVALID = -1 };

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
	ScienceAvailabilityType getScienceAvailabilityTypeFromString(const AsciiString &str);
	void setScienceAvailability(ScienceType science, ScienceAvailabilityType type);
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC785Set(const AsciiString &playerName, const AsciiString &scienceName, const AsciiString &availName)
{
	int mask = g_Va009FE16C->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			ScienceAvailabilityType avail = player->getScienceAvailabilityTypeFromString(availName);
			if (avail == SCIENCE_AVAILABILITY_INVALID)
				continue;
			ScienceType st = TheScienceStore->rva001FF725(scienceName);
			if (st == SCIENCE_INVALID)
				continue;
			player->setScienceAvailability(st, avail);
		}
	} while (mask != 0);
}

// Retail's call at 0x003BC7D0 reaches the rowed free function under this
// method spelling; bind it so the linked build resolves to the row.
#pragma comment(linker, "/alternatename:?rva001FF725@ScienceStore@@QBE?AW4ScienceType@@ABVAsciiString@@@Z=?Rva001FF725Get@@YG?AW4ScienceType@@ABVAsciiString@@@Z")
