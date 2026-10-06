// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C2C28Do@@YGXPAVParameter@@0@Z @0x003C2C28 103B
// Script sum player field over mask then set counter: mask via rowed rva00357475
// 0x00357475 with NULL, each player via rowed getEachPlayerFromMask 0x002A7BC9,
// value via rowed get 0x002A9ED2, counter via pin bfmeCounter 0x0020874B by value.
// Evidence: callers 0x003CE190; neighbours Rva003C2A29 0x003C2A29 Rva003C2C8F 0x003C2C8F;
// globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0 temporary.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

class Rva002A9ED2DwordField
{
public:
	int get() const;
};

class Player
{
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
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
	friend void __stdcall Rva003C2C28Do(Parameter *a, Parameter *b);
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void __stdcall Rva003C2C28Do(Parameter *a, Parameter *b)
{
	int total = 0;
	int mask = TheScriptEngine->rva00357475(a->m_string, (bool *)0);
	while (mask != 0) {
		Player *p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p != 0)
			total += ((Rva002A9ED2DwordField *)p)->get();
	}
	ScriptCounter *c = TheScriptEngine->bfmeCounter(b->m_string);
	c->m_value = total;
}
