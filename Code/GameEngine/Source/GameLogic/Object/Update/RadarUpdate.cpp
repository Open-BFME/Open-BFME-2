// cl: /DNDEBUG /MD
//
// RadarUpdate::extendRadar, retail 0x004A0D0F (80 bytes), and
// RadarUpdate::update, retail 0x004A0D5F (77 bytes), in the RadarUpdate block
// after the matched RadarUpdate ctor 0x004A0C72 and its deleting dtor.
// Donors: BFME1 game/GameEngine/Source/GameLogic/Object/Update/
// RadarUpdate_extendRadar.cpp and RadarUpdate_update.cpp (open-bfme-1 068db38bb4),
// same bodies: extendRadar sets the radar-extending model condition, stamps the
// done frame as the unsigned frame plus the module data Real via __ftol2 and
// sets m_radarActive; update (entered on the +0x10 update interface) finishes
// the extension once the frame passes it and swaps extending for upgraded.
// BFME2 deltas (target evidence): the condition words start at Object+0x10C and
// the bits are 2*32+11 (extending, +0x114 mask 0x800) and 2*32+12 (upgraded,
// mask 0x1000); the notifier is the pinned 0x0028AE6D; TheGameLogic's frame is
// at +0x40; update clears the done frame before setting the complete flag.
// The ZH twin supplies the labels only.
typedef unsigned int UnsignedInt;
typedef bool Bool;

typedef float Real;

enum ModelConditionFlagType
{
	MODELCONDITION_RADAR_EXTENDING = 2 * 32 + 11,
	MODELCONDITION_RADAR_UPGRADED = 2 * 32 + 12
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

class Object
{
public:
	void rva0028AE6D();
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set)
	{
		if (m_modelConditionFlags.test(clr) || !m_modelConditionFlags.test(set))
		{
			m_modelConditionFlags.clear(clr);
			m_modelConditionFlags.set(set);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class ModuleData;
struct RadarUpdateModuleData
{
	unsigned char m_unmodelled_00[8];
	Real m_radarExtendTime; // +0x08
};
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
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

class RadarUpdate : public UpdateModule
{
public:
	void extendRadar();
	virtual UpdateSleepTime update();
private:
	const RadarUpdateModuleData *getRadarUpdateModuleData() const
	{
		return (const RadarUpdateModuleData *)m_moduleData;
	}

	UnsignedInt m_extendDoneFrame; // +0x20
	Bool m_extendComplete; // +0x24
	Bool m_radarActive; // +0x25
};

void RadarUpdate::extendRadar()
{
	Object *obj = getObject();
	const RadarUpdateModuleData *modData = getRadarUpdateModuleData();

	obj->setModelConditionState(MODELCONDITION_RADAR_EXTENDING);

	m_extendDoneFrame = TheGameLogic->getFrame() + modData->m_radarExtendTime;
	m_radarActive = true;
}

UpdateSleepTime RadarUpdate::update()
{
	// if no extend frame nothing to do
	if (m_extendDoneFrame == 0)
		return UPDATE_SLEEP_NONE;
	// check to see if our extension is already done
	if (m_extendComplete == true)
		return UPDATE_SLEEP_NONE;
	// see if it's time to stop the extension
	if (TheGameLogic->getFrame() > m_extendDoneFrame)
	{
		m_extendDoneFrame = 0;
		m_extendComplete = true;
		getObject()->clearAndSetModelConditionState(MODELCONDITION_RADAR_EXTENDING, MODELCONDITION_RADAR_UPGRADED);
	}
	return UPDATE_SLEEP_NONE;
}
