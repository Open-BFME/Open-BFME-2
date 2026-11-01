// cl: /DNDEBUG /MD /GX
//
// ??0BloodthirstyUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0044E0AA,
// 105 bytes. BloodthirstyUpdate behavior ctor over the rowed UpdateModule
// base (0x253390): re-stores the primary vtable slot (the behavior vtable
// 0x00C3F0B4) and the +0x0C/+0x10/+0x20 secondary slots (address-of TU-local
// dummies is wrong here; retail carries literal secondary installs, so the
// slots are explicit members), zeroes the scan members, and parks the module
// awake through setWakeFrame. Member names follow the BFME1 BloodthirstyUpdate
// donor (m_object at +0x08, UPDATE_SLEEP_NONE, scan members at +0x24/+0x28/
// +0x2C); the +0x20 slot is the secondary interface word the donor carries as
// BloodthirstyUpdateIface, initialized retail-first to 0x00BFBCBC and then
// installed retail-last to 0x00C3EFC4.
//
// Scheduling notes: the setWakeFrame call sits last in source while the
// compiler hoists its push/mov-ecx setup above the stores; the sourced-before
// wakeSlot pointer (address-take idiom, zero emitted bytes) commits the first
// +0x20 store above that hoist, which plain source order cannot hold. /GX for
// the EH prologue plus the single mid-body state store; the declared-only
// base dtor arms it with no emitted code. Recipe: PlayerHealSpecialPowerCtor
// plus AIGateUpdateCtor over the same rowed base.

extern "C" const void *const __identifier("??_7Rva005F0584Base0@@6B@")[];  // folded vftable 0x00BFBCBC (2 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7BloodthirstyUpdate@@6BBloodthirstyUpdateIface@@@")[];  // vftable 0x00C3EFC4
extern "C" const void *const __identifier("??_7BloodthirstyUpdate@@6BUpdateModule@@@")[];  // vftable 0x00C3EFEC
extern "C" const void *const __identifier("??_7BloodthirstyUpdate@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C3EFF8
extern "C" const void *const __identifier("??_7BloodthirstyUpdate@@6BObjectModule@@@")[];  // vftable 0x00C3F0B4

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class BloodthirstyUpdate : public UpdateModule
{
public:
	BloodthirstyUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	unsigned int m_bestTargetID;
	unsigned int m_inRange;
	unsigned int m_nextScanFrames;
};

// ??0BloodthirstyUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x44E0AA
BloodthirstyUpdate::BloodthirstyUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *wakeSlot = (int *)&m_secondary20;
	*wakeSlot = (int)((unsigned int)__identifier("??_7Rva005F0584Base0@@6B@"));
	m_vtable = (const void *)((unsigned int)__identifier("??_7BloodthirstyUpdate@@6BObjectModule@@@"));
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7BloodthirstyUpdate@@6BBehaviorModuleInterface@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7BloodthirstyUpdate@@6BUpdateModule@@@"));
	m_secondary20 = (const void *)((unsigned int)__identifier("??_7BloodthirstyUpdate@@6BBloodthirstyUpdateIface@@@"));
	m_bestTargetID = 0;
	m_inRange = 0;
	m_nextScanFrames = 0;
	setWakeFrame(m_object, (UpdateSleepTime)UPDATE_SLEEP_NONE);
}
