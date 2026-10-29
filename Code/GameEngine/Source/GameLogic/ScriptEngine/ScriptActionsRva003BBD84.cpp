// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
//
// Twin mask sweeps over players, range-17 batch (same family as rowed
// Rva003BB233Set 0x003BB233, which sweeps a caller val; these sweep constant
// 1 through two unrowed Player entries).
// ?doPlayerGarrisonAllBuildings@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BBD84 64B: mask from ScriptEngine
// rva00357475 0x00357475, then the rowed Player::garrisonAllUnits(CMD_FROM_SCRIPT) (0x002AEEA7) per player.
// ?doPlayerExitAllBuildings@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BBDC4 64B: same through pinned
// Player::ungarrisonAllUnits(CMD_FROM_SCRIPT). Evidence: ret 4 single name arg, TheScriptEngine +
// ThePlayerList globals, getEachPlayerFromMask loop; player entries pinned
// address-derived.
#include "ascii_string.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

// 0x002AF037 is the rowed Player::ungarrisonAllUnits (PlayerTeamCommands.cpp).
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1, CMD_FROM_AI = 2 };

class Player
{
public:
	void garrisonAllUnits(CommandSourceType cmdSource);
	void ungarrisonAllUnits(CommandSourceType cmdSource);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void ScriptActions::doPlayerGarrisonAllBuildings(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->garrisonAllUnits(CMD_FROM_SCRIPT);
	} while (mask != 0);
}

void ScriptActions::doPlayerExitAllBuildings(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->ungarrisonAllUnits(CMD_FROM_SCRIPT);
	} while (mask != 0);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
