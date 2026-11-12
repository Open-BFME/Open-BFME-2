// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "EvacuateGarrisonSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SupplyCenterDockUpdate.
// stlport
//
// ??0EvacuateGarrisonSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004CDBFC (47B). Same opaque-base pattern as MissileLauncherBuildingUpdate:
// unidentified 0x88-byte UpdateModule-derived intermediate base 0x0044EF5E
// (pinned opaque as Rva0044EF5E); the derived body re-stores the inherited
// +0x0C/+0x10/+0x20 pointer slots (address-of TU-local dummies,
// DIR32-patched). No trailing members (factory size 0x88). Do NOT declare an
// explicit vptr member on the base: the compiler's hidden vptr already sits
// at +0 and a declared one shifts every slot by 4.
class Thing;
class ModuleData;

extern "C" char __identifier("??_7ArrowStormUpdate@@6BBehaviorModuleInterface@@@");
extern "C" char __identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@");
// +0x20: retail stores 0x00C552A4, SpecialAbilityUpdate's SpecialPowerUpdateInterface
// table (ICF-shared); the ledger binds this compiled name there.
extern "C" char __identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@");

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

class EvacuateGarrisonSpecialPower : public Rva0044EF5E
{
public:
	EvacuateGarrisonSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~EvacuateGarrisonSpecialPower();
};

EvacuateGarrisonSpecialPower::EvacuateGarrisonSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &__identifier("??_7ArrowStormUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = &__identifier("??_7ArrowStormUpdate@@6BUpdateModule@@@");
	m_p20 = &__identifier("??_7SpecialAbilityUpdate@@6BSpecialPowerUpdateInterface@@@");
}

