// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?doSetCounterToPlayerOwnershipOfUnitsWithModelCondition@ScriptActions@@IAEXABVAsciiString@@00@Z @0x003C2F9C 129B
// Script count KindOf objects across players in mask into a counter: mask from
// first arg via rowed rva00357475 0x00357475 with NULL, kind bit via rowed
// BitFlags<304> getSingleBitFromName 0x000B42CA from second arg str() with empty
// fallback, sum over rowed getEachPlayerFromMask 0x002A7BC9 of rowed
// Player::rva002ABD1D 0x002ABD1D with limit 0x7ffffffe, counter via pin
// bfmeCounter 0x0020874B from third arg by value.
// Evidence: caller 0x003CE3C9; neighbours Rva003C2E61 0x003C2E61 Rva003C3175
// 0x003C3175; globals g_Va009FE16C ThePlayerList g_Rva0107301CEmptyString;
// StringBase copy 0x000365F0 temporary.
#include "ascii_string.h"

class ScriptEngine;
class PlayerList;
class Player;
struct ScriptCounter;

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend class ScriptActions;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

class Player
{
public:
	int rva002ABD1D(int kind, int limit);
};

struct ScriptCounter
{
	int m_value;
};

extern class ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

template <unsigned int N>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

class ScriptActions
{
protected:
	void doSetCounterToPlayerOwnershipOfUnitsWithModelCondition(const AsciiString &playerName, const AsciiString &kindName, const AsciiString &counterName);
};

void ScriptActions::doSetCounterToPlayerOwnershipOfUnitsWithModelCondition(const AsciiString &playerName, const AsciiString &kindName, const AsciiString &counterName)
{
	int mask = TheScriptEngine->rva00357475(playerName, (bool *)0);
	int total = 0;
	const char *holder = *(const char *const *)&kindName;
	const char *name = holder ? holder + 8 : "";
	int bit = BitFlags<304>::getSingleBitFromName(name);
	while (mask != 0)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player != 0)
			total += player->rva002ABD1D(bit, 0x7ffffffe);
	}
	ScriptCounter *counter = TheScriptEngine->bfmeCounter((AsciiString &)counterName);
	counter->m_value = total;
}
