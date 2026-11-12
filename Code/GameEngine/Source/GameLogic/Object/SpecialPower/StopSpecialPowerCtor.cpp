// cl: /DNDEBUG /MD
//
// ??0StopSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C676C,
// 46 bytes. Behavior-side ctor completing the StopSpecialPower file-unit
// (ModuleData proc/factory/ctor rowed at 0x4C6751/0x2522B5/0x4C68AB;
// behavior factory rowed at 0x25227D news 0x38 with this pinned 2-arg ctor;
// poolkey rowed at 0x4C67DB).
//
// Shape: frameless single-base ctor over the rowed SpecialPower base 0x493C5A
// (ModuleFactory literal, human-readable pin) with one and-zero member at
// +0x34, then three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (Defector precedent: explicit stores, no virtuals declared
// anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Flat classes throughout keep the body
// frameless. Factory news 0x38 fits the +0x34 tail. Zero new pins (base
// resolves via the existing SpecialPowerModule pin).

extern "C" const void *const __identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00BEFCF8 (38 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva004C67A0@@6B@")[];  // vftable 0x00C5DE08
extern "C" const void *const __identifier("??_7Rva004C67A0@@6BObjectModule@@@")[];  // vftable 0x00C5DE6C

class Thing;
class ModuleData;

class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
private:
	unsigned char m_pad[0x34];
};

class StopSpecialPower : public SpecialPowerModule
{
public:
	StopSpecialPower(Thing *thing, const ModuleData *moduleData);
private:
	int m_34;
};

// ??0StopSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C676C
StopSpecialPower::StopSpecialPower(Thing *thing, const ModuleData *moduleData) :
	SpecialPowerModule(thing, moduleData),
	m_34(0)
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7Rva004C67A0@@6BObjectModule@@@"));
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)__identifier("??_7SpecialPowerModule@@6BBehaviorModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva004C67A0@@6B@"));
}
