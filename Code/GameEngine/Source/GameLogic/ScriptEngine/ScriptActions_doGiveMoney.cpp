// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?doGiveMoney@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BC0A7 96B leaf caller 0x003CC57C globals 0x009FE16C 0x009FEEE8
// Evidence: ScriptEngine::rva00357475 mask then getEachPlayer loop Money at Player+0x90 deposit if amount>=0 else withdraw -amount.
#include "ascii_string.h"

#include "../../../Include/GameLogic/ScriptEngine.h"

class Player;
#include "../../../Include/Common/PlayerList.h"

class Rva0039B795;
class Rva0039B7AD;

#include "../../../Include/GameLogic/Module/Rva003B0D7C.h"

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::doGiveMoney(const AsciiString &name, int amount)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player == 0)
			continue;
		Rva003B0D7C *money = (Rva003B0D7C *)((char *)player + 0x90);
		if (money == 0)
			continue;
		if (amount < 0)
			money->withdraw((unsigned int)-amount, 0, true);
		else
			money->rva003B0D7C(amount, 0, true);
	} while (mask != 0);
}
