// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CommandPointsUpgradeModuleData@@QAE@XZ, retail 0x00254891, 65 bytes.
// EH ctor over the rowed OpenContainModuleData base (0x253487, frameless and
// therefore not unwindable): base call, single state-0 store, the compact
// and-zero of CommandPoints at +0x118, the lea of RequiredObject at +0x11C,
// the distinctive vtable literal 0x00BF2658, then the filter construction
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

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	~OpenContainModuleData();
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

	unsigned char m_data[4];
};

class CommandPointsUpgradeModuleData : public OpenContainModuleData
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
	: m_vtable(reinterpret_cast<void *>(0x00BF2658)),
	m_commandPoints(0),
	m_requiredObject()
{
}
