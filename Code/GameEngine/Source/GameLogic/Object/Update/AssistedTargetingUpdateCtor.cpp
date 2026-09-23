// cl: /O1 /DNDEBUG /MD /GX
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

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AssistedTargetingUpdate : public UpdateModule
{
public:
	AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AssistedTargetingUpdate();
private:
	const Object *getObject() const { return m_object; }
};

// ??0AssistedTargetingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00486E8D
AssistedTargetingUpdate::AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	setWakeFrame(const_cast<Object*>(getObject()), 0x3fffffff);
}
