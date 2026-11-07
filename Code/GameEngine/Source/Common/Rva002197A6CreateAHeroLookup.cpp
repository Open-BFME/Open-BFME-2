// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroManager hero-data lookup by id, retail 0x002197A6 (116 bytes,
// ret 4). Name is address-derived: neither binary names the method.
//
// Target facts: with TheGameInfo (VA 0x00E02EEC) set, the body scans the 8
// slots through the rowed GameInfo::getSlot 0x003FF29F and takes the slot's
// embedded CreateAHeroData at +0x64 when the +0x60 byte is set, matching its
// id (+4) against the argument; otherwise it scans the CreateAHeroData
// pointer registry vector at VA 0x00DFE358 (g_CreateAHeroRegistry, rowed in
// CreateAHeroRegistry.cpp). Both loops stop at the first hit.
//
// Shape from the WorldBuilder debug twin (WB 0x00B7E8E0, callgraph match):
// separate loop indices, an inline slot getter returning the embedded data or
// null, an inline id getter in the slot loop, size() bound and the re-indexed
// registry element assigned on a hit. Inline helper names are not in either
// binary and are descriptive only.
#include <vector>

#include "../../Include/GameLogic/CreateAHeroData.h"

class GameSlot
{
public:
	char m_pad[0x60];
	bool m_hasHeroData;
	char m_pad61[3];
	CreateAHeroData m_heroData;
	CreateAHeroData *getHeroData() { return m_hasHeroData ? &m_heroData : 0; }
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
};
extern GameInfo *TheGameInfo;
// The registry's storage is the global ScriptGlueRva003BE7ED.cpp defines at
// that address (g_00DFE358); read it through a vector view.
extern unsigned int g_00DFE358[3];
#define g_CreateAHeroRegistry (*(_STL::vector<CreateAHeroData *> *)&g_00DFE358)

#include "../../Include/GameLogic/CreateAHeroManager.h"

CreateAHeroData *CreateAHeroManager::rva002197A6(int id)
{
	CreateAHeroData *result = 0;
	if (TheGameInfo != 0)
	{
		for (unsigned int i = 0; result == 0 && i < 8; ++i)
		{
			GameSlot *slot = TheGameInfo->getSlot(i);
			if (slot == 0)
				continue;
			CreateAHeroData *data = slot->getHeroData();
			if (data != 0 && data->field04 == id)
				result = data;
		}
	}
	else
	{
		for (unsigned int i = 0; result == 0 && i < g_CreateAHeroRegistry.size(); ++i)
		{
			if (id == g_CreateAHeroRegistry[i]->field04)
				result = g_CreateAHeroRegistry[i];
		}
	}
	return result;
}
