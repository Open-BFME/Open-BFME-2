// cl: /Ireference/shims/bfme2_ascii
// ?Rva003E52EBCheck@@YG_NPAVParameter@@PAUCondA003E52EB@@PAUCondB003E52EB@@@Z
// retail 0x003E52EB 146B leaf free stdcall bool of 3x Parameter ret 0xc. Evidence:
// rowed ScriptEngine::rva00357475 via g_Va009FE16C with (Parameter+0x10 AsciiString and NULL)
// plus rowed PlayerList::getPlayerFromMask via ThePlayerList plus Player +0x1c value
// op at [p2+8] 0..5 selects < <= == >= > != vs [p3+8] like siblings 0x003E4F79 0x003E514F;
// globals g_Va009FE16C ThePlayerList; siblings 0x003E514F 0x003E537D /O1.
#include "ascii_string.h"

class Parameter
{
public:
	char m_pad[0x10];
	AsciiString m_10;
};

struct CondA003E52EB
{
	char m_pad[8];
	int m_op;
};

struct CondB003E52EB
{
	char m_pad[8];
	int m_value;
};

class Player
{
public:
	char m_pad[0x1c];
	int m_1c;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern class ScriptEngine *TheScriptEngine;

bool __stdcall Rva003E52EBCheck(Parameter *a, CondA003E52EB *b, CondB003E52EB *c)
{
	int mask = TheScriptEngine->rva00357475(a->m_10, 0);
	Player *pl = ThePlayerList->getPlayerFromMask(mask);
	if (!pl)
		return false;
	int op = b->m_op;
	int val = pl->m_1c;
	bool result = false;
	switch (op) {
		case 0: result = (val < c->m_value); break;
		case 1: result = (val <= c->m_value); break;
		case 2: result = (val == c->m_value); break;
		case 3: result = (val >= c->m_value); break;
		case 4: result = (val > c->m_value); break;
		case 5: result = (val != c->m_value); break;
	}
	if (result)
		return true;
	return false;
}
