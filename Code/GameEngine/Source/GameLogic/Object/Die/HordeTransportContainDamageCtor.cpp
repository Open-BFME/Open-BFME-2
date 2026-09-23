// cl: /O1 /DNDEBUG /MD
//
// ??0HordeTransportContainDamage@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BB130, 40 bytes. Behavior-side ctor completing the
// HordeTransportContainDamage file-unit (poolkey rowed at 0x4BB0EB,
// ModuleData factory rowed at 0x250ED4, behavior instance factory rowed at
// 0x250E9C news 0x34 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the pinned DamageModule base
// 0x4B9704 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// existing DamageModule pin; rowing the base is parked on a same-value
// scheduling wall, stash 0x004B9704).

class Thing;
class ModuleData;

class DamageModule
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
};

class HordeTransportContainDamage : public DamageModule
{
public:
	HordeTransportContainDamage(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeTransportContainDamage@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB130
HordeTransportContainDamage::HordeTransportContainDamage(Thing *thing, const ModuleData *moduleData) :
	DamageModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00C59E70;
	*(unsigned int *)((char *)this + 0xC) = 0x00C597F8;
	*(unsigned int *)((char *)this + 0x10) = 0x00C59E64;
}
