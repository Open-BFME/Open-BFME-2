// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doShroudMapEntire@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BBA59 122B: ScriptActions member sibling of 0x003BB94C reaching rva007397C0 instead of rva00739780.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once, then getNthPlayer (0x002A7A29) loop over PlayerList count +0x14 checking Player +0x5c or getEachPlayerFromMask (0x002A7BC9) loop reading Player +0x54, both reaching rva007397C0 (0x007397C0) via TheShroudManager (0x009FE74C); globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CBEB7.
class AsciiString;
#include "../../../Include/Common/Player.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getNthPlayer(int i);
	Player *getEachPlayerFromMask(int &mask);
	char m_pad00[0x14];
	int m_playerCount; // +0x14
};
extern PlayerList *ThePlayerList;
class PartitionManager;
extern PartitionManager *TheShroudManager;
class Rva007397C0
{
public:
	void rva007397C0(int playerIndex);
};
void ScriptActions::doShroudMapEntire(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0) {
		for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->m_playerType != 0)
				continue;
			((Rva007397C0 *)TheShroudManager)->rva007397C0(i);
		}
	} else {
		Player *player;
		do {
			player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player)
				((Rva007397C0 *)TheShroudManager)->rva007397C0(player->m_playerIndex);
		} while (mask != 0);
	}
}
