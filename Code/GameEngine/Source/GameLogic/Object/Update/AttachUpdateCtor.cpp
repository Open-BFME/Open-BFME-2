// cl: /DNDEBUG /MD /GX
//
// ??0AttachUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00491A0F,
// 89 bytes. Behavior-side ctor completing the AttachUpdate file-unit
// (ModuleData proc/factory rowed at 0x491957/0x24D8D2; poolkey rowed at
// 0x491912; behavior instance factory rowed at 0x24D89A news 0x14 with this
// pinned 2-arg ctor as its caller).
//
// Shape follows WallUpgradeUpdate precedent verbatim over the same rowed
// UpdateModule base 0x253390: re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (explicit members, all immediates
// DIR32-masked) plus an and-zero int at +0x20 plus an or-minus-one int at
// +0x24, and parks the module awake-through-none via setWakeFrame.
// Member names follow the Bloodthirsty donor (m_object at +0x08,
// UPDATE_SLEEP_NONE). /GX for the EH prologue plus the single mid-body
// state store; the declared-only base dtor arms it with no emitted code.
// Zero new pins (base ctor resolves via its row; setWakeFrame resolves via
// the existing IAEX Object-uint pin at 0x44DF71).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C4DB14[];  // ??_7Rva0049188D@@6BRva0049188D_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4DB14=??_7Rva0049188D@@6BRva0049188D_B2@@@")
extern "C" const void *const vtbl_00C4DB20[];  // ??_7Rva0049188D@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4DB20=??_7Rva0049188D@@6BRva0024A797@@@")

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

class AttachUpdate : public UpdateModule
{
public:
	AttachUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	int m_24;
};

// ??0AttachUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00491A0F
AttachUpdate::AttachUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData),
	m_20(0),
	m_24(-1)
{
	m_vtable = (const void *)((unsigned int)vtbl_00C4DB20);
	m_secondary0C = (const void *)((unsigned int)vtbl_00BEFF90);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C4DB14);
	setWakeFrame(m_object, (UpdateSleepTime)UPDATE_SLEEP_NONE);
}
