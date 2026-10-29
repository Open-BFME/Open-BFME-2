// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BC86ESet@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BC86E 65B: ScriptActions member mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva002A9F17::rva002A9F17 0x002A9F17 with second string; cmp mask jne loop ret 8; caller 0x003CDB27; sibling 0x003BB233 65B shape.

#include "ascii_string.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class Rva002A9F17
{
public:
	void rva002A9F17(const StringBase<char> *name);
};

void ScriptActions::Rva003BC86ESet(const AsciiString &name, const AsciiString &val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9F17 *)player)->rva002A9F17((const StringBase<char> *)&val);
	} while (mask != 0);
}
