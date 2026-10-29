// stlport
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2CD8Do@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2CD8 92B
// Script set counter from player field: mask via rowed rva00357475 0x00357475 with NULL,
// player via rowed getPlayerFromMask 0x002A7B91, value via rowed get 0x002A7389 on
// player+0x60 with 1, counter via pin bfmeCounter 0x0020874B from second arg by value.
// Evidence: callers 0x003CE1CE; neighbours Rva003C2C8F 0x003C2C8F Rva003C2E61 0x003C2E61;
// globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0 temporary.
// ?Rva003C2D34Do@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2D34 92B (caller 0x003CE1ED): the same
// body reading the player+0x60 member through its unrowed 0x002A7548 (returns
// 0x002A7461's value less the member's +8), pinned by address.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

class Rva002A7389
{
public:
	int get(int x);
	int rva002A7548(int x);
};
class Rva002A7461
{
public:
	int rva002A7548(int x);
};

class Player
{
public:
	char m_pad[0x60];
	Rva002A7389 m_60;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};

struct ScriptCounter
{
	int m_value;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003C2CD8Do(Parameter *parameter, Parameter *b)
{
	int mask = TheScriptEngine->rva00357475(parameter->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = player->m_60.get(1);
	ScriptCounter *scriptCounter = TheScriptEngine->bfmeCounter(b->m_string);
	scriptCounter->m_value = v;
}

void ScriptActions::Rva003C2D34Do(Parameter *parameter, Parameter *b)
{
	int mask = TheScriptEngine->rva00357475(parameter->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = ((Rva002A7461 *)&player->m_60)->rva002A7548(1);
	ScriptCounter *scriptCounter = TheScriptEngine->bfmeCounter(b->m_string);
	scriptCounter->m_value = v;
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
