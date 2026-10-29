// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C2EC9Do@ScriptActions@@QAEXPBX00@Z @0x003C2EC9 211B
// Set counter from KindOf-filtered object count for player: mask from first arg
// via rowed rva00357475 0x00357475 with NULL, player via rowed getPlayerFromMask
// 0x002A7B91, sum via rowed rva0039BF67 0x0039BF67 on player+0x3BC with
// mustBeSet carrying the bit from second arg +8 and empty mustBeClear,
// counter via pin bfmeCounter 0x0020874B from third arg by value.
// Evidence: caller 0x003CE368; neighbours Rva003C2E61 0x003C2E61 Rva003C2F9C
// 0x003C2F9C; globals g_Va009FE16C ThePlayerList; StringBase copy 0x000365F0.
#include "ascii_string.h"

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)
#pragma comment(linker, "/alternatename:??0?$BitFlags@$0HE@@@QAE@ABV0@@Z=??0BfmeFixedStorage0004543D@@QAE@ABV0@@Z")

class ScriptEngine;
class PlayerList;
class Player;
class Rva0039BF67;
struct ScriptCounter;

template <int N>
class BitFlags
{
public:
	__declspec(dllimport) __forceinline BitFlags() {}
	BitFlags(const BitFlags &other);
	unsigned m_words[7];
};

#include "../../../Include/GameLogic/ScriptEngine.h"

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};

class Rva0039BF67
{
public:
	int rva0039BF67(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear);
};

class Player
{
public:
	char m_pad[0x3bc];
	Rva0039BF67 m_counts;
};

struct ScriptCounter
{
	int m_value;
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void ScriptActions::Rva003C2EC9Do(const void *a1, const void *a2, const void *a3)
{
	const AsciiString &playerName = *(const AsciiString *)((const char *)a1 + 0x10);
	const AsciiString &counterName = *(const AsciiString *)((const char *)a3 + 0x10);
	int mask = TheScriptEngine->rva00357475(playerName, (bool *)0);
	if (mask == 0)
		return;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return;
	Rva0039BF67 *counts = (Rva0039BF67 *)((char *)player + 0x3bc);
	if (counts == 0)
		return;
	BitFlags<116> mustBeClear;
	BitFlags<116> mustBeSet;
	memset(&mustBeSet, 0, sizeof(mustBeSet));
	unsigned kind = *(const unsigned *)((const char *)a2 + 8);
	mustBeSet.m_words[kind >> 5] |= (1u << (kind & 31));
	memset(&mustBeClear, 0, sizeof(mustBeClear));
	memset(&mustBeClear, 0, sizeof(mustBeClear));
	int count = counts->rva0039BF67(mustBeSet, mustBeClear);
	ScriptCounter *counter = TheScriptEngine->bfmeCounter((AsciiString &)counterName);
	counter->m_value = count;
}
