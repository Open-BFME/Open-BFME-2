// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BC6D9Set@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BC6D9 86B: ScriptActions member grant-science mask loop.
// Evidence: ScienceType from rowed ScienceStore::getScienceFromInternalName 0x001FF725 with second arg then -1 check; mask from ScriptEngine::rva00357475 0x00357475 with (name,0) then PlayerList getEachPlayerFromMask 0x002A7BC9 loop reaching Player::grantScience 0x002AD85E; globals TheScienceStore 0x009FE0E0 g_Va009FE16C ThePlayerList; ret 8; caller 0x003CD56B.

// ?Rva003BC72FSet@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BC72F 86B (caller 0x003CD590): the
// same loop reaching the unrowed Player member 0x002AD826 instead (ZH
// attemptToPurchaseScience shape: capability check 0x002ABE86, purchase cost
// 0x001FF3DC negated into +8's slot 2, then 0x002AD661; returns true), pinned
// by address.
#include "ascii_string.h"

enum ScienceType { SCIENCE_INVALID = -1 };

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
	bool grantScience(ScienceType science);
	bool attemptToPurchaseScience(ScienceType science);
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003BC6D9Set(const AsciiString &playerName, const AsciiString &scienceName)
{
	ScienceType st = TheScienceStore->getScienceFromInternalName(scienceName);
	if (st == SCIENCE_INVALID)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->grantScience(st);
	} while (mask != 0);
}

void ScriptActions::Rva003BC72FSet(const AsciiString &playerName, const AsciiString &scienceName)
{
	ScienceType st = TheScienceStore->getScienceFromInternalName(scienceName);
	if (st == SCIENCE_INVALID)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->attemptToPurchaseScience(st);
	} while (mask != 0);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
