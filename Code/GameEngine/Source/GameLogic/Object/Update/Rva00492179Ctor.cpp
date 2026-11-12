// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00492179@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00492179 (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (address-of TU-local dummies, DIR32-patched: 0xC4D640 /
// 0xC4DEE8 / 0xC552A4). No trailing members (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24D9D2 factory stub.
// The paired dtor (0x004921B0, ModuleUpdateDtors.cpp) is already rowed (same consts).
class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7ArrowStormUpdate@@6BBehaviorModuleInterface@@@")[];
extern "C" const void *const __identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@")[];
// +0x20: retail stores 0x00C552A4, SpecialAbilityUpdate's SpecialPowerUpdateInterface
// table (ICF-shared); the ledger binds this compiled name there.
extern "C" const void *const __identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@")[];

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

class Rva00492179 : public Rva0044EF5E
{
public:
	Rva00492179(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00492179();
};

Rva00492179::Rva00492179(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = __identifier("??_7ArrowStormUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@");
	m_p20 = __identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@");
}

// ~Rva00492179 (retail 0x004921B0) and its deleting destructor are defined in
// ModuleUpdateDtors.cpp.
