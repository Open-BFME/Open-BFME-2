// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
//
// MappedImageCache::rva005EFFA6, retail 0x005EFFA6 (134 B), slot 1 of its vftable 0x00C78A78. INI block parse of a per-faction list whose
// field table is built on first use from two name tables (4 building kinds then 7 unit kinds; the
// per-entry callbacks are the rowed 0x005EFF68 and 0x005EFF87, the entry itself is passed as
// userData) and then handed to INI::initFromINI with this as the instance. Evidence: target bytes
// (two counted fill loops, zero terminator, build-once flag), callee rows, and the name tables
// at VA 0x00C78A58 and 0x00C78A20.
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

void Rva005EFF68(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x005EFF68
void Rva005EFF87(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x005EFF87

struct Rva005EFFA6Name
{
	int value;
	const char *name;
};

class MappedImageCache
{
public:
	virtual void rva005EFFA6(INI *ini);
};

void MappedImageCache::rva005EFFA6(INI *ini)
{
	static const Rva005EFFA6Name buildingKinds[4] =
	{
		{ 1, "BuildingFortress" },
		{ 2, "BuildingArmory" },
		{ 3, "BuildingResource" },
		{ 4, "BuildingBarracks" }
	};
	static const Rva005EFFA6Name unitKinds[7] =
	{
		{ 0, "UnitSoldier" },
		{ 1, "UnitArcher" },
		{ 2, "UnitPikemen" },
		{ 3, "UnitCavalry" },
		{ 4, "UnitMonster" },
		{ 5, "UnitHero" },
		{ 6, "UnitFortress" }
	};
	static FieldParse table[12];
	static bool built = false;
	if (!built)
	{
		FieldParse *entry = table;
		const Rva005EFFA6Name *kind = buildingKinds;
		for (int count = 4; count != 0; --count)
		{
			entry->token = kind->name;
			entry->parse = Rva005EFF68;
			entry->userData = kind;
			entry->offset = 0;
			++entry;
			++kind;
		}
		kind = unitKinds;
		for (int count = 7; count != 0; --count)
		{
			entry->token = kind->name;
			entry->parse = Rva005EFF87;
			entry->userData = kind;
			entry->offset = 0;
			++entry;
			++kind;
		}
		entry->token = 0;
		entry->parse = 0;
		entry->userData = 0;
		entry->offset = 0;
		built = true;
	}
	ini->initFromINI(this, table);
}
