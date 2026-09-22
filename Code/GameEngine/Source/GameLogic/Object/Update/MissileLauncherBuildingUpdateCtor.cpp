// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "StoreObjectsSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed MissileLauncherBuildingUpdate.
// stlport
//
// ??0StoreObjectsSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004CD933 (66B). The 0x88-byte UpdateModule-derived intermediate
// base at 0x0044EF5E is unidentified (28 module-ctor callers call it), so it
// is modeled opaque as Rva0044EF5E and pinned; its ctor resolves through
// that pin. The +0x0C/+0x10/+0x20 pointer slots are inherited base members
// the derived body re-stores (address-of TU-local dummies, DIR32-patched).
// The trailing 12-byte vector at +0x88 (the factory news 0x94 bytes) is
// default-constructed in the body through an explicit constructor call on
// byte storage, which reproduces retail's init-list-bypassing order
// (vtable, slots, vector call) and the dead-argument allocator temporary
// at [ebp+0x0F]. The element type is the E16 size stand-in whose
// vector_base pins to retail 0x00211E58. Do NOT declare an explicit vptr
// member on the base: the compiler's hidden vptr already sits at +0 and a
// declared one shifts every slot by 4.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;
static int s_dummy20;

// Opaque 0x88-byte UpdateModule-derived intermediate (vptr + members out to
// +0x84 per the 243B retail body); ctor resolves to the opaque pin at
// 0x0044EF5E. Protected slots mirror the retail stores.
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

class StoreObjectsSpecialPower : public Rva0044EF5E
{
public:
	StoreObjectsSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~StoreObjectsSpecialPower();

private:
	unsigned char m_tailBuf[12];
};

StoreObjectsSpecialPower::StoreObjectsSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy20;
	((_STL::vector<BfmeE16> *)m_tailBuf)->_STL::vector<BfmeE16>::vector();
}

// ??1StoreObjectsSpecialPower@@ present-unmatched
StoreObjectsSpecialPower::~StoreObjectsSpecialPower()
{
}
