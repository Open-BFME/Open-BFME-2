// cl: /Ireference/shims/bfme2_ascii /O1
//
// ?Rva003BC86ESet@@YGXABVAsciiString@@0@Z @0x003BC86E 65B: free stdcall mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva002A9F17::rva002A9F17 0x002A9F17 with second string; cmp mask jne loop ret 8; caller 0x003CDB27; sibling 0x003BB233 65B shape.

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

class Rva002A9F17
{
public:
	void rva002A9F17(const StringBase<char> *name);
};

void __stdcall Rva003BC86ESet(const AsciiString &name, const AsciiString &val)
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
