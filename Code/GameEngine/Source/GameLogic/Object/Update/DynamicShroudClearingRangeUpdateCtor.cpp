// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// stlport
//
// ??0DynamicShroudClearingRangeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x0048B067
// 253 bytes. Behavior-side ctor completing the DynamicShroudClearingRangeUpdate
// file-unit (ModuleData proc/ctor/factory, poolkey, instance factory and
// killGridDecals are all rowed; this ctor is the pinned remainder).
//
// Transcribed from the BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/
// DynamicShroudClearingRangeUpdateCtorThunk.cpp), which names both calls in
// the tail: Object::getControllingPlayer (rowed at 0x28AFA9) and
// Object::getShroudClearingRange (pinned at 0x28DE87). Retail keeps the
// donor order exactly: change-interval/vision zeros, shrink+grow count,
// max(1) total, shrink/grow/sustain deadlines, done-forever frame off
// TheGameLogic, decals flag, 200.0f native range, 0.0f current range, state
// zero, then the object-gated range load and the 30-wide RadiusDecal clear
// loop over this+0x50 (killGridDecals proves the array base and stride).
// The RadiusDecal element ctor/dtor ride the rowed/pinned 0x330DA4/0x330DD6
// pair through the ehvec helper; clear resolves via its row.

class Thing;
class ModuleData;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	float getShroudClearingRange() const;
};

class GameLogic
{
public:
	unsigned char m_unreconstructed_00[0x40];
	unsigned int m_frame;
	unsigned int getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();
};

class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();

private:
	const void *m_template;			// +0x00, rowed ctor zeroes
	void *m_decal;					// +0x04, rowed ctor zeroes
	unsigned char m_empty;			// +0x08, rowed ctor sets 1
	unsigned char m_pad_09[3];
	float m_unknown0C;				// +0x0C, rowed ctor zeroes (SSE)
};

class DynamicShroudClearingRangeUpdateModuleData
{
public:
	unsigned char m_unreconstructed_00[0x08];
	unsigned int m_shrinkDelay;			// +0x08
	unsigned int m_shrinkTime;			// +0x0C
	unsigned int m_growDelay;			// +0x10
	unsigned int m_growTime;			// +0x14
};

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	DynamicShroudClearingRangeUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_vtable;				// +0x00
	const ModuleData *m_moduleData;		// +0x04
	Object *m_object;					// +0x08
	const void *m_secondary0C;			// +0x0C
	const void *m_secondary10;			// +0x10
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
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

template <class T>
static const T &bfmeMax(const T &left, const T &right)
{
	return right < left ? left : right;
}

// ??0DynamicShroudClearingRangeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048B067
DynamicShroudClearingRangeUpdate::DynamicShroudClearingRangeUpdate(
	Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_vtable(reinterpret_cast<const void *>(0x00C4BEBC))
	, m_secondary0C(reinterpret_cast<const void *>(0x00BEFF90))
	, m_secondary10(reinterpret_cast<const void *>(0x00C4BEB0))
{
	const DynamicShroudClearingRangeUpdateModuleData *md =
		(const DynamicShroudClearingRangeUpdateModuleData *)moduleData;
	m_changeIntervalCountdown = 0;
	m_visionChangePerInterval = 0.0f;
	m_stateCountDown = md->m_shrinkDelay + md->m_shrinkTime;
	m_totalFrames = bfmeMax(1, m_stateCountDown);
	m_shrinkStartDeadline = m_stateCountDown - md->m_shrinkDelay;
	m_growStartDeadline = m_stateCountDown - md->m_growDelay;
	m_sustainDeadline = m_growStartDeadline - md->m_growTime;
	m_doneForeverFrame = TheGameLogic->getFrame() + m_stateCountDown;
	m_decalsCreated = 0;
	m_nativeClearingRange = 200.0f;
	m_currentClearingRange = 0.0f;
	m_state = 0;

	Object *object = m_object;
	if (!object)
		return;
	Player *controller = object->getControllingPlayer();
	if (!controller)
		return;
	m_nativeClearingRange = object->getShroudClearingRange();

	RadiusDecal *decal = m_gridDecal;
	int decalsLeft = 30;
	do {
		decal->clear();
		++decal;
	} while (--decalsLeft != 0);
}
