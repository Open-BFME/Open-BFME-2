// cl: /O1 /DNDEBUG /MD /GX
//
// ??0AimWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045B226,
// 85 bytes. Behavior-side ctor completing the AimWeaponBehavior file-unit
// (poolkey rowed at 0x45B198, proc rowed at 0x45B215, ModuleData factory
// rowed at 0x24B0F7, ModuleData ctor rowed at 0x45B1DD, behavior factory
// rowed at 0x24B0BF news 0x24 with this pinned 2-arg ctor).
//
// StealthDetector-mirror recipe (StealthDetectorUpdateCtor.cpp): UpdateModule
// is 0x20 (BehaviorModule pair plus UpdateModuleInterface plus three ints,
// per UpdateModuleCtor.cpp); the derived re-installs its three vtables at
// +0/+0xC/+0x10, clears its flag byte at +0x20, then wakes next frame with
// setWakeFrame(getObject(), 1) via the rowed UpdateModule base and the
// pinned 0x44DF71. Zero new pins (all callees rowed/pinned).

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

class AimWeaponBehavior : public UpdateModule
{
public:
	AimWeaponBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~AimWeaponBehavior();
private:
	const Object *getObject() const { return m_object; }
	bool m_bfme20;
};

// ??0AimWeaponBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x0045B226
AimWeaponBehavior::AimWeaponBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_bfme20 = false;
	setWakeFrame(const_cast<Object*>(getObject()), 1);
}
