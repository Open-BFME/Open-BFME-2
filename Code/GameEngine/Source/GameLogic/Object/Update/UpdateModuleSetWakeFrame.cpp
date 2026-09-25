// cl: /O1 /DNDEBUG /MD
//
// ?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z,
// retail 0x0044DF71, 28 bytes. Direct BFME1 donor transfer
// (UpdateModule::setWakeFrame): the current GameLogic frame plus the wake
// delay is forwarded with (obj, this) to friend_awakenUpdateModule.
// getFrame() is inline (member load at +0x40, Poisoned precedent) and
// TheGameLogic is DIR32-masked; the awaken call resolves via its pin.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	// (we use 0x3fffffff so that we can add offsets and not overflow...
	//	and also 'cuz we shift the value up by two bits for the phase.
	// note that at 30fps, this is ~414 days...
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
#define UPDATE_SLEEP(numFrames) ((UpdateSleepTime)(numFrames))

class Object;
class UpdateModule;

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }
	void friend_awakenUpdateModule(Object *obj, UpdateModule *u, UnsignedInt when);

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40 (Poisoned precedent)
};

extern GameLogic *TheGameLogic;

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	UnsignedInt m_nextCallFrameAndPhase; // +0x14 (ctor TU precedent)

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	UpdateSleepTime getWakeFrame() const;
};

// ?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z @0x0044DF71
void UpdateModule::setWakeFrame(Object *obj, UpdateSleepTime wakeDelay)
{
	UnsignedInt now = TheGameLogic->getFrame();
	TheGameLogic->friend_awakenUpdateModule(obj, this, now + (UnsignedInt)wakeDelay);
}

// ?getWakeFrame@UpdateModule@@IBE?AW4UpdateSleepTime@@XZ @0x0044DF5B
// BFME1 donor reads (m_nextCallFrameAndPhase >> 2); retail compares the raw
// +0x14 word, so BFME2 dropped the phase shift here.
UpdateSleepTime UpdateModule::getWakeFrame() const
{
	UnsignedInt now = TheGameLogic->getFrame();
	UnsignedInt nextCallFrame = m_nextCallFrameAndPhase;
	if (nextCallFrame > now)
		return UPDATE_SLEEP(nextCallFrame - now);
	else
		return UPDATE_SLEEP_NONE;
}
