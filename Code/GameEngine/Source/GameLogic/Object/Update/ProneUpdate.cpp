// cl: /DNDEBUG /MD
//
// ProneUpdate methods, retail 0x0049FF50..0x0049FFF6 in source order:
// startProneEffects 0x0049FF50 (40 bytes), stopProneEffects 0x0049FF78 (40),
// update 0x0049FFA0 (25), goProne 0x0049FFB9 (62).
// Donor: Zero Hour ProneUpdate.cpp, transferred as written. Identity: the class
// is proven by the matched ProneUpdate ctor 0x0049FF06, pool key 0x0049FE9A and
// name getter 0x0049FE94; goProne was pinned at 0x0049FFB9 from a placed caller;
// update is slot 0 of the vtable 0x00C51910 at +0x10 (UpdateModuleInterface;
// that vtable's matched dtor 0x0049FE7B keeps the placeholder row name
// Rva0049FE7B) and calls stopProneEffects on the full object; goProne calls
// startProneEffects.
// BFME2 deltas: the model condition lives on the Object (word array at +0x10C,
// MODELCONDITION_PRONE = word 2 bit 7) and is set or cleared through
// masked-word accessors around the pinned notifier 0x0028AE6D; the no-attack
// status goes through the matched Object::setStatus(type, bool) (status 5).

typedef int Int;
typedef float Real;
typedef bool Bool;
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	void setStatus(ObjectStatusTypes status, bool set);
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
// MODELCONDITION_PRONE in BFME2: word 2 bit 7 of the Object condition words.
enum
{
	MODELCONDITION_PRONE = 2 * 32 + 7,
	OBJECT_STATUS_NO_ATTACK = 5
};
class DamageInfo
{
public:
	unsigned char m_pad[0x70];
	Real m_actualDamageDealt; // out.m_actualDamageDealt, +0x70
};
class ProneUpdateModuleData
{
public:
	unsigned char m_pad[8];
	Real m_damageToFramesRatio; // +0x08
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class ProneUpdate : public UpdateModule
{
public:
	void goProne(const DamageInfo *damageInfo);
	virtual UpdateSleepTime update();
protected:
	const ProneUpdateModuleData *getProneUpdateModuleData() const
	{
		return (const ProneUpdateModuleData *)getModuleData();
	}
	void startProneEffects();
	void stopProneEffects();
	Int m_proneFrames; // +0x20
};
void ProneUpdate::startProneEffects()
{
	Object *object = getObject();
	setModelConditionBit(object, MODELCONDITION_PRONE);
	object->setStatus((ObjectStatusTypes)OBJECT_STATUS_NO_ATTACK, true);
}
void ProneUpdate::stopProneEffects()
{
	Object *object = getObject();
	clearModelConditionBit(object, MODELCONDITION_PRONE);
	object->setStatus((ObjectStatusTypes)OBJECT_STATUS_NO_ATTACK, false);
}
UpdateSleepTime ProneUpdate::update()
{
	if (m_proneFrames > 0)
	{
		m_proneFrames--;
		if (m_proneFrames == 0)
			stopProneEffects();
	}
	return UPDATE_SLEEP_NONE;
}
void ProneUpdate::goProne(const DamageInfo *damageInfo)
{
	Bool wasProne = (m_proneFrames > 0);
	Int damageTaken = (Int)damageInfo->m_actualDamageDealt;
	m_proneFrames += damageTaken * getProneUpdateModuleData()->m_damageToFramesRatio;
	if (!wasProne && (m_proneFrames > 0))
		startProneEffects();
}
