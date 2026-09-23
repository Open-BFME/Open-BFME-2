// cl: /O1 /DNDEBUG /MD
//
// ??0SpawnedModelConditionCreate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00250A1F, 40 bytes. Behavior-side ctor completing the
// SpawnedModelConditionCreate file-unit (poolkey rowed at 0x250A4E,
// name getter rowed at 0x250A93, behavior instance factory rowed at
// 0x25496D news 0x18 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed CreateModule base
// 0x4B8CF7 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed CreateModule spelling).

class Thing;
class ModuleData;

class CreateModule
{
public:
	CreateModule(Thing *thing, const ModuleData *moduleData);
};

class SpawnedModelConditionCreate : public CreateModule
{
public:
	SpawnedModelConditionCreate(Thing *thing, const ModuleData *moduleData);
};

// ??0SpawnedModelConditionCreate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00250A1F
SpawnedModelConditionCreate::SpawnedModelConditionCreate(Thing *thing, const ModuleData *moduleData) :
	CreateModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00BEFA7C;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEF9C0;
	*(unsigned int *)((char *)this + 0x10) = 0x00BEF9B0;
}
