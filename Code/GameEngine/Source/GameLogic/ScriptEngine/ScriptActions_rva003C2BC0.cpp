// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C2BC0Do@@YGXPAVParameter@@0@Z @0x003C2BC0 104B
// Script sum player+0x94 over mask then set counter: mask via rowed rva00357475
// 0x00357475 with NULL, each player via rowed getEachPlayerFromMask 0x002A7BC9,
// value int at player+0x94 via +0x90 base null-checked, counter via pin bfmeCounter
// 0x0020874B by value. Evidence: callers 0x003CE171; neighbours Rva003C2A29 0x003C2A29
// Rva003C2C28 0x003C2C28; globals g_Va009FE16C ThePlayerList; StringBase 0x000365F0.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_string;
};

struct PlayerInner003C2BC0
{
	char m_pad[4];
	int m_4;
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
	friend void __stdcall Rva003C2BC0Do(Parameter *a, Parameter *b);
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void __stdcall Rva003C2BC0Do(Parameter *a, Parameter *b)
{
	int total = 0;
	int mask = TheScriptEngine->rva00357475(a->m_string, (bool *)0);
	while (mask != 0) {
		Player *p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p != 0) {
			PlayerInner003C2BC0 *r = (PlayerInner003C2BC0 *)((char *)p + 0x90);
			if (r != 0)
				total += r->m_4;
		}
	}
	ScriptCounter *c = TheScriptEngine->bfmeCounter(b->m_string);
	c->m_value = total;
}
