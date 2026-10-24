// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "HordeDispatchSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SupplyTruckAIUpdate.
// stlport
//
// ??0HordeDispatchSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004C89E6 (47B). The intermediate base is SpecialPowerModule:
// retail's derived E8 targets 0x00493C5A, rowed as
// ??0SpecialPowerModule@@QAE@PAVThing@@PBVModuleData@@@Z (330B,
// SpecialPowerModuleCtor.cpp), same (Thing*, ModuleData*) ABI; the base
// dtor resolves to rowed ??1SpecialPowerModule@@MAE@XZ (0x00493DEF).
// The derived body re-stores the inherited +0x0C/+0x10 pointer slots
// (address-of TU-local dummies, DIR32-patched). No trailing members
// (factory size 0x88). Do NOT declare an explicit vptr member on the base:
// the compiler's hidden vptr already sits at +0 and a declared one shifts
// every slot by 4.
class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;

// Minimal ABI view of SpecialPowerModule: only the ctor/dtor the derived
// body binds (rowed 0x00493C5A / 0x00493DEF). Protected slots mirror the
// retail stores; the full virtual sequence lives in SpecialPowerModuleCtor.
class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~SpecialPowerModule();
public:

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x88 - 0x14];
};

class HordeDispatchSpecialPower : public SpecialPowerModule
{
public:
	HordeDispatchSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeDispatchSpecialPower();
};

HordeDispatchSpecialPower::HordeDispatchSpecialPower(Thing *thing, const ModuleData *moduleData)
	: SpecialPowerModule(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
}

// ??1HordeDispatchSpecialPower@@ present-unmatched
HordeDispatchSpecialPower::~HordeDispatchSpecialPower()
{
}
