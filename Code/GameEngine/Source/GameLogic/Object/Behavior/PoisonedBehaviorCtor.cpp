// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0PoisonedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00482F7D,
// 120 bytes. Behavior-side ctor completing the PoisonedBehavior file-unit
// (ModuleData proc/factory/ctor rowed at 0x482F6C/0x24C3A6/0x253CDD;
// behavior factory rowed at 0x24C36E news 0x34 with this pinned 2-arg ctor;
// poolkey rowed at 0x482F27).
//
// Donor: BFME1 PoisonedBehavior.cpp ctor (UpdateModule base plus four member
// zeroings plus setWakeFrame(getObject(), 0x3fffffff)). BFME2 repairs:
// UpdateModule is 0x20 (BehaviorModule pair plus UpdateModuleInterface plus
// three ints, per UpdateModuleCtor.cpp); DamageModuleInterface base at +0x20
// (inline empty ctor, virtual onDamage) carries the fourth vtable slot;
// members are m_poisonDamageFrame at +0x24, m_poisonOverallStopFrame at +0x28,
// m_poisonDamageAmount float at +0x2C, m_deathType at +0x30 set to 5.
// Retail stores the base vtable at +0x20 first, then the derived batch, then
// zeros/float/5, then setWakeFrame via rowed UpdateModule base and pinned
// 0x44DF71. Zero new pins (all callees rowed/pinned).

class Thing;
class ModuleData;
class Object;
class DamageInfo;

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

class DamageModuleInterface
{
public:
	DamageModuleInterface() {}
	virtual void onDamage(DamageInfo *damageInfo);
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
public:
	PoisonedBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PoisonedBehavior();
private:
	const Object *getObject() const { return m_object; }
	unsigned int m_poisonDamageFrame;
	unsigned int m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	int m_deathType;
};

// ??0PoisonedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00482F7D
PoisonedBehavior::PoisonedBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_poisonDamageFrame(0),
	m_poisonOverallStopFrame(0),
	m_poisonDamageAmount(0.0f),
	m_deathType(5)
{
	setWakeFrame(const_cast<Object*>(getObject()), 0x3fffffff);
}
