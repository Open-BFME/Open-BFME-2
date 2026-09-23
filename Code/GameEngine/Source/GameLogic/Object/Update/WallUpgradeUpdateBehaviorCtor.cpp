// cl: /O1 /DNDEBUG /MD /GX
//
// ??0WallUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AB317,
// 121 bytes. Behavior-side ctor completing the WallUpgradeUpdate file-unit
// (behavior factory rowed at 0x24F2EF news 0x34 with this pinned 2-arg ctor;
// poolkey rowed at 0x4AB2D2).
//
// Shape follows Bloodthirsty precedent verbatim over the same rowed
// UpdateModule base 0x253390: re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x20/+0x24 secondary slots (explicit members, all immediates
// DIR32-masked) plus two int zeros at +0x28/+0x2C plus bytes 1/0 at
// +0x30/+0x31, and parks the module awake-through-none via setWakeFrame.
// Member names follow the Bloodthirsty donor (m_object at +0x08,
// UPDATE_SLEEP_NONE, int members at +0x24/+0x28/+0x2C); the +0x20/+0x24
// slots are secondary interface words, initialized retail-first to
// 0x00BE2B78/0x00C1C780 and then installed retail-last to
// 0x00C54768/0x00C54764.
//
// Scheduling notes: the setWakeFrame call sits last in source while the
// compiler hoists its push/mov-ecx setup above the stores; the sourced-before
// wakeSlot pointers (address-take idiom, zero emitted bytes) commit the first
// +0x20/+0x24 stores above that hoist, which plain source order cannot hold.
// /GX for the EH prologue plus the single mid-body state store; the
// declared-only base dtor arms it with no emitted code.

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
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class WallUpgradeUpdate : public UpdateModule
{
public:
	WallUpgradeUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	const void *m_secondary24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_pad32[2];
};

// ??0WallUpgradeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004AB317
WallUpgradeUpdate::WallUpgradeUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *wakeSlot20 = (int *)&m_secondary20;
	*wakeSlot20 = (int)0x00BE2B78;
	int *wakeSlot24 = (int *)&m_secondary24;
	*wakeSlot24 = (int)0x00C1C780;
	m_vtable = (const void *)0x00C54780;
	m_secondary0C = (const void *)0x00C49800;
	m_secondary10 = (const void *)0x00C54774;
	m_secondary20 = (const void *)0x00C54768;
	m_secondary24 = (const void *)0x00C54764;
	m_28 = 0;
	m_2C = 0;
	m_30 = 1;
	m_31 = 0;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
