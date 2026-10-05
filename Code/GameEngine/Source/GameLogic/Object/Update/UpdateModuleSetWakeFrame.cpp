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
	const ModuleData *m_moduleData;
	Object *m_object; // +0x08

public:
	Object *getObject() const { return m_object; }
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

// BitFlags<11> is DisabledMaskType (BitFlags11DisabilityCtors.cpp); its
// copy is a 4-byte memcpy call in retail, as its constructors memset.
#pragma function(memcpy)
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

template <int NUM_BITS>
class BitFlags
{
public:
	__forceinline BitFlags(const BitFlags &src) { memcpy(m_bits, src.m_bits, sizeof(m_bits)); }

private:
	UnsignedInt m_bits[(NUM_BITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;

// VA 0x00E030CC: the dynamic initializer at 0x007B00F1 memsets it clear.
extern DisabledMaskType DISABLEDMASK_NONE;
// VA 0x00E030D0: memset clear at 0x007B0103, then all bits set through the
// rowed 0x00419CC8.
extern DisabledMaskType DISABLEDMASK_ALL;

// Slot order: update, getDisabledTypesToProcess (ZH), then a BFME 2 slot
// that wakes the module (0x0044DF8D; no donor name).
class UpdateModuleInterface
{
public:
	virtual void update() = 0;
	virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
	virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	UnsignedInt m_nextCallFrameAndPhase; // +0x14 (ctor TU precedent)

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	UpdateSleepTime getWakeFrame() const;

public:
	DisabledMaskType getDisabledTypesToProcess() const;
	void rva0044DF8D(UpdateSleepTime wakeDelay);
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

// ?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ @0x00253376
// ZH UpdateModule default; the {for UpdateModuleInterface} slot after update
// in some 60 module vtables.
DisabledMaskType UpdateModule::getDisabledTypesToProcess() const
{
	return DISABLEDMASK_NONE;
}

// ?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z @0x0044DF8D
// The interface slot after getDisabledTypesToProcess: this adjusts from the
// interface at +0x10 and sets the wake frame of the owning object.
void UpdateModule::rva0044DF8D(UpdateSleepTime wakeDelay)
{
	setWakeFrame(getObject(), wakeDelay);
}

// ?getDisabledTypesToProcess@Rva004DF396@@UBE?AV?$BitFlags@$0L@@@XZ @0x004DF396
// The DISABLEDMASK_ALL override many ZH modules declare inline; identical
// copies fold, so the {for UpdateModuleInterface} slot of several vtables
// lands here and the owning class is not recovered.
class Rva004DF396 : public UpdateModule
{
public:
	DisabledMaskType getDisabledTypesToProcess() const;
};

DisabledMaskType Rva004DF396::getDisabledTypesToProcess() const
{
	return DISABLEDMASK_ALL;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?setWakeFrame@UpdateModule@@QAEXPAVObject@@I@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
#pragma comment(linker, "/alternatename:?setWakeFrame@WeaponModeSpecialPowerUpdateBase@@IAEXPAVObject@@W4UpdateSleepTime@@@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
#pragma comment(linker, "/alternatename:?setWakeFrame@Rva0026E9BDBase@@IAEXPAVObject@@I@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
#pragma comment(linker, "/alternatename:?setWakeFrame@ALU_UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
#pragma comment(linker, "/alternatename:?setWakeFrame@FireWeaponUpdate@@IAEXPAVObject@@I@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
#pragma comment(linker, "/alternatename:?setWakeFrame@UpdateModule@@IAEXPAVObject@@I@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?bfmeSetWakeBJ@BfmeWakeBJ@@QAEXPAXH@Z=?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")
