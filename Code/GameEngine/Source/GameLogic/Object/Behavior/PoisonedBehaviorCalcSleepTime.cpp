// cl: /O1 /DNDEBUG /MD /GX
//
// ?calcSleepTime@PoisonedBehavior@@IAE?AW4UpdateSleepTime@@XZ, retail 0x00482EFF,
// 40 bytes. Poisoned file-unit drain: returns UPDATE_SLEEP_FOREVER when the
// overall stop frame is unset or reached, else UpdateModule::frameToSleepTime
// over (damageFrame, overallStopFrame) with FOREVER defaults.
//
// Donor: BFME1 PoisonedBehavior.cpp calcSleepTime (0x00202930, 45B). BFME2
// repairs: GameLogic frame at +0x40 (retail; reference header says +0x3C),
// members at +0x24/+0x28 per PoisonedBehaviorCtor (DamageModuleInterface base
// at +0x20). frameToSleepTime pinned at 0x44DF71-family 0x44DF28 via the four
// pushes this call site emits.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

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

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40 (retail; reference header says +0x3C)
};

extern GameLogic *TheGameLogic;

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	UpdateSleepTime frameToSleepTime(UnsignedInt frame1, UnsignedInt frame2 = UPDATE_SLEEP_FOREVER, UnsignedInt frame3 = UPDATE_SLEEP_FOREVER, UnsignedInt frame4 = UPDATE_SLEEP_FOREVER);
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
protected:
	UpdateSleepTime calcSleepTime();
private:
	unsigned int m_poisonDamageFrame; // +0x24
	unsigned int m_poisonOverallStopFrame; // +0x28
	float m_poisonDamageAmount; // +0x2C
	int m_deathType; // +0x30
};

// ?calcSleepTime@PoisonedBehavior@@IAE?AW4UpdateSleepTime@@XZ @0x00482EFF
UpdateSleepTime PoisonedBehavior::calcSleepTime()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_poisonOverallStopFrame == 0 || m_poisonOverallStopFrame == now)
		return UPDATE_SLEEP_FOREVER;
	return frameToSleepTime(m_poisonDamageFrame, m_poisonOverallStopFrame);
}
