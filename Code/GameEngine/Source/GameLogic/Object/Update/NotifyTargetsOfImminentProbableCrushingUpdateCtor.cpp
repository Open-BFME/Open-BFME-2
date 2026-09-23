// cl: /O1 /DNDEBUG /MD
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
	*(unsigned int *)this = 0x00BF186C;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFF90;
	*(unsigned int *)((char *)this + 0x10) = 0x00BF1860;
}
