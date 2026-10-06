// cl: /Ireference/shims/bfme2_ascii
//
// ?Rva003BCB37Set@@YGXABVAsciiString@@H@Z @0x003BCB37 67B: free stdcall mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva002A9DB8::rva002A9DB8 0x002A9DB8 with (second arg-1); cmp mask jne loop ret 8; siblings 0x003BC86E 0x003BCBC7 shape; caller 0x003CD914.

#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class Rva002A9DB8
{
public:
	void *rva002A9DB8(int unused);
};

void __stdcall Rva003BCB37Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9DB8 *)player)->rva002A9DB8(val - 1);
	} while (mask != 0);
}
