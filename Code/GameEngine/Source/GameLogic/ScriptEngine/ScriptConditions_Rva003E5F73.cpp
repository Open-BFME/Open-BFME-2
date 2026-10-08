// ?evaluatePlayerHasNumberObjectsWithModelCondition@ScriptConditions@@IAE_NPAVParameter@@PAUCondA003E5F73@@PAUCondB003E5F73@@PAUCondC003E5F73@@@Z
// retail 0x003E5F73, 191 bytes.
// Evidence: leaf via pin-only rva00357B82 plus rowed getSingleBitFromName plus rowed getEachPlayerFromMask plus rowed Player::rva002ABD1D; g_Va009FE16C plus ThePlayerList plus empty string fallback; accumulate until sum exceeds limit then op switch.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

class Parameter
{
};

class ScriptEngine
{
public:
	int rva00357B82(Parameter *p);
};

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

class ScriptConditions
{
protected:
	bool evaluatePlayerHasNumberObjectsWithModelCondition(Parameter *param, CondA003E5F73 *a, CondB003E5F73 *b, CondC003E5F73 *c);
};

bool ScriptConditions::evaluatePlayerHasNumberObjectsWithModelCondition(Parameter *param, CondA003E5F73 *a, CondB003E5F73 *b, CondC003E5F73 *c)
{
	int mask = TheScriptEngine->rva00357B82(param);
	int limit = c->m_limit;
	int total = 0;

	void *holder = a->m_holder;
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

	int op = b->m_op;

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

// ?g_Va009FE16C@@3PAVScriptEngine@@A: the global at this VA is ?TheScriptEngine@@3PAVScriptEngine@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009FE16C@@3PAVScriptEngine@@A=?TheScriptEngine@@3PAVScriptEngine@@A")
#pragma comment(linker, "/alternatename:?TheDebugWindowInterface@@3PAXA=?TheScriptEngine@@3PAVScriptEngine@@A")
// ?g_Va009FE16C@@3PAVScriptEngine@@A: the global at VA 0xdfe16c is ?TheScriptEngine@@3PAVScriptEngine@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE16C@@3PAVScriptEngine@@A=?TheScriptEngine@@3PAVScriptEngine@@A")
