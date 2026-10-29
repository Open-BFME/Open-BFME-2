// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB6C0Clear@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BB6C0 64B: ScriptActions member clearing a byte slot for each player in a name mask.
// Target evidence: calls ScriptEngine::rva00357475 (0x00357475) once then getEachPlayerFromMask (0x002A7BC9) loop calling set@Rva002A9D98ByteSlot (0x002A9D98) with 0; globals g_Va009FE16C (0x009FE16C) and ThePlayerList (0x009FEEE8); ret 4; caller 0x003CBC77.
class AsciiString;
class Player;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
class Rva002A9D98ByteSlot
{
public:
	void set(unsigned char v);
};
void ScriptActions::Rva003BB6C0Clear(const AsciiString &name)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9D98ByteSlot *)player)->set(0);
	} while (mask != 0);
}
