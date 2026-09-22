// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "CurseSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SpawnPointProductionExitUpdate.
// stlport
//
// ??0CurseSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004CCD7F (47B). Same opaque-base pattern as MissileLauncherBuildingUpdate:
// unidentified 0x88-byte UpdateModule-derived intermediate base 0x0044EF5E
// (pinned opaque as Rva0044EF5E); the derived body re-stores the inherited
// +0x0C/+0x10/+0x20 pointer slots (address-of TU-local dummies,
// DIR32-patched). No trailing members (factory size 0x88). Do NOT declare an
// explicit vptr member on the base: the compiler's hidden vptr already sits
// at +0 and a declared one shifts every slot by 4.
class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;
static int s_dummy20;

// Opaque 0x88-byte UpdateModule-derived intermediate; ctor resolves to the
// opaque pin at 0x0044EF5E. Protected slots mirror the retail stores.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
	const void *m_p20;
	unsigned char m_pad2[0x88 - 0x24];
};

// ??1Rva0044EF5E@@ present-unmatched
Rva0044EF5E::~Rva0044EF5E()
{
}

class CurseSpecialPower : public Rva0044EF5E
{
public:
	CurseSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~CurseSpecialPower();
};

CurseSpecialPower::CurseSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy20;
}

// ??1CurseSpecialPower@@ present-unmatched
CurseSpecialPower::~CurseSpecialPower()
{
}
