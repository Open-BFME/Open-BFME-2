// cl: /O1 /DNDEBUG /MD
//
// ??0SpecialPowerTimerRefreshSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251BDE, 40 bytes. Behavior-side ctor completing the
// SpecialPowerTimerRefreshSpecialPower file-unit (poolkey rowed at
// 0x251C31, name getter rowed at 0x251C76, behavior instance factory rowed
// at 0x254B1E news 0x18 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed SpecialPowerModule base
// 0x493C5A with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed SpecialPowerModule spelling).

class Thing;
class ModuleData;

class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
};

class SpecialPowerTimerRefreshSpecialPower : public SpecialPowerModule
{
public:
	SpecialPowerTimerRefreshSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0SpecialPowerTimerRefreshSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x00251BDE
SpecialPowerTimerRefreshSpecialPower::SpecialPowerTimerRefreshSpecialPower(Thing *thing, const ModuleData *moduleData) :
	SpecialPowerModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00BEFDB4;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFCF8;
	*(unsigned int *)((char *)this + 0x10) = 0x00C5E080;
}
