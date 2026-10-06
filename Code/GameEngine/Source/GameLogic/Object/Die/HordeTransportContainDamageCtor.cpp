// cl: /DNDEBUG /MD
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

extern "C" const void *const vtbl_00C597F8[];  // folded, 6 classes; via ??_7BoneFXDamage@@6BBehaviorModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C597F8=??_7BoneFXDamage@@6BBehaviorModuleInterface@@@")

extern "C" const void *const vtbl_00C59E64[];  // ??_7Rva004BB0CC@@6BRva004BB0CC_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C59E64=??_7Rva004BB0CC@@6BRva004BB0CC_B2@@@")
extern "C" const void *const vtbl_00C59E70[];  // ??_7Rva004BB0CC@@6BRva004B96CC@@@
#pragma comment(linker, "/alternatename:_vtbl_00C59E70=??_7Rva004BB0CC@@6BRva004B96CC@@@")

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
	*(unsigned int *)this = ((unsigned int)vtbl_00C59E70);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00C597F8);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C59E64);
}
