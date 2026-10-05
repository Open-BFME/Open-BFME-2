// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?Rva003C2CD8Do@@YGXPAVParameter@@0@Z @0x003C2CD8 92B
// Script set counter from player field: mask via rowed rva00357475 0x00357475 with NULL,
// player via rowed getPlayerFromMask 0x002A7B91, value via rowed get 0x002A7389 on
// player+0x60 with 1, counter via pin bfmeCounter 0x0020874B from second arg by value.
// Evidence: callers 0x003CE1CE; neighbours Rva003C2C8F 0x003C2C8F Rva003C2E61 0x003C2E61;
// globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0 temporary.
// ?Rva003C2D34Do@@YGXPAVParameter@@0@Z @0x003C2D34 92B (caller 0x003CE1ED): the same
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

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend void __stdcall Rva003C2CD8Do(Parameter *a, Parameter *b);
	friend void __stdcall Rva003C2D34Do(Parameter *a, Parameter *b);
};

extern ScriptEngine *g_Va009FE16C;
extern PlayerList *ThePlayerList;

void __stdcall Rva003C2CD8Do(Parameter *a, Parameter *b)
{
	int mask = g_Va009FE16C->rva00357475(a->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = player->m_60.get(1);
	ScriptCounter *c = g_Va009FE16C->bfmeCounter(b->m_string);
	c->m_value = v;
}

void __stdcall Rva003C2D34Do(Parameter *a, Parameter *b)
{
	int mask = g_Va009FE16C->rva00357475(a->m_string, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	int v = player->m_60.rva002A7548(1);
	ScriptCounter *c = g_Va009FE16C->bfmeCounter(b->m_string);
	c->m_value = v;
}
