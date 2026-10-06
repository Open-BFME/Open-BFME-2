// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C2E61Do@@YGXPBX00@Z @0x003C2E61 104B
// Set counter for player: mask from first arg via rowed rva00357475 0x00357475 with NULL,
// player via rowed getPlayerFromMask 0x002A7B91, value via rowed rva0039C0F4 0x0039C0F4 on
// player+0x3BC, counter via pin bfmeCounter 0x0020874B from third arg by value.
// Evidence: callers 0x003CE33F; neighbours Rva003C2A29 0x003C2A29 and Rva003C3175 0x003C3175;
// globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0 temporary.
#include "ascii_string.h"

class ScriptEngine;
class PlayerList;
class Player;
class Rva0039C0F4;
struct ScriptCounter;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend void __stdcall Rva003C2E61Do(const void *, const void *, const void *);
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};

class Rva0039C0F4
{
public:
	int rva0039C0F4(const AsciiString &name);
};

class Player
{
public:
	char m_pad[0x3bc];
	Rva0039C0F4 m_counts;
};

struct ScriptCounter
{
	int m_value;
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void __stdcall Rva003C2E61Do(const void *a1, const void *a2, const void *a3)
{
	const AsciiString &s1 = *(const AsciiString *)((const char *)a1 + 0x10);
	const AsciiString &s2 = *(const AsciiString *)((const char *)a2 + 0x10);
	const AsciiString &s3 = *(const AsciiString *)((const char *)a3 + 0x10);
	int mask = TheScriptEngine->rva00357475(s1, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	Rva0039C0F4 *counts = (Rva0039C0F4 *)((char *)player + 0x3bc);
	if (counts == 0)
		return;
	int v = counts->rva0039C0F4(s2);
	ScriptCounter *c = TheScriptEngine->bfmeCounter((AsciiString &)s3);
	c->m_value = v;
}
