// cl: /Ireference/shims/bfme2_ascii /O1
//
// ?Rva003BC626Set@@YGXABVAsciiString@@H@Z @0x003BC626 84B: free stdcall mask loop over players with two per-player calls.
// Evidence: mov ecx,[0xDFE16C] call ScriptEngine::rva00357475 0x00357475 with (name,0) test mask je; loop ThePlayerList 0x009FEEE8 getEachPlayerFromMask 0x002A7BC9 then virtual slot1 on Player+8 with second arg then GameSlot::setTeamNumber 0x002E6A93 with Player+0x1c; cmp mask jne loop ret 8; sibling 0x003BC7EF same mask-loop shape.

#include "ascii_string.h"

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;

class Sub08
{
public:
	virtual void v0();
	virtual void v1(int val);
};

class Player
{
public:
	unsigned char m_pad[8]; // +0x00..0x07
	Sub08 m_sub; // +0x08 (vptr)
	unsigned char m_pad2[0x10]; // +0x0C..0x1B
	int m_1c; // +0x1C
	int m_20; // +0x20 (written by setTeamNumber via +0x18 relative to m_sub)
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class GameSlot
{
public:
	void setTeamNumber(int val);
};

void __stdcall Rva003BC626Set(const AsciiString &name, int val)
{
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			Sub08 *sub = &player->m_sub;
			sub->v1(val);
			((GameSlot *)sub)->setTeamNumber(player->m_1c);
		}
	} while (mask != 0);
}
