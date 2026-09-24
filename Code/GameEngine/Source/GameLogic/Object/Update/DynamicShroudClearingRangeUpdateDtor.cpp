// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ??1DynamicShroudClearingRangeUpdate@@UAE@XZ retail 0x0048B1AF
// 95 bytes. Behavior-side dtor completing the DynamicShroudClearingRangeUpdate
// file-unit (behavior ctor rowed at 0x48B067 over the same model; ModuleData
// proc/ctor/factory, poolkey, instance factory and killGridDecals all rowed).
//
// Transcribed from the Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameLogic/Object/Update/
// DynamicShroudClearingRangeUpdate.cpp): the dtor body is just
// killGridDecals() ("just in case"); the RadiusDecal array teardown and the
// UpdateModule base dtor (pinned at 0x24A797) are implicit.
//
// The three vtable installs (+0/+0xC/+0x10) are the compiler's MI vptr group
// (ObjectModule primary plus UpdateModuleInterface/ModuleInterface
// secondaries, BFME1 donor layout), emitted as a group ahead of the EH
// state-1 store; user-spelled secondary stores always sink below it.
// killGridDecals resolves via its row; the array teardown rides the rowed
// RadiusDecal ctor plus the pinned dtor.

class Thing;
class ModuleData;
class Player;
class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() {}
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() {}
};

class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
};

class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();

private:
	const void *m_template;			// +0x00
	void *m_decal;					// +0x04
	unsigned char m_empty;			// +0x08
	unsigned char m_pad_09[3];
	float m_unknown0C;				// +0x0C
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	virtual ~DynamicShroudClearingRangeUpdate();
	void killGridDecals();

private:
	int m_state;						// +0x20
	int m_stateCountDown;				// +0x24
	int m_totalFrames;					// +0x28
	unsigned int m_growStartDeadline;	// +0x2C
	unsigned int m_sustainDeadline;		// +0x30
	unsigned int m_shrinkStartDeadline;	// +0x34
	unsigned int m_doneForeverFrame;	// +0x38
	unsigned int m_changeIntervalCountdown;	// +0x3C
	unsigned char m_decalsCreated;		// +0x40
	unsigned char m_pad_41[3];
	float m_visionChangePerInterval;	// +0x44
	float m_nativeClearingRange;		// +0x48
	float m_currentClearingRange;		// +0x4C
	RadiusDecal m_gridDecal[30];		// +0x50
};

// ??1DynamicShroudClearingRangeUpdate@@UAE@XZ @0x0048B1AF
DynamicShroudClearingRangeUpdate::~DynamicShroudClearingRangeUpdate()
{
	killGridDecals();// just in case
}
