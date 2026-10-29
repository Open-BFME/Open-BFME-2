// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BC582Set@ScriptActions@@QAEXABVAsciiString@@H@Z @0x003BC582 76B: ScriptActions member mask loop calling Player+8 float method.
// Evidence: mov ecx,[TheScriptEngine] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then Rva003805BB::rva003805BB 0x003805BB with float(val) and false on Player+8; cmp mask jne loop ret 8; sibling ScriptActionsRva003BC5CE same mask-loop shape.

#include "ascii_string.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class Rva00380200
{
public:
	bool rva003805BB(float val, bool flag);
};

class Player
{
public:
	unsigned char m_pad[8]; // +0x00..0x07
	Rva00380200 m_sub; // +0x08
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003BC582Set(const AsciiString &name, int val)
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
