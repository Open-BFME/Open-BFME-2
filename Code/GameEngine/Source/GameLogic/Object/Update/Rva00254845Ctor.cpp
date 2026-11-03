// cl: /O1 /GX- /MD /DNDEBUG
//
// ??0Rva00254845@@QAE@XZ, retail 0x00254845, 18 bytes.
// Frameless ctor over the rowed OpenContain base (0x253487) at offset 0: calls
// the base ctor, then stores folded vtable 0x00BF2558 at +0. No own members.
extern "C" const void *const __identifier("??_7WeaponSetUpgradeModuleData@@6B@")[];  // vftable 0x00BF2558

class ModuleData;
class MultiIniFieldParse;
#include "../../../../Include/Common/INI/INI.h"
class BuildableHeroListUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};
class AllowBannerSpawnUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

class Rva00253487Base
{
public:
	Rva00253487Base();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class Rva00254845 : public Rva00253487Base
{
public:
	Rva00254845();
};

Rva00254845::Rva00254845()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@")));
}

class Rva0025480BData : public Rva00253487Base
{
public:
	__forceinline Rva0025480BData()
	{
		m_vtable = reinterpret_cast<void *>(((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@")));
	}
};

// ?ModuleFactoryDataAt0025480B@@YAPAVModuleData@@PAVINI@@@Z @0x0025480B (58B)
ModuleData *ModuleFactoryDataAt0025480B(INI *ini)
{
	Rva0025480BData *data = new Rva0025480BData;
	if (ini)
		ini->initFromINIMultiProc(data, BuildableHeroListUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// ?ModuleFactoryDataAt00254857@@YAPAVModuleData@@PAVINI@@@Z @0x00254857 (58B)
ModuleData *ModuleFactoryDataAt00254857(INI *ini)
{
	Rva0025480BData *data = new Rva0025480BData;
	if (ini)
		ini->initFromINIMultiProc(data, AllowBannerSpawnUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

struct FieldParse;
int Rva004CE29DGet();

#include "../../../../Include/Common/INI/FieldParse.h"

// ?rva00253475@@YAXAAVMultiIniFieldParse@@@Z @0x00253475 (18B)
void __declspec(noinline) rva00253475(MultiIniFieldParse &p)
{
	p.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 8);
}

// ?ModuleFactoryDataAt00254DB3@@YAPAVModuleData@@PAVINI@@@Z @0x00254DB3 (52B)
ModuleData *ModuleFactoryDataAt00254DB3(INI *ini)
{
	Rva00253487Base *data = new Rva00253487Base;
	if (ini)
		ini->initFromINIMultiProc(data, rva00253475);
	return reinterpret_cast<ModuleData *>(data);
}

extern const FieldParse g_rva004A33BEFieldParseTable[];

// Zero Hour's FieldParse record (INI.h).
void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);

// The condition names at VA 0x00DCBB7C (RVA 0x009CBB7C) that the
// PersistantConditions entry hands parseBitString32; null-terminated.
const char *g_Va00DCBB7C[] =
{
	"ATTACKING", "MOVING", "USING_ABILITY", "FIRING_PRIMARY",
	"FIRING_SECONDARY", "FIRING_TERTIARY", "FIRING_QUATERNARY",
	"FIRING_QUINARY", "MOUNTED", "AWAY_FROM_TREES",
	"HORDEBRAIN_NOT_STEALTHED", "PRIMARY_FORMATION", "TAKING_DAMAGE", 0
};

// Retail's table at VA 0x00C522C0 (RVA 0x008522C0), null-terminated.
extern const FieldParse g_rva004A33BEFieldParseTable[] =
{
	{ "AllowKindOf", Rva002567EAParse, 0, 0x8 },
	{ "Radius", INI::parseReal, 0, 0x24 },
	{ "DelayBetweenUpdates", INI::parseInt, 0, 0x28 },
	{ "PersistantConditions", INI::parseBitString32, g_Va00DCBB7C, 0x140 },
	{ 0, 0, 0, 0 }
};

// ?rva004A33BE@@YAXAAVMultiIniFieldParse@@@Z @0x004A33BE (34B)
void __declspec(noinline) rva004A33BE(MultiIniFieldParse &p)
{
	p.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x30);
	p.add(g_rva004A33BEFieldParseTable, 0);
}

class Rva002553F6
{
public:
	Rva002553F6();

private:
	unsigned char m_pad[0x144];
};

// ?ModuleFactoryDataAt00255440@@YAPAVModuleData@@PAVINI@@@Z @0x00255440 (52B)
ModuleData *ModuleFactoryDataAt00255440(INI *ini)
{
	Rva002553F6 *data = new Rva002553F6;
	if (ini)
		ini->initFromINIMultiProc(data, rva004A33BE);
	return reinterpret_cast<ModuleData *>(data);
}

