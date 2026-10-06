// cl: /DNDEBUG /MD
//
// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253E64, 40 bytes. Behavior-side ctor completing the
// NotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey rowed at
// 0x253E8E, name getter rowed at 0x253ED3, behavior instance factory rowed
// at 0x255207 news 0x34 with this ctor as sole raw caller; the Horde twin
// keeps its own poolkey 0x253DB2, factory 0x2551CF and pinned ctor 0x253D88).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00BF1860[];  // ??_7Rva00253EF5@@6BRva00253EF5_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF1860=??_7Rva00253EF5@@6BRva00253EF5_B2@@@")
extern "C" const void *const vtbl_00BF186C[];  // ??_7Rva00253EF5@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF186C=??_7Rva00253EF5@@6BRva0024A797@@@")

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class NotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253E64
NotifyTargetsOfImminentProbableCrushingUpdate::NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF186C);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00BEFF90);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00BF1860);
}
