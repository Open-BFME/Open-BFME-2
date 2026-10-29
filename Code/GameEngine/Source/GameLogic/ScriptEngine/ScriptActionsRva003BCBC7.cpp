// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BCBC7Set@ScriptActions@@QAEXABVAsciiString@@M@Z @0x003BCBC7 65B: ScriptActions member mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then movss [eax+0x18],xmm0 from second float arg; cmp mask jne loop ret 8; caller 0x003CD9EC; sibling 0x003BB233 65B shape.

#include "ascii_string.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class Player
{
public:
	char m_pad00[0x18];
	float m_18;
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003BCBC7Set(const AsciiString &name, float val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->m_18 = val;
	} while (mask != 0);
}
