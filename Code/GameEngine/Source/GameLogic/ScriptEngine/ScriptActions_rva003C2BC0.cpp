// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2BC0Do@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C2BC0 104B
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
	int m_money;
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

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003C2BC0Do(Parameter *a, Parameter *b)
{
	int total = 0;
	int mask = TheScriptEngine->rva00357475(a->m_string, (bool *)0);
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player != 0) {
			PlayerInner003C2BC0 *money = (PlayerInner003C2BC0 *)((char *)player + 0x90);
			if (money != 0)
				total += money->m_money;
		}
	}
	ScriptCounter *counter = TheScriptEngine->bfmeCounter(b->m_string);
	counter->m_value = total;
}
