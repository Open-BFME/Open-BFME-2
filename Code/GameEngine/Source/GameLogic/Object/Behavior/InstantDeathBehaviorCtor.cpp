// cl: /DNDEBUG /MD
//
// ??0InstantDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045CF55,
// 42 bytes. Behavior-side ctor completing the InstantDeathBehavior file-unit
// (poolkey rowed at 0x45CF10, ModuleData factory rowed at 0x24B213,
// behavior instance factory rowed at 0x24B1DB news 0x34 with this ctor as
// sole raw caller).
//
// Shape: frameless single-base ctor over the pinned DieModule base 0x45CEBD
// with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise pointer
// casts (StopSpecialPower precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// existing DieModule pin).

extern "C" const void *const vtbl_00C4A650[];  // folded, 21 classes; via ??_7CreateCrateDie@@6BBehaviorModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4A650=??_7CreateCrateDie@@6BBehaviorModuleInterface@@@")

extern "C" const void *const vtbl_00C41E44[];  // ??_7Rva0045CE6D@@6BRva0045CE6D_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C41E44=??_7Rva0045CE6D@@6BRva0045CE6D_B2@@@")
extern "C" const void *const vtbl_00C41E48[];  // ??_7Rva0045CE6D@@6BDieModule@@@
#pragma comment(linker, "/alternatename:_vtbl_00C41E48=??_7Rva0045CE6D@@6BDieModule@@@")

class Thing;
class ModuleData;

class DieModule
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);
};

class InstantDeathBehavior : public DieModule
{
public:
	InstantDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0InstantDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045CF55
InstantDeathBehavior::InstantDeathBehavior(Thing *thing, const ModuleData *moduleData) :
	DieModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C41E48);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00C4A650);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C41E44);
}
