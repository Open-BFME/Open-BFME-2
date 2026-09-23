// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004A65AE, 118 bytes. Behavior-side ctor completing the
// SupplyCenterProductionExitUpdate file-unit (behavior factory rowed at
// 0x24EE3F news 0x34 with this pinned 2-arg ctor; poolkey rowed at
// 0x4A6569).
//
// Shape follows Bloodthirsty precedent verbatim over the same rowed
// UpdateModule base 0x253390: re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x20 secondary slots (explicit members, all immediates
// DIR32-masked) plus three float zeros at +0x24/+0x28/+0x2C via movss
// (xorps setup, /arch:SSE lever) plus a byte zero at +0x30, and parks the
// module awake-through-forever via setWakeFrame. Member names follow the
// Bloodthirsty donor (m_object at +0x08, UPDATE_SLEEP_FOREVER,
// float members at +0x24/+0x28/+0x2C); the +0x20 slot is the secondary
// interface word, initialized retail-first to 0x00C430B4 and then installed
// retail-last to 0x00C52D00.
//
// Scheduling notes: the setWakeFrame call sits last in source while the
// compiler hoists its push/mov-ecx setup above the stores; the sourced-before
// wakeSlot pointer (address-take idiom, zero emitted bytes) commits the first
// +0x20 store above that hoist, which plain source order cannot hold. /GX for
// the EH prologue plus the single mid-body state store; the declared-only
// base dtor arms it with no emitted code.

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
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

class SupplyCenterProductionExitUpdate : public UpdateModule
{
public:
	SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	float m_24;
	float m_28;
	float m_2C;
	unsigned char m_30;
	unsigned char m_pad31[3];
};

// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A65AE
SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *wakeSlot = (int *)&m_secondary20;
	*wakeSlot = (int)0x00C430B4;
	m_vtable = (const void *)0x00C52D30;
	m_secondary0C = (const void *)0x00C4B1F0;
	m_secondary10 = (const void *)0x00C4B1E0;
	m_secondary20 = (const void *)0x00C52D00;
	m_30 = 0;
	_ReadWriteBarrier();
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0.0f;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
