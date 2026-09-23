// cl: /O1 /DNDEBUG /MD
//
// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253D88, 40 bytes. Behavior-side ctor completing the
// HordeNotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey
// rowed at 0x253DB2, behavior instance factory rowed at 0x2551CF news 0x34
// with this ctor as sole raw caller; the non-Horde twin keeps its own
// poolkey 0x253E8E, factory 0x255207 and rowed ctor 0x253E64).
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

class HordeNotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253D88
HordeNotifyTargetsOfImminentProbableCrushingUpdate::HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00BF17F8;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFF90;
	*(unsigned int *)((char *)this + 0x10) = 0x00BF17EC;
}
