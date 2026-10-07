// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii
//
// ?Rva003BC582Set@@YGXABVAsciiString@@H@Z @0x003BC582 76B: free stdcall mask loop calling Player+8 float method.
// Evidence: mov ecx,[TheScriptEngine] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva003805BB::rva003805BB 0x003805BB with float(val) and false on Player+8; cmp mask jne loop ret 8; sibling ScriptActionsRva003BC5CE same mask-loop shape.

#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;

class Rva003805BB
{
public:
	bool rva003805BB(float val, bool flag);
};

class Player
{
public:
	unsigned char m_pad[8]; // +0x00..0x07
	Rva003805BB m_sub; // +0x08
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void __stdcall Rva003BC582Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			player->m_sub.rva003805BB((float)val, false);
		}
	} while (mask != 0);
}
