// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00490D3F@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00490D3F (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (address-of TU-local dummies, DIR32-patched: 0xC4D640 /
// 0xC4DEE8 / 0xC552A4). No trailing members (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24D67B factory stub.
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

class Rva00490D3F : public Rva0044EF5E
{
public:
	Rva00490D3F(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00490D3F();
};

Rva00490D3F::Rva00490D3F(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy20;
}

// ~Rva00490D3F (retail 0x00490D76) and its deleting destructor are defined in
// ModuleUpdateDtors.cpp.
