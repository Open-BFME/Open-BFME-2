// cl: /O1 /DNDEBUG /MD
//
// ??0HeroDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C2324, 42 bytes.
// Behavior-side ctor completing the HeroDie file-unit (poolkey rowed at
// 0x4C22C9, behavior instance factory rowed at 0x25185B news 0x34 with this
// ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the pinned DieModule base 0x45CEBD
// with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise pointer
// casts (StopSpecialPower precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// existing DieModule pin).

class Thing;
class ModuleData;

class DieModule
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);
};

class HeroDie : public DieModule
{
public:
	HeroDie(Thing *thing, const ModuleData *moduleData);
};

// ??0HeroDie@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C2324
HeroDie::HeroDie(Thing *thing, const ModuleData *moduleData) :
	DieModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00C5C428;
	*(unsigned int *)((char *)this + 0xC) = 0x00C4A650;
	*(unsigned int *)((char *)this + 0x10) = 0x00C5C424;
}
