// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2D90Do@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2D90 90B
// Script set counter from player field: mask via rowed rva00357475 0x00357475 with NULL,
// player via rowed getPlayerFromMask 0x002A7B91, value via rowed rva002A7461 0x002A7461
// on player+0x60 with no args, counter via pin bfmeCounter 0x0020874B from second arg by value.
// Evidence: caller 0x003CE20C; neighbours Rva003C2CD8 0x003C2CD8 Rva003C2DEA 0x003C2DEA;
// globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0 temporary.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

class Rva002A7461
{
public:
	int rva002A7461();
};

class Player
{
public:
	char m_pad[0x60];
	Rva002A7461 m_60;
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

void ScriptActions::Rva003C2D90Do(Parameter *parameter, Parameter *b)
{
	int mask = TheScriptEngine->rva00357475(parameter->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = player->m_60.rva002A7461();
	ScriptCounter *scriptCounter = TheScriptEngine->bfmeCounter(b->m_string);
	scriptCounter->m_value = v;
}
