// cl: /O1 /GX /MD /DNDEBUG
//
// ??0DualWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z at retail
// 0x0045AE55, 88 bytes. Behavior-side ctor in the DualWeapon file-unit:
// pool key 0x45ADE0 (DualWeaponBehavior string) ends where the ModuleData
// ctor 0x45AE25 begins, proc 0x45AE44 (SwitchWeapon table) ends where this
// ctor begins, and ??_G 0x45AEAD starts where this ctor ends. The rowed
// UpdateModule base ctor (0x253390) plus the setWakeFrame pin (0x44DF71)
// carry the frame; the derived class re-stores the inherited +0x0C/+0x10
// slots, zeroes its close-range flag and switch timer through one shared
// zero register, then keeps itself awake with setWakeFrame(obj, 1).
// Shape follows the BoredUpdate/PrisonDockUpdate behavior-ctor precedent:
// opaque single-vptr base, declared-only dtors driving the single EH state
// with zero emitted code. Member names are inferred from the SwitchWeapon
// table (MinimumSwitchTime, UseCloseRangeWhileMounted); the +0x0C/+0x10
// targets are TU-local dummies (DIR32-masked, identity rests on the
// file-unit, not their values).

class Thing;
class ModuleData;
class Object;

static int s_dualWeapon0C;
static int s_dualWeapon10;

// Opaque UpdateModule (0x20 bytes); ctor resolves to the matched row at
// 0x00253390, setWakeFrame to the pin at 0x0044DF71.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, unsigned int frame);
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
};

class DualWeaponBehavior : public UpdateModule
{
public:
	DualWeaponBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~DualWeaponBehavior();

private:
	bool m_closeRangeActive; // +0x20
	int m_switchTimer; // +0x24
};

// ??0DualWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x45AE55
DualWeaponBehavior::DualWeaponBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int zero = 0;
	m_p0C = &s_dualWeapon0C;
	m_p10 = &s_dualWeapon10;
	m_closeRangeActive = (unsigned char)zero;
	m_switchTimer = zero;
	setWakeFrame(*(Object **)((char *)this + 8), 1);
}
