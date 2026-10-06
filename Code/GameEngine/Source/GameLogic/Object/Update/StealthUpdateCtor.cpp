// cl: /DNDEBUG /MD /GX
//
// ??0StealthUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00374B02,
// 198 bytes. Zero Hour's StealthUpdate::StealthUpdate (GeneralsMD
// GameLogic/Object/Update/StealthUpdate.cpp), reshaped by BFME 2.
// Target evidence: the body runs the rowed UpdateModule ctor 0x00253390,
// then stores vtable 0x00817F20 (slot 1 the rowed StealthUpdate
// loadPostProcess 0x00374AE8, slot 3 the rowed StealthUpdate::xfer
// 0x00374942) and the two interface vtables at +0x0C and +0x10; the
// member offsets are the ones StealthUpdateXfer.cpp and
// StealthUpdateUpgradeMasks.cpp established (frames at +0x20/+0x24/+0x28,
// enabled at +0x30, disguise player -1 at +0x38, template at +0x3C, the
// two 0x80-byte upgrade masks at +0x48/+0xC8 built by the rowed clear
// helper 0x001EAE6F, the version-4 flag at +0x148). As in ZH the
// enabled flag is !teamDisguised (module data +0x30), innate stealth
// (module data +0x54) sets status 0x12 through the rowed status helper
// 0x003743CF (every caller of which lies in this class's code), and the
// module wakes with UPDATE_SLEEP_NONE. BFME 2 drops ZH's stealth-delay
// frame, pulse phase and granted-by-special-power sleep; the bytes at
// +0x2C, +0x31..+0x34 and +0x44..+0x47 are BFME 2 additions without ZH
// names.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

class Thing;
class ModuleData;
class Object;
class ThingTemplate;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_CAN_STEALTH = 0x12
};

// The shared 0x80-byte clear at 0x001EAE6F, rowed under an address name.
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
};

// BFME 2's 0x80-byte upgrade mask; its constructor is that clear.
struct UpgradeMaskType
{
	UpgradeMaskType() { ((Rva001EAE6FHelper *)this)->clear80(); }
	unsigned long m_words[32];
};

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

class StealthUpdateModuleData
{
public:
	unsigned char m_pad00[0x30];
	Bool m_teamDisguised; // +0x30
	unsigned char m_pad31[0x54 - 0x31];
	Bool m_innateStealth; // +0x54
};

// The status helper at 0x003743CF, rowed under an address name.
class Rva003743CF
{
public:
	void rva003743CF(void *status, Bool set);
};

class StealthUpdate : public UpdateModule
{
public:
	StealthUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~StealthUpdate();
private:
	const StealthUpdateModuleData *getStealthUpdateModuleData() const { return (const StealthUpdateModuleData *)m_moduleData; }

	UnsignedInt m_stealthAllowedFrame; // +0x20
	UnsignedInt m_detectionExpiresFrame; // +0x24
	UnsignedInt m_framesGranted; // +0x28
	Int m_2c; // +0x2C
	Bool m_enabled; // +0x30
	Bool m_31;
	Bool m_32;
	Bool m_33;
	Bool m_34;
	Int m_disguiseAsPlayerIndex; // +0x38
	const ThingTemplate *m_disguiseAsTemplate; // +0x3C
	UnsignedInt m_disguiseTransitionFrames; // +0x40
	Bool m_disguiseHalfpointReached; // +0x44
	Bool m_transitioningToDisguise; // +0x45
	Bool m_disguised; // +0x46
	Bool m_47;
	UpgradeMaskType m_mask48;
	UpgradeMaskType m_maskC8;
	Bool m_148;
};

StealthUpdate::StealthUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_stealthAllowedFrame(0)
	, m_detectionExpiresFrame(0)
	, m_framesGranted(0)
	, m_2c(-1)
	, m_enabled(true)
	, m_31(false)
	, m_32(false)
	, m_33(false)
	, m_34(true)
	, m_disguiseAsPlayerIndex(-1)
	, m_disguiseAsTemplate(NULL)
	, m_disguiseTransitionFrames(0)
	, m_disguiseHalfpointReached(false)
	, m_transitioningToDisguise(false)
	, m_disguised(false)
	, m_47(false)
	, m_148(false)
{
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();

	//Must be enabled manually if using disguise system (bomb truck uses)
	m_enabled = !data->m_teamDisguised;

	if (data->m_innateStealth)
	{
		//Giving innate stealth units this status bit allows other code to easily check the status bit.
		ObjectStatusTypes status = OBJECT_STATUS_CAN_STEALTH;
		((Rva003743CF *)this)->rva003743CF(&status, true);
	}

	// start active, since some stealths start enabled from the get-go
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
