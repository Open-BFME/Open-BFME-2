// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?Rva003C2D90Do@@YGXPAVParameter@@0@Z @0x003C2D90 90B
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

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend void __stdcall Rva003C2D90Do(Parameter *a, Parameter *b);
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void __stdcall Rva003C2D90Do(Parameter *a, Parameter *b)
{
	int mask = TheScriptEngine->rva00357475(a->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = player->m_60.rva002A7461();
	ScriptCounter *c = TheScriptEngine->bfmeCounter(b->m_string);
	c->m_value = v;
}
