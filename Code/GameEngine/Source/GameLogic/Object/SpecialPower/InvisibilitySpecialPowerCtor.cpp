// cl: /O1 /DNDEBUG /MD
//
// ??0InvisibilitySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004C23A4, 42 bytes. Behavior-side ctor completing the
// InvisibilitySpecialPower file-unit (poolkey rowed at 0x4C23D4, ModuleData
// proc/factory/ctor rowed at 0x4C2389/0x2518CB/0x4C244D, behavior instance
// factory rowed at 0x251893 news 0x34 with this ctor as sole raw caller).
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

class InvisibilitySpecialPower : public SpecialPowerModule
{
public:
	InvisibilitySpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0InvisibilitySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C23A4
InvisibilitySpecialPower::InvisibilitySpecialPower(Thing *thing, const ModuleData *moduleData) :
	SpecialPowerModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00C5C51C;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFCF8;
	*(unsigned int *)((char *)this + 0x10) = 0x00C5C4B8;
}
