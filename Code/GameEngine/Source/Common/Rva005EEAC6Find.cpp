// cl: /O1 /MD /arch:SSE
// ?rva005EEAC6@Rva005EEAC6@@QAE_NPAVPlayer@@0PAUCoord3D@@@Z, retail 0x005EEAC6, 181 bytes.
// Best-entry Coord picker with shroud skip: zeroes out Coord, looks up table via
// g_00DFEEF8 map, scans entries for highest count (Rva00049D20::rva005D772D),
// copies entry Coord (Rva00049D20::rva00049D20), checks TheShroudManager
// getShroudStatusForPlayer, keeps best visible. Evidence: caller 0x005D7D93
// passes this+0x28 with record plus Player plus Coord; callees rowed/pinned;
// globals g_00DFEEF8 TheShroudManager.
// Honest address name; owner unproven.

class Player;
struct Coord3D;
class PartitionManager;
class Rva002A8F24;
class Rva00049D20;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player
{
public:
	unsigned char m_pad[0x54];
	int m_playerIndex;
};

enum CellShroudStatus
{
	CLEAR = 0,
	FOGGED = 1,
	SHROUDED = 2
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};

extern PartitionManager *TheShroudManager;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva00049D20
{
public:
	int rva005D772D(int index);
	void *rva00049D20(void *dest, int index);
};

struct Rva005EEAC6Range
{
	char m_pad[0x10];
	void *m_begin;
	void *m_end;
};

struct Rva005EEAC6Store
{
	char m_pad[0x10];
	Rva005EEAC6Range *m_table;
};

class Rva005EEAC6
{
public:
	bool rva005EEAC6(Player *a1, Player *a2, Coord3D *out);
};

bool Rva005EEAC6::rva005EEAC6(Player *a1, Player *a2, Coord3D *out)
{
	Coord3D tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 0.0f;
	*out = tmp;
	void *store = g_00DFEEF8->rva002A8F24(a1);
	Rva005EEAC6Range *tbl = ((Rva005EEAC6Store *)store)->m_table;
	unsigned int count = (unsigned int)(((char *)tbl->m_end - (char *)tbl->m_begin) >> 2);
	unsigned int best = 0;
	for (unsigned int i = 0; i < count; ++i)
	{
		unsigned int c = (unsigned int)((Rva00049D20 *)tbl)->rva005D772D((int)i);
		if (c <= best)
			continue;
		((Rva00049D20 *)tbl)->rva00049D20(&tmp, (int)i);
		int idx = a2->m_playerIndex;
		if (TheShroudManager->getShroudStatusForPlayer(idx, &tmp) == SHROUDED)
			continue;
		best = c;
		*out = tmp;
	}
	if (best > 0)
		return true;
	return false;
}
