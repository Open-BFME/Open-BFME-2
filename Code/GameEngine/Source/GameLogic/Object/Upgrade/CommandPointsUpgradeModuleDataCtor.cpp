char g_00BF2658;

// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CommandPointsUpgradeModuleData@@QAE@XZ, retail 0x00254891, 65 bytes.
// EH ctor over the rowed Rva00253487Base base (0x253487, frameless and
// therefore not unwindable): base call, single state-0 store, the compact
// and-zero of CommandPoints at +0x118, the lea of RequiredObject at +0x11C,
// the distinctive vtable literal (unsigned int)&g_00BF2658, then the filter construction
// through the opaque 0x3623E5 pin (EnragedUpdateModuleDataCtor precedent:
// same mangled owner, 4 bytes of storage, declared dtor). Size 0x120
// matches the rowed ModuleData factory at 0x2548D2 (sole raw caller, news
// 0x120). Class identity is the table 0x00C590E8 (CommandPoints at +0x118,
// RequiredObject at +0x11C) beside the rowed chained proc. Scheduling: the
// all-init-list shape (vtable, int-zero, filter, in decl order) reproduces
// retail and-lea-vtable-call exactly — the RMW-and hoists above the vtable
// store while the pure lea hoists between them (FreeLifeBodyModuleDataCtor
// precedent); the TU-local base stays empty (EBO) with a declared-only dtor
// so it arms the single EH state with zero emitted code (Topple/Enraged
// precedent), and the derived owns the vtable slot at +0 over the base
// extent, overwriting the base-installed vtable exactly as retail.

class Rva00253487Base
{
public:
	Rva00253487Base();
	~Rva00253487Base();
};

#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class CommandPointsUpgradeModuleData : public Rva00253487Base
{
public:
	CommandPointsUpgradeModuleData();

private:
	void *m_vtable; // +0 (derived-owned over the EBO-empty base)
	unsigned char m_pad[0x114]; // +4..+0x117 (base extent)
	int m_commandPoints; // +0x118
	Rva003623E5Member m_requiredObject; // +0x11C
};

// ??0CommandPointsUpgradeModuleData@@QAE@XZ @0x254891
CommandPointsUpgradeModuleData::CommandPointsUpgradeModuleData()
	: m_vtable(reinterpret_cast<void *>((unsigned int)&g_00BF2658)),
	m_commandPoints(0),
	m_requiredObject()
{
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1Rva00253487Base@@QAE@XZ=??3@YAXPAX@Z")
