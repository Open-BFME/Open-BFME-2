// cl: /Ireference/shims/bfme2_ascii
//
// ?Rva003BB233Set@@YGXABVAsciiString@@H@Z @0x003BB233 65B: free stdcall mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva002A9BF2::rva002A9CCA 0x002A9CCA with second arg; cmp mask jne loop ret 8; caller 0x003CB355.
// ?Rva003BB163Set@@YGXABVAsciiString@@H@Z @0x003BB163 65B (caller 0x003CA929) and
// ?Rva003BC8AFSet@@YGXABVAsciiString@@H@Z @0x003BC8AF 65B (caller 0x003CDB4C) are
// the same loop over the players' unrowed int setters 0x002A9DEC (forwards to the
// AI player at +0x2DC) and 0x002A9F35 (passes +0x318 to the 0x00E03158 global),
// pinned by address.

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

class Rva002A9BF2
{
public:
	void rva002A9CCA(int val);
	void rva002A9DEC(int val);
	void rva002A9F35(int val);
};

void __stdcall Rva003BB233Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9BF2 *)player)->rva002A9CCA(val);
	} while (mask != 0);
}

void __stdcall Rva003BB163Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9BF2 *)player)->rva002A9DEC(val);
	} while (mask != 0);
}

void __stdcall Rva003BC8AFSet(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9BF2 *)player)->rva002A9F35(val);
	} while (mask != 0);
}
