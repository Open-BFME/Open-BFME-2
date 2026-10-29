// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BC785Set@ScriptActions@@QAEXABVAsciiString@@00@Z @0x003BC785 106B: ScriptActions member science-availability mask loop.
// Evidence: mask from ScriptEngine::rva00357475 0x00357475 with (name,0); loop ThePlayerList getEachPlayerFromMask 0x002A7BC9 then Player::getScienceAvailabilityTypeFromString 0x002ABEC9 with third arg then ScienceStore::getScienceFromInternalName 0x001FF725 with second arg then Player::setScienceAvailability 0x002AD8C9; globals g_Va009FE16C ThePlayerList TheScienceStore; ret 12; caller 0x003CD5C2.

#include "ascii_string.h"

enum ScienceType { SCIENCE_INVALID = -1 };
enum ScienceAvailabilityType { SCIENCE_AVAILABILITY_INVALID = -1 };

class ScienceStore
{
public:
	ScienceType getScienceFromInternalName(const AsciiString &name) const;
};
extern ScienceStore *TheScienceStore;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

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

void ScriptActions::Rva003BC785Set(const AsciiString &playerName, const AsciiString &scienceName, const AsciiString &availName)
{
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			ScienceAvailabilityType avail = player->getScienceAvailabilityTypeFromString(availName);
			if (avail == SCIENCE_AVAILABILITY_INVALID)
				continue;
			ScienceType st = TheScienceStore->getScienceFromInternalName(scienceName);
			if (st == SCIENCE_INVALID)
				continue;
			player->setScienceAvailability(st, avail);
		}
	} while (mask != 0);
}
