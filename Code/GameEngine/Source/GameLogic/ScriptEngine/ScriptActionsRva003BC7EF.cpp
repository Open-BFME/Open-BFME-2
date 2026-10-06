// cl: /Ireference/shims/bfme2_ascii
//
// ?Rva003BC7EFSet@@YGXABVAsciiString@@H@Z @0x003BC7EF 65B: free stdcall mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Player::rva002AA756 0x002AA756 with second arg; cmp mask jne loop ret 8; caller 0x003CDAEA; sibling 0x003BB233 same 65B shape.

#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;

class Player
{
public:
	void rva002AA756(int val);
};
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC7EFSet(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			player->rva002AA756(val);
	} while (mask != 0);
}
