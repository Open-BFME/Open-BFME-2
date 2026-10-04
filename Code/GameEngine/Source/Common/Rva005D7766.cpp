// cl: /O1 /MD /arch:SSE
// ?rva005D7766@Rva005D7706@@QAE_NPAVObject@@@Z, retail 0x005D7766, 221 bytes.
// Evidence: slot 6 of 0x00875DB4 class Rva005D7706, terrain table via TheTerrainLogic+0x584 with shroud check then 0x005EE8DD.
class Object;
class Player;
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class PartitionManager;
enum CellShroudStatus
{
	CLEAR = 0,
	FOGGED = 1,
	SHROUDED = 2
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int idx, const Coord3D *pos) const;
};

extern PartitionManager *TheShroudManager;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

struct TableEntry
{
	char m_pad[0x18];
	unsigned char m_18;
};

class Rva00049D20
{
public:
	int rva005D772D(int idx);
	void *rva00049D20(void *dest, int idx);
	char m_pad00[0x10];
	void **m_begin;
	void **m_end;
};

class TerrainLogic
{
public:
	char m_pad00[0x584];
	Rva00049D20 *m_584;
};

class Player
{
public:
	char m_pad[0x54];
	int m_playerIndex;
};

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);
};

class Rva005D7706
{
public:
	bool rva005D7766(Object *source);
};

bool Rva005D7706::rva005D7766(Object *source)
{
	Rva00049D20 *tbl = TheTerrainLogic->m_584;
	Coord3D best;
	best.x = 0.0f;
	best.y = 0.0f;
	best.z = 0.0f;
	unsigned int bestIdx = 0;
	unsigned int bestCount = 0;
	unsigned int count = (unsigned int)(((char *)tbl->m_end - (char *)tbl->m_begin) >> 2);
	for (unsigned int i = 0; i < count; ++i)
	{
		TableEntry *e = (TableEntry *)tbl->m_begin[i];
		if (e->m_18 != 0)
			continue;
		unsigned int c = (unsigned int)tbl->rva005D772D((int)i);
		if (c <= bestCount)
			continue;
		Coord3D cur;
		tbl->rva00049D20(&cur, (int)i);
		Player *p = source->getControllingPlayer();
		int idx = p->m_playerIndex;
		if (TheShroudManager->getShroudStatusForPlayer(idx, &cur) == 2)
			continue;
		bestIdx = i;
		c = (unsigned int)tbl->rva005D772D((int)i);
		best = cur;
		bestCount = c;
	}
	if (bestCount > 0)
	{
		TableEntry *be = (TableEntry *)tbl->m_begin[bestIdx];
		be->m_18 = 1;
		return ((Rva005EE816 *)this)->rva005EE8DD(&best, source);
	}
	return false;
}
