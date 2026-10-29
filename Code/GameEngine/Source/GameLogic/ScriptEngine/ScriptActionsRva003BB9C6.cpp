// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB9C6Reveal@ScriptActions@@QAEX_NABVAsciiString@@@Z @0x003BB9C6 147B: ScriptActions member reveal-or-undo shroud for a player-name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once, then getNthPlayer (0x002A7A29) loop over PlayerList count +0x14 checking Player +0x5c or getEachPlayerFromMask (0x002A7BC9) loop reading Player +0x54, reaching revealMapForPlayerPermanently (0x00739790) or undoRevealMapForPlayerPermanently (0x007397B0) via TheShroudManager (0x009FE74C) selected by bool arg +8; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 8; caller 0x003CBE9F.
class AsciiString;
class Player
{
public:
	char m_pad00[0x54];
	int m_index54; // +0x54
	char m_pad58[0x04];
	int m_field5C; // +0x5c
};
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
class PartitionManager
{
public:
	void revealMapForPlayerPermanently(int playerIndex);
	void undoRevealMapForPlayerPermanently(int playerIndex);
};
extern PartitionManager *TheShroudManager;
void ScriptActions::Rva003BB9C6Reveal(bool reveal, const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0) {
		for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player->m_field5C != 0)
				continue;
			if (reveal)
				TheShroudManager->revealMapForPlayerPermanently(i);
			else
				TheShroudManager->undoRevealMapForPlayerPermanently(i);
		}
	} else {
		Player *player;
		do {
			player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player) {
				if (reveal)
					TheShroudManager->revealMapForPlayerPermanently(player->m_index54);
				else
					TheShroudManager->undoRevealMapForPlayerPermanently(player->m_index54);
			}
		} while (mask != 0);
	}
}
