// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "HordeDispatchSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SupplyTruckAIUpdate.
// stlport
//
// ??0HordeDispatchSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004C89E6 (47B). Same opaque-base pattern as MissileLauncherBuildingUpdate:
// unidentified 0x88-byte UpdateModule-derived intermediate base 0x00493C5A
// (pinned opaque as Rva00493C5A); the derived body re-stores the inherited
// +0x0C/+0x10/+0x20 pointer slots (address-of TU-local dummies,
// DIR32-patched). No trailing members (factory size 0x88). Do NOT declare an
// explicit vptr member on the base: the compiler's hidden vptr already sits
// at +0 and a declared one shifts every slot by 4.
class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;

// Opaque 0x88-byte UpdateModule-derived intermediate; ctor resolves to the
// opaque pin at 0x00493C5A. Protected slots mirror the retail stores.
class Rva00493C5A
{
public:
	Rva00493C5A(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00493C5A();

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x88 - 0x14];
};

// ??1Rva00493C5A@@ present-unmatched
Rva00493C5A::~Rva00493C5A()
{
}

class HordeDispatchSpecialPower : public Rva00493C5A
{
public:
	HordeDispatchSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeDispatchSpecialPower();
};

HordeDispatchSpecialPower::HordeDispatchSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva00493C5A(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
}

// ??1HordeDispatchSpecialPower@@ present-unmatched
HordeDispatchSpecialPower::~HordeDispatchSpecialPower()
{
}
