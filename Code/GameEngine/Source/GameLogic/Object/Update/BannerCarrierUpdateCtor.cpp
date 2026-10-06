// cl: /DNDEBUG /MD
//
// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00496A98,
// 42 bytes. Behavior-side ctor completing the BannerCarrierUpdate file-unit
// (poolkey rowed at 0x496A1E, behavior instance factory rowed at 0x24E173
// news 0x34 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C4F82C[];  // ??_7Rva004969FF@@6BRva004969FF_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4F82C=??_7Rva004969FF@@6BRva004969FF_B2@@@")
extern "C" const void *const vtbl_00C4F838[];  // ??_7Rva004969FF@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4F838=??_7Rva004969FF@@6BRva0024A797@@@")

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class BannerCarrierUpdate : public UpdateModule
{
public:
	BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0BannerCarrierUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00496A98
BannerCarrierUpdate::BannerCarrierUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C4F838);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00BEFF90);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C4F82C);
}
