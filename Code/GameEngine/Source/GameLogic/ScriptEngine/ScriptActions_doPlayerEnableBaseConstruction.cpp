// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doPlayerEnableBaseConstruction@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BB3DC 62B: ScriptActions member setting Player byte +0x339 for each player in a name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once then getEachPlayerFromMask (0x002A7BC9) loop writing byte [eax+0x339]=1; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CB81C; sibling of 0x003BB31D.
class AsciiString;
class Player
{
public:
	char m_pad00[0x339];
	unsigned char m_flag339; // +0x339
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
void ScriptActions::doPlayerEnableBaseConstruction(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->m_flag339 = 1;
	} while (mask != 0);
}
