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
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

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

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

// ?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z @0x0044DF71
void UpdateModule::setWakeFrame(Object *obj, UpdateSleepTime wakeDelay)
{
	UnsignedInt now = TheGameLogic->getFrame();
	TheGameLogic->friend_awakenUpdateModule(obj, this, now + (UnsignedInt)wakeDelay);
}
