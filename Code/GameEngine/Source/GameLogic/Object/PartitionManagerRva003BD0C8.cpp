// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD0C8Set@ScriptActions@@QAEXABVAsciiString@@E@Z, retail 0x003BD0C8 64B leaf via rowed 0x00357475 0x002A7BC9.
// Player-mask byte setter: mask from ScriptEngine::rva00357475 then getEachPlayerFromMask loop writing byte [eax+0x735]=val.
// Evidence: callees rowed; caller 0x003CE316; prev 0x003BD032 next 0x003BD153 same /O1; sibling Rva003BB39E pattern with 0x338 constant.
class AsciiString;
class Player
{
public:
	char m_pad00[0x735];
	unsigned char m_flag735; // +0x735
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
void ScriptActions::Rva003BD0C8Set(const AsciiString &name, unsigned char val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->m_flag735 = val;
	} while (mask != 0);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
