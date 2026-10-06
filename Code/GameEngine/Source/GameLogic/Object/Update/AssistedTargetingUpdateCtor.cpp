// cl: /DNDEBUG /MD /GX
//
// ??0AssistedTargetingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00486E8D,
// 84 bytes. Behavior-side ctor completing the AssistedTargetingUpdate
// file-unit (poolkey rowed at 0x486E31, proc rowed at 0x486E7C, ModuleData
// factory rowed at 0x253C23, ModuleData ctor rowed at 0x253C08, behavior
// factory rowed at 0x24CC11 news 0x20 with this pinned 2-arg ctor).
//
// StealthDetector-mirror recipe (StealthDetectorUpdateCtor.cpp): UpdateModule
// is 0x20 (BehaviorModule pair plus UpdateModuleInterface plus three ints,
// per UpdateModuleCtor.cpp); the derived re-installs its three vtables at
// +0/+0xC/+0x10, then parks itself awake with setWakeFrame(getObject(),
// FOREVER) via the rowed UpdateModule base and the pinned 0x44DF71. Zero new
// pins (all callees rowed/pinned).
//
// LINK-COMDAT fix: no virtuals, so no vtable COMDATs are emitted (FlammableUpdateCtor
// precedent). The three vptr slots are explicit data members re-stored to
// TU-local dummies (DIR32-masked); the rowed base ctor plus setWakeFrame keep
// the 84B body. This removes the differing ??_7AssistedTargetingUpdate@@6B@
// copy that clashed with AssistedTargetingUpdate.cpp's full-class vtables.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

static int s_dummy00;
static int s_dummy0C;
static int s_dummy10;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AssistedTargetingUpdate : public UpdateModule
{
public:
	AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0AssistedTargetingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00486E8D
AssistedTargetingUpdate::AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_vtable = &s_dummy00;
	m_secondary0C = &s_dummy0C;
	m_secondary10 = &s_dummy10;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
