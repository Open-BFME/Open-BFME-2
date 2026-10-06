// cl: /O1 /MD /EHsc
//
// ??0LifetimeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x003A4B58 (165B).
// LifetimeUpdate ctor: UpdateModule base then m_dieFrame/m_birthFrame zeroed
// plus bool +0x28 copied from moduleData m_startDisabled; vptrs at +0x00
// +0x0C +0x10 (UpdateModule MI layout per rowed xfer 0x003A4AFA which xfers
// +0x20/+0x24 then bool +0x28); if startDisabled setWakeFrame FOREVER else
// HULK override (template byte +0x112 mask 4 plus GameLogic +0xA0 override
// not -1) selects calc(override override) else calc(min max) then setWakeFrame.
// Callees rowed: UpdateModule ctor 0x00253390 and calc 0x003A49F0 and
// setWakeFrame 0x0044DF71. EH prolog via /EHsc.
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Int getHulkMaxLifetimeOverride() const { return m_hulkMaxLifetimeOverride; }

private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
	unsigned char m_pad44[0x5C]; // 0x44..0xA0
	Int m_hulkMaxLifetimeOverride; // +0xA0
};

extern GameLogic *TheGameLogic;

class ThingTemplate
{
public:
	unsigned char m_pad00[0x112];
	unsigned char m_hulkKind; // +0x112 bit 2 (mask 4) is HULK
};

class Thing
{
public:
	virtual ~Thing();

	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isHulkKind() const { return (getTemplate()->m_hulkKind & 4) != 0; }

private:
	const ThingTemplate *m_template; // +0x04
};

class Object : public Thing
{
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
	virtual void updateSlot();
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	// Declared only: retail's ~UpdateModule (0x0024A797, pin) restores the three vtables and
	// tail-jumps on; the implicit one here compiled to a 5-byte jmp the link could keep.
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class LifetimeUpdateModuleData
{
private:
	unsigned char m_pad00[8];

public:
	UnsignedInt m_minFrames; // +0x08
	UnsignedInt m_maxFrames; // +0x0C
	Bool m_startDisabled; // +0x10
};

class LifetimeUpdate : public UpdateModule
{
public:
	LifetimeUpdate(Thing *thing, const ModuleData *moduleData);

private:
	UnsignedInt calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames);

	UnsignedInt m_dieFrame; // +0x20
	UnsignedInt m_birthFrame; // +0x24
	Bool m_disabled; // +0x28
};

LifetimeUpdate::LifetimeUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), m_dieFrame(0), m_birthFrame(0), m_disabled(false)
{
	const LifetimeUpdateModuleData *data = (const LifetimeUpdateModuleData *)getModuleData();
	Bool startDisabled = data->m_startDisabled;
	m_disabled = startDisabled;
	if (startDisabled == true)
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	}
	else
	{
		UnsignedInt delay;
		if (getObject()->isHulkKind() && TheGameLogic->getHulkMaxLifetimeOverride() != -1)
			delay = calcSleepDelay(TheGameLogic->getHulkMaxLifetimeOverride(), TheGameLogic->getHulkMaxLifetimeOverride());
		else
			delay = calcSleepDelay(data->m_minFrames, data->m_maxFrames);
		setWakeFrame(getObject(), (UpdateSleepTime)delay);
	}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorSlot@BehaviorModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
