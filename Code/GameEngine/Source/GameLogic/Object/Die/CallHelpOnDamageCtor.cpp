// cl: /DNDEBUG /MD
//
// ??0CallHelpOnDamage@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BB43C,
// 44 bytes. Behavior-side ctor completing the CallHelpOnDamage file-unit
// (poolkey rowed at 0x4BB470, ModuleData factory rowed at 0x250F5D,
// behavior instance factory rowed at 0x250F25 news 0x34 with this ctor as
// sole raw caller).
//
// Shape: frameless single-base ctor over the pinned DamageModule base
// 0x4B9704 with a leading and-zero member at +0x14 plus three explicit
// vtable stores at +0/+0xC/+0x10 via byte-wise pointer casts (and-first
// order is natural under /O1; no virtuals declared anywhere so no vtable
// is emitted here; all three immediates are DIR32-masked in comparison).
// Zero new pins (base resolves via the existing DamageModule pin).

extern "C" const void *const vtbl_00C597F8[];  // folded, 6 classes; via ??_7BoneFXDamage@@6BBehaviorModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C597F8=??_7BoneFXDamage@@6BBehaviorModuleInterface@@@")

class Thing;
class ModuleData;

class DamageModule
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
};

class CallHelpOnDamage : public DamageModule
{
public:
	CallHelpOnDamage(Thing *thing, const ModuleData *moduleData);
};

// ??0CallHelpOnDamage@@QAE@PAVThing@@PBVModuleData@@@Z @0x004BB43C
CallHelpOnDamage::CallHelpOnDamage(Thing *thing, const ModuleData *moduleData) :
	DamageModule(thing, moduleData)
{
	*(int *)((char *)this + 0x14) = 0;
	*(unsigned int *)this = 0x00C59FDC;
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00C597F8);
	*(unsigned int *)((char *)this + 0x10) = 0x00C59FD0;
}
