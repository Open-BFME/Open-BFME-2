// cl: /Ireference/shims/bfme2_ascii
// ?evaluatePlayerHasNumberObjectsWithModelCondition@ScriptConditions@@IAE_NPAVParameter@@PAUCondA003E5F73@@PAUCondB003E5F73@@PAUCondC003E5F73@@@Z
// retail 0x003E5F73, 191 bytes.
// Evidence: leaf via pin-only rva00357B82 plus rowed getSingleBitFromName plus rowed getEachPlayerFromMask plus rowed Player::rva002ABD1D; TheScriptEngine plus ThePlayerList plus empty string fallback; accumulate until sum exceeds limit then op switch.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

class Parameter
{
};

#include "../../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class Player
{
public:
	int rva002ABD1D(int kind, int limit);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

extern PlayerList *ThePlayerList;


template <unsigned int N>
class BitFlags
{
public:
	static int getSingleBitFromName(const char *token);
};

struct CondA003E5F73
{
	char m_pad[0x10];
	void *m_holder;
};

struct CondB003E5F73
{
	char m_pad[8];
	int m_op;
};

struct CondC003E5F73
{
	char m_pad[8];
	int m_limit;
};

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluatePlayerHasNumberObjectsWithModelCondition(Parameter *param, CondA003E5F73 *modelConditionParm, CondB003E5F73 *comparisonParm, CondC003E5F73 *countParm)
{
	int mask = TheScriptEngine->rva00357B82(param);
	int limit = countParm->m_limit;
	int total = 0;

	void *holder = modelConditionParm->m_holder;
	const char *name = holder ? (const char *)holder + 8 : "";
	int bit = BitFlags<304>::getSingleBitFromName(name);

	while (mask != 0)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
		{
			total += player->rva002ABD1D(bit, limit);
			if (total > limit)
				break;
		}
	}

	int op = comparisonParm->m_op;

	switch (op)
	{
	case 0:
		return total < limit;
	case 1:
		return total <= limit;
	case 2:
		return total == limit;
	case 3:
		return total >= limit;
	case 4:
		return total > limit;
	case 5:
		return total != limit;
	default:
		break;
	}

	return false;
}

// ?TheScriptEngine@@3PAVScriptEngine@@A: the global at this VA is ?TheScriptEngine@@3PAVScriptEngine@@A; this name is an alias for it.
// ?TheScriptEngine@@3PAVScriptEngine@@A: the global at VA 0xdfe16c is ?TheScriptEngine@@3PAVScriptEngine@@A.
