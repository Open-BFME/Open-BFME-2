// cl: /DNDEBUG /MD /GX
//
// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail
// 0x004A65AE 120 bytes. Behavior-side ctor completing the
// SupplyCenterProductionExitUpdate file-unit (behavior instance factory rowed
// at 0x24EE3F news 0x34 with this 2-arg ctor as its sole caller; poolkey
// rowed at 0x4A6569; ModuleData side lives in the twin-owned
// SupplyCenterProductionExitUpdateCtor.cpp shard, untouched here).
//
// Shape follows the DefaultProductionExitUpdate behavior recipe over the same
// rowed UpdateModule base 0x253390: two-phase +0x20 slot (C430B4-then-C52D00
// via sourced-before address-take) plus a byte zero at +0x30 plus float zeros
// at +0x24/+0x28/+0x2C via an xmm0-homed fzero local (/arch:SSE flips x87
// fldz to retail xorps+movss) plus the setWakeFrame tail (m_object at
// +0x08 with the 0x3FFFFFFF never-wake literal). The sourced-before takes
// pin the push-imm between the stores: slot20 take holds the +0x20 store
// early and ready take plus object take split the call pushes to retail
// positions (take-split law). /GX for the EH prologue plus the single
// early state store; the declared-only base dtor arms it with no emitted
// code. Zero new pins (base ctor resolves via its row; setWakeFrame
// resolves via the existing IAEX Object-uint pin at 0x44DF71). Row
// supersedes the ctor pin.

extern "C" const void *const __identifier("??_7ContainIface30@@6B@")[];  // folded vftable 0x00C430B4 (2 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7SpawnPointProductionExitUpdate@@6BUpdateModule@@@")[];  // folded vftable 0x00C4B1E0 (5 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7SpawnPointProductionExitUpdate@@6BBehaviorModuleInterface@@@")[];  // folded vftable 0x00C4B1F0 (4 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7SupplyCenterProductionExitUpdate@@6BRva004A653D_E1@@@")[];  // vftable 0x00C52D00
extern "C" const void *const __identifier("??_7SupplyCenterProductionExitUpdate@@6BObjectModule@@@")[];  // vftable 0x00C52D30

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
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

class SupplyCenterProductionExitUpdate : public UpdateModule
{
public:
	SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	float m_doorDelay24;
	float m_queueDelay28;
	float m_idleDelay2C;
	unsigned char m_exitReady30;
};

// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A65AE
SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)((unsigned int)__identifier("??_7ContainIface30@@6B@"));
	unsigned char *readySlot = &m_exitReady30;
	Object **objSlot = &m_object;
	m_vtable = (const void *)((unsigned int)__identifier("??_7SupplyCenterProductionExitUpdate@@6BObjectModule@@@"));
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7SpawnPointProductionExitUpdate@@6BBehaviorModuleInterface@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7SpawnPointProductionExitUpdate@@6BUpdateModule@@@"));
	m_secondary20 = (const void *)((unsigned int)__identifier("??_7SupplyCenterProductionExitUpdate@@6BRva004A653D_E1@@@"));
	*readySlot = 0;
	m_doorDelay24 = fzero;
	m_queueDelay28 = fzero;
	m_idleDelay2C = fzero;
	setWakeFrame(*objSlot, UPDATE_SLEEP_FOREVER);
}
