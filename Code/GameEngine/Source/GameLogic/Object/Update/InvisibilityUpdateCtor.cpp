// cl: /DNDEBUG /MD
//
// ??0InvisibilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A382D,
// 67 bytes. InvisibilityUpdate behavior ctor over the rowed UpdateModule
// base (0x253390, thing plus data): the trailing Rva004A3A09Iface base
// stores its own vtable at +0x20, the complete object then stores its
// vtables at +0x00, +0x0C, +0x10 and +0x20, and the body copies the module
// data's +0x1D0 flag into +0x24. Plain virtual classes give that order;
// the layout is InvisibilityUpdate.cpp's (pool key at 0x004A393C plus
// ModuleData proc 0x004A381C).

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct InvisibilityUpdateModuleData
{
	unsigned char m_pad000[0x1D0];
	bool m_startsActive; // +0x1D0
};

class InvisibilityUpdatePrimary
{
public:
	virtual void primaryAnchor();
protected:
	const InvisibilityUpdateModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class Rva004A3A20Interface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public InvisibilityUpdatePrimary, public BehaviorModuleOther, public Rva004A3A20Interface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	unsigned char m_pad14[12];
};

class Rva004A3A09Iface
{
public:
	virtual bool rva004A3A09() = 0;
};

class InvisibilityUpdate : public UpdateModule, public Rva004A3A09Iface
{
public:
	InvisibilityUpdate(Thing *thing, const ModuleData *moduleData);
	virtual bool rva004A3A09();
	virtual UpdateSleepTime update();
private:
	bool m_24; // +0x24
};

// ??0InvisibilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
InvisibilityUpdate::InvisibilityUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_24 = m_moduleData->m_startsActive;
}
