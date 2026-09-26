// cl: /O1 /DNDEBUG /MD
//
// ?Rva004A390B@InvisibilityUpdate@@MAEXXZ, retail 0x004A390B, 49 bytes.
// InvisibilityUpdate vslot 5 (offset 0x14) of vtable 0x00852534: stealth-gated
// wake-frame refresh over the rowed UpdateModule base (0x253390). When
// +0x24 is nonzero, fetch a delay through the +0x10 base slot 0 and forward
// it with +0x08 to rowed setWakeFrame 0x44DF71; otherwise forward
// UPDATE_SLEEP_FOREVER (0x3FFFFFFF). Identity is class plus slot; the method
// name is an honest address name and the +0x10 slot-0 name is TU-local
// descriptive (indirect call, no row). Evidence: vtable 0x852534 from ctor
// 0x4A382D and dtor 0x4A389F; sibling dtor TU shares layout.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
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
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class Iface10
{
public:
	virtual int fetchDelay();
};

class UpdateModule : public BehaviorModule, public Iface10
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime delay);
private:
	unsigned char m_pad14[0x20 - 0x14];
};

class TrailingModuleInterface
{
public:
	virtual void trailingAnchor();
};

class InvisibilityUpdate : public UpdateModule, public TrailingModuleInterface
{
protected:
	virtual void Rva004A390B();
private:
	unsigned char m_stealth24;
};

void InvisibilityUpdate::Rva004A390B()
{
	if (m_stealth24 != 0) {
		Object *obj = m_object;
		int delay = ((Iface10 *)((char *)this + 0x10))->fetchDelay();
		setWakeFrame(obj, (UpdateSleepTime)delay);
	} else {
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
	}
}
