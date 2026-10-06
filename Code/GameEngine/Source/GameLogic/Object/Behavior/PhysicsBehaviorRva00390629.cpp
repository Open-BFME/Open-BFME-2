// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// PhysicsBehavior::rva00390629(bool), retail 0x00390629 (150 bytes), and
// PhysicsBehavior::rva003906BF(), retail 0x003906BF (106 bytes): the two methods
// between the matched PhysicsBehavior::rva00390601 and the PhysicsBehavior ctor
// 0x003907A6. Callers pass the Object +0x25C physics pointer (0x00495058 loads
// it and tail-jumps to 0x003906BF; the 0x00291B1D and 0x0036B047 callers follow
// the PhysicsBehavior call 0x003909FA on the same this).
// Both refuse when the Object's template float +0x610 or that of the Object it
// is contained by (+0x274) is at least 100.0 (the 0x00BC292C literal).
// 0x00390629 stores the (possibly refused) flag at +0x5C and, when it ends up
// clear, clears model conditions 5*32+3, 3*32+31 and 4*32+0 and zeroes +0x58.
// 0x003906BF sets model condition 4*32+0, sets +0x5C, copies module data +0x20
// into +0x58 and wakes the module (setWakeFrame UPDATE_SLEEP_NONE).
// Condition bits: Object word array at +0x10C, notifier 0x0028AE6D on change.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class ThingTemplate
{
public:
	unsigned char m_pad[0x610];
	float m_610; // +0x610
};
class Object
{
public:
	virtual ~Object();
	void rva0028AE6D();
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getContainedBy() const { return m_containedBy; }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 0x08];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x274 - 0x158];
	Object *m_containedBy; // +0x274
};
class PhysicsBehaviorModuleData
{
public:
	unsigned char m_pad[0x20];
	unsigned int m_20; // +0x20
};
class Thing;
class ModuleData;
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
};
class UpdateModuleInterface
{
public:
	virtual void update();
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};
class PhysicsBehavior : public UpdateModule
{
public:
	void rva00390629(bool enable);
	void rva003906BF();
private:
	unsigned char m_pad20[0x58 - 0x20];
	unsigned int m_58; // +0x58
	bool m_5C; // +0x5C
};
void PhysicsBehavior::rva00390629(bool enable)
{
	Object *obj = m_object;
	const ThingTemplate *tmpl = obj->getTemplate();
	const Object *container = obj->getContainedBy();
	if (tmpl->m_610 >= 100.0f || (container && container->getTemplate()->m_610 >= 100.0f))
		enable = false;
	m_5C = enable;
	if (enable)
		return;
	obj->clearModelConditionState(5 * 32 + 3);
	obj->clearModelConditionState(3 * 32 + 31);
	obj->clearModelConditionState(4 * 32 + 0);
	m_58 = 0;
}
void PhysicsBehavior::rva003906BF()
{
	Object *obj = m_object;
	const ThingTemplate *tmpl = obj->getTemplate();
	const Object *container = obj->getContainedBy();
	if (tmpl->m_610 >= 100.0f || (container && container->getTemplate()->m_610 >= 100.0f))
		return;
	obj->setModelConditionState(4 * 32 + 0);
	m_5C = true;
	m_58 = ((const PhysicsBehaviorModuleData *)m_moduleData)->m_20;
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
