// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?show@Rva004E7A85@@QAEXXZ @0x004E7A85 82B.
// First-shot refresh: when m_4 is still zero, sweep the +0x1C collector via
// rowed 0x004E551E, resolve the relationship index through the 0x00DFEE88
// world (rowed PlayerList probe 0x002A7C70 on its +0x10/+0x54 chain, default
// 0 when any link is null), submit the collector plus index to the
// TheGameLogic +0x170 target via rowed 0x00359D42, then run rowed 0x004E54B8
// on the collector. Always finishes with ++m_4.
#include "../../Include/Common/PlayerList.h"
typedef int Int;

class Rva004E7A85World10
{
public:
	char m_pad[0x54];
	int m_playerIndex;
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

#include "../../Include/GameClient/TerrainResourceManager.h"

#include "../../Include/GameClient/ResourceEntryCollector.h"

#include "../../Include/Common/Rva004E54B8.h"

class Rva004E7A85
{
public:
	void show();
private:
	char m_pad[4];
	int m_4;
	char m_pad08[0x1C - 0x08];
	ResourceEntryCollector m_1C;
};

void Rva004E7A85::show()
{
	if (m_4 == 0) {
		ResourceEntryCollector *resourceEntryCollector = &m_1C;
		resourceEntryCollector->rva004E551E();
		Rva004E7A85World *world = (*(Rva004E7A85World **)&ThePlayerList);
		int rel = 0;
		if (world != 0 && world->m_10 != 0) {
			int idx = world->m_10->m_playerIndex;
			rel = ((PlayerList *)world)->getPlayersWithRelationship(idx, 3, false);
		}
		((Rva00359D42Target *)TheGameLogic)->m_170->enumerateRegisteredClaimants(rel, (Cb00359D42 *)resourceEntryCollector);
		((Rva004E54B8 *)resourceEntryCollector)->rva004E54B8();
	}
	++m_4;
}
