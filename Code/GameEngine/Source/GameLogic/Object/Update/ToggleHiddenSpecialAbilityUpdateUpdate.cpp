// cl: /O1 /DNDEBUG /MD
//
// ToggleHiddenSpecialAbilityUpdate::update, retail 0x004AE286 (74 bytes):
// slot 0 of the class's +0x10 update-module interface table 0x00C552C8, so
// `this` is that subobject (module data at -0x0C, Object at -0x08). Runs the
// SpecialAbilityUpdate update 0x00451FA2 (the slot-0 entry of the
// special-ability +0x10 tables, pinned by address) and keeps its sleep;
// with a module data delay at +0x7C and the Object in status 0x10, once that
// many frames have passed since the frame at +0x88 the primary slot 23 runs,
// else the module sleeps for the delay.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_10 = 0x10
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
};
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;		// +0x40
};
extern GameLogic *TheGameLogic;
struct ToggleHiddenSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0x7C];
	unsigned int m_delay;		// +0x7C
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
	virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04();
	virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08();
	virtual void p09(); virtual void p10(); virtual void p11(); virtual void p12();
	virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16();
	virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20();
	virtual void p21(); virtual void p22();
	virtual void rvaSlot23();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class SpecialAbilityUpdate : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
protected:
	unsigned char m_pad14[0x88 - 0x14];
	unsigned int m_88;		// +0x88
};
class ToggleHiddenSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update();
};
UpdateSleepTime ToggleHiddenSpecialAbilityUpdate::update()
{
	UpdateSleepTime sleep = SpecialAbilityUpdate::update();
	const ToggleHiddenSpecialAbilityUpdateModuleData *data =
		(const ToggleHiddenSpecialAbilityUpdateModuleData *)m_moduleData;
	if (data)
	{
		unsigned int delay = data->m_delay;
		if (delay && m_object->testStatus(OBJECT_STATUS_10))
		{
			if (TheGameLogic->getFrame() >= m_88 + delay)
				rvaSlot23();
			else
				sleep = (UpdateSleepTime)delay;
		}
	}
	return sleep;
}
