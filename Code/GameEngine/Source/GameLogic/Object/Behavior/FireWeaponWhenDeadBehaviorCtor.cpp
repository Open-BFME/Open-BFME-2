// cl: /DNDEBUG /MD /GX
//
// ??0FireWeaponWhenDeadBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00482D80, 203 bytes. Zero Hour's
// FireWeaponWhenDeadBehavior::FireWeaponWhenDeadBehavior (GeneralsMD
// GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp), rebased by
// BFME 2 onto UpdateModule. Target evidence: the body runs the rowed
// UpdateModule ctor 0x00253390, the rowed UpgradeMux ctor 0x004CE2A3 on
// +0x20 and the implicit ctor of the one-slot die interface at +0x28
// (vtable 0x0081C780, slot 0 _purecall), then stores the five vtables the
// rowed dtor 0x00482E96 restores (0x008497B4 primary, slot 3 the rowed xfer
// 0x00482BDB and slot 4 the rowed FireWeaponWhenDeadBehavior pool key
// 0x00482E51; 0x00849698 for the die interface, slot 0 the onDie body at
// 0x00482C4A). It builds the +0x2C damage record through the rowed ctor
// 0x00263895 and, as in ZH, gives itself the upgrade when the module data's
// initially-active flag (+0x118) is set. BFME 2 adds the +0xA8 count: the
// module data's +0x11C count clamped to at least 1 when it is positive.
// The module sleeps forever.
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;
class DamageInfo;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

template <class T>
inline const T &maxOf(const T &a, const T &b)
{
	return a < b ? b : a;
}

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
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
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual Bool attemptUpgrade();
	void giveSelfUpgrade();
protected:
	Bool m_upgradeExecuted; // +0x04
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

// The +0x2C damage record; its ctor is rowed at 0x00263895.
class Rva00263895Member
{
public:
	Rva00263895Member();
private:
	unsigned char m_data[0x7C];
};

class FireWeaponWhenDeadBehaviorModuleData
{
public:
	unsigned char m_pad00[0x118];
	Bool m_initiallyActive; // +0x118
	UnsignedInt m_count; // +0x11C
};

class FireWeaponWhenDeadBehavior : public UpdateModule, public UpgradeMux, public DieModuleInterface
{
public:
	FireWeaponWhenDeadBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponWhenDeadBehavior();
	virtual void onDie(const DamageInfo *damageInfo);
private:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const { return (const FireWeaponWhenDeadBehaviorModuleData *)m_moduleData; }

	Rva00263895Member m_damageInfo; // +0x2C
	UnsignedInt m_count; // +0xA8
};

FireWeaponWhenDeadBehavior::FireWeaponWhenDeadBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_count = 0;
	if (getFireWeaponWhenDeadBehaviorModuleData()->m_initiallyActive)
	{
		giveSelfUpgrade();
	}
	const FireWeaponWhenDeadBehaviorModuleData *data = getFireWeaponWhenDeadBehaviorModuleData();
	if (data->m_count > 0.0f)
		m_count = maxOf(data->m_count, (UnsignedInt)1);
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
