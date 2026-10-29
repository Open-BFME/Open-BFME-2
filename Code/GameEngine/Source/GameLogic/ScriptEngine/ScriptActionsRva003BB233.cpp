// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BB233Set@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BB233 65B: ScriptActions member mask loop over players.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva002A9BF2::rva002A9CCA 0x002A9CCA with second arg; cmp mask jne loop ret 8; caller 0x003CB355.
// ?Rva003BB163Set@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BB163 65B (caller 0x003CA929) and
// ?Rva003BC8AFSet@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BC8AF 65B (caller 0x003CDB4C) are
// the same loop over the players' unrowed int setters 0x002A9DEC (forwards to the
// AI player at +0x2DC) and 0x002A9F35 (passes +0x318 to the 0x00E03158 global),
// pinned by address.

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

class Rva002A9BF2
{
public:
	void rva002A9CCA(int val);
};

// LINK: 0x2A9DEC and 0x2A9F35 are rowed on their own owner classes (Rva002A9DEC; Rva002A9F17 takes the
// argument as a pointer); bind them through casts of the same player pointer.
class Rva002A9DEC
{
public:
	void rva002A9DEC(int val);
};

class Rva002A9F17
{
public:
	void rva002A9F35(const void *val);
};

void ScriptActions::Rva003BB233Set(const AsciiString &name, int val)
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

void ScriptActions::Rva003BB163Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9DEC *)player)->rva002A9DEC(val);
	} while (mask != 0);
}

void ScriptActions::Rva003BC8AFSet(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
			((Rva002A9F17 *)player)->rva002A9F35((const void *)val);
	} while (mask != 0);
}

// Member ABI: executeAction3CA4BE supplies its ScriptActions receiver in ECX.
// Canonical class declares these methods; original action verbs remain uncertain.
