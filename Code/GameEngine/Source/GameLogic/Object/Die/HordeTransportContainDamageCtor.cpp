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

extern "C" const void *const __identifier("??_7EvacuateDamage@@6BPB_Iface1@@@")[];  // folded vftable 0x00C597F8 (6 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva004BB0CC@@6BRva004BB0CC_B2@@@")[];  // vftable 0x00C59E64
extern "C" const void *const __identifier("??_7Rva004BB0CC@@6BRva004B96CC@@@")[];  // vftable 0x00C59E70

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"

class HordeTransportContainDamage : public DamageModule
{
public:
	HordeTransportContainDamage(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeTransportContainDamage@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB130
HordeTransportContainDamage::HordeTransportContainDamage(Thing *thing, const ModuleData *moduleData) :
	DamageModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7Rva004BB0CC@@6BRva004B96CC@@@"));
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7EvacuateDamage@@6BPB_Iface1@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva004BB0CC@@6BRva004BB0CC_B2@@@"));
}
