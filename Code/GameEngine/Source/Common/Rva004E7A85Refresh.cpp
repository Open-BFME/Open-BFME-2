// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E7A85@Rva004E7A85@@QAEXXZ @0x004E7A85 82B.
// First-shot refresh: when m_4 is still zero, sweep the +0x1C collector via
// rowed 0x004E551E, resolve the relationship index through the 0x00DFEE88
// world (rowed PlayerList probe 0x002A7C70 on its +0x10/+0x54 chain, default
// 0 when any link is null), submit the collector plus index to the
// TheGameLogic +0x170 target via rowed 0x00359D42, then run rowed 0x004E54B8
// on the collector. Always finishes with ++m_4.
class PlayerList
{
public:
	int getPlayersWithRelationship(int src, unsigned int allowed, bool reverse);
};
typedef int Int;

class Rva004E7A85World10
{
public:
	char m_pad[0x54];
	int m_54;
};

class Rva004E7A85World
{
public:
	char m_pad[0x10];
	Rva004E7A85World10 *m_10;
};

extern class PlayerList *ThePlayerList;

class GameLogic;
extern GameLogic *TheGameLogic;

class Rva00359D42Target
{
public:
	char m_pad[0x170];
	class TerrainResourceManager *m_170;
};

class TerrainResourceManager;
class Cb00359D42;

class TerrainResourceManager
{
public:
	void enumerateRegisteredClaimants(int v, Cb00359D42 *cb);
};

class ResourceEntryCollector
{
public:
	void rva004E551E();
};

class Rva004E54B8
{
public:
	void rva004E54B8();
};

class Rva004E7A85
{
public:
	void rva004E7A85();
private:
	char m_pad[4];
	int m_4;
	char m_pad08[0x1C - 0x08];
	ResourceEntryCollector m_1C;
};

void Rva004E7A85::rva004E7A85()
{
	if (m_4 == 0) {
		ResourceEntryCollector *c = &m_1C;
		c->rva004E551E();
		Rva004E7A85World *world = (*(Rva004E7A85World **)&ThePlayerList);
		int rel = 0;
		if (world != 0 && world->m_10 != 0) {
			int idx = world->m_10->m_54;
			rel = ((PlayerList *)world)->getPlayersWithRelationship(idx, 3, false);
		}
		((Rva00359D42Target *)TheGameLogic)->m_170->enumerateRegisteredClaimants(rel, (Cb00359D42 *)c);
		((Rva004E54B8 *)c)->rva004E54B8();
	}
	++m_4;
}
