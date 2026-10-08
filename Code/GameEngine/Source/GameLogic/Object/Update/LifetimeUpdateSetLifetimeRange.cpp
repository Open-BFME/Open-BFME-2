// cl: /MD
//
// ?setLifetimeRange@LifetimeUpdate@@QAEXII@Z, retail 0x003A4AB3 (31 bytes).
// LifetimeUpdate::setLifetimeRange (DeletionUpdate precedent at 0x00488450
// which is also 31B): delay = calcSleepDelay(min max) then
// setWakeFrame(getObject delay). Callees are the rowed LifetimeUpdate calc
// at 0x003A49F0 and the rowed UpdateModule::setWakeFrame at 0x0044DF71.
// Layout follows the rowed xfer ?xfer@Rva003A49D1@@MAEXPAVXfer@@@Z at
// 0x003A4AFA: UpdateModule base 0x20 with Object at +0x08 so getObject
// inlines to [esi+0x08]. Vtable immediates need no patching here.
// ?rva003A4AD2@LifetimeUpdate@@QAEXXZ, retail 0x003A4AD2 (15 bytes):
// honest-address wrapper reapplying moduleData min/max through the rowed
// setLifetimeRange above; moduleData at +0x04 with min at +0x08 max at +0x0C.
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual void disabledTypesSlot();
	// BFME 2's wake slot (rowed UpdateModule default 0x0044DF8D).
	virtual void rva0044DF8D(UpdateSleepTime wakeDelay);
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class LifetimeUpdateModuleData
{
private:
	unsigned char m_pad00[8];

public:
	UnsignedInt m_minFrames; // +0x08
	UnsignedInt m_maxFrames; // +0x0C
	unsigned char m_pad10[0x11 - 0x10];
	bool m_creditKiller; // +0x11, credit the killer with the death
	unsigned char m_pad12[0x14 - 0x12];
	int m_deathType; // +0x14
};

class LifetimeUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames);
	void rva003A4AD2();
	void rva0044DF8D(UpdateSleepTime wakeDelay);

private:
	UnsignedInt calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames);

	unsigned char m_pad14[0x14];
	bool m_28; // +0x28
};

void LifetimeUpdate::setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = calcSleepDelay(minFrames, maxFrames);
	setWakeFrame(getObject(), (UpdateSleepTime)delay);
}

void LifetimeUpdate::rva003A4AD2()
{
	const LifetimeUpdateModuleData *data = (const LifetimeUpdateModuleData *)getModuleData();
	setLifetimeRange(data->m_minFrames, data->m_maxFrames);
}

// ?rva0044DF8D@LifetimeUpdate@@UAEXW4UpdateSleepTime@@@Z, retail 0x003A4AE1
// (25 bytes): LifetimeUpdate's override of the UpdateModuleInterface wake
// slot (slot 2 of its {for UpdateModuleInterface} table, after the rowed
// 0x00253376): unless told to sleep forever, clear +0x28 and reapply the
// module data's lifetime range through rva003A4AD2 above.
void LifetimeUpdate::rva0044DF8D(UpdateSleepTime wakeDelay)
{
	if (wakeDelay != UPDATE_SLEEP_FOREVER)
	{
		m_28 = false;
		rva003A4AD2();
	}
}

// ?update@LifetimeUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x003A4BFD..
// 0x003A4CAE (177 bytes): LifetimeUpdate's update in its BFME 2 form (slot 0
// of the UpdateModuleInterface table, so it runs on that subobject). An
// object of kind 0x9A keeps ticking. Otherwise the death is credited -- to the
// object found through the +0x254 module's slot-15 entry ID (rowed
// GameLogic::findObjectByID, then its pinned 0x00294D61 report), or, without
// the module data's +0x11 flag, to the controlling player's +0x3BC record,
// whose +0x110 flag is cleared around its 0x0039CBCE tally (not yet rowed;
// pinned) -- and the object
// is killed (rowed Object::kill) with damage type 8 and the module data's
// death type. It then sleeps forever.
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum KindOfType
{
	KINDOF_9A = 0x9A
};

enum DamageType
{
	DAMAGE_8 = 8
};

enum DeathType
{
	DEATH_NONE_TYPE = 0
};

class Rva003A4BFDEntry
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_id08;
};

class Rva003A4BFDModule
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual Rva003A4BFDEntry *getEntry();	// slot 15
};

// The flag setter is the rowed W3DBridge::setEnabled fold, which stores
// its argument at +0x110.
class W3DBridge
{
public:
	void setEnabled(bool enabled);
	unsigned char m_pad000[0x110];
	bool m_enabled110;
};

class Rva0039CBCE
{
public:
	void rva0039CBCE(Object *obj, int amount);
};

class Player
{
public:
	unsigned char m_pad000[0x3BC];
	W3DBridge m_record3BC;
};

class Rva00294D61
{
public:
	void report(Object *victim, int amount);
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
	Player *getControllingPlayer() const;
	void kill(DamageType damageType, DeathType deathType);
	unsigned char m_pad000[0x254];
	Rva003A4BFDModule *m_module254;
};

UpdateSleepTime LifetimeUpdate::update()
{
	const LifetimeUpdateModuleData *data = (const LifetimeUpdateModuleData *)getModuleData();
	Object *me = getObject();
	if (me->isKindOf(KINDOF_9A))
		return UPDATE_SLEEP_NONE;
	if (data->m_creditKiller)
	{
		Object *killer = TheGameLogic->findObjectByID(me->m_module254->getEntry() ? me->m_module254->getEntry()->m_id08 : INVALID_OBJECT_ID);
		if (killer)
			reinterpret_cast<Rva00294D61 *>(killer)->report(me, 1);
	}
	else
	{
		W3DBridge *record = &me->getControllingPlayer()->m_record3BC;
		bool saved = record->m_enabled110;
		record->setEnabled(false);
		reinterpret_cast<Rva0039CBCE *>(record)->rva0039CBCE(me, -1);
		record->setEnabled(saved);
	}
	me->kill(DAMAGE_8, (DeathType)data->m_deathType);
	return UPDATE_SLEEP_FOREVER;
}
