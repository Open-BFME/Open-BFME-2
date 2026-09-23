// cl: /O1 /GX /DNDEBUG /MD
//
// ??0StealthDetectorUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004A2CB9, 116 bytes. Behavior-side ctor in the StealthDetectorUpdate
// file-unit (pool key 0x4A2C74 plus ModuleData proc 0x4A2D82 plus ModuleData
// ctor plus both factories all rowed): the rowed UpdateModule base ctor
// (0x253390 thing plus data) runs first, the inherited +0x0C/+0x10 pointer
// slots re-store to TU-local dummies (DIR32-masked), then the module parks
// itself awake with setWakeFrame(obj frames) through the pin at 0x44DF71 - a
// GetGameLogicRandomValue (rowed) roll over the owner range when the owner
// flag byte is clear else UPDATE_SLEEP_FOREVER. Recipe: BoredUpdateCtor.cpp
// opaque-base pattern (the declared-only base dtor drives the single EH state
// with zero emitted code) plus the PassiveAreaEffectBehaviorCtor.cpp
// setWakeFrame tail. The row supersedes the sole-caller pin at the same
// address.

class Thing;
class ModuleData;
class Object;

struct StealthDetectorOwner
{
	int m_pad00;
	int m_pad04;
	int m_maxRange;
	int m_pad0C;
	unsigned char m_flag10;
};

static int s_dummy0C;
static int s_dummy10;

static const char s_file[] = "StealthDetectorUpdate";

enum { UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

int __cdecl GetGameLogicRandomValue(int low, int high, char *file, int line);

// Opaque UpdateModule base; ctor resolves to its row. The hidden vptr sits at
// +0 so m_owner lands at +4; +0x0C/+0x10 are the re-stored inherited slots.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	StealthDetectorOwner *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	void setWakeFrame(Object *obj, unsigned int frame);
};

class StealthDetectorUpdate : public UpdateModule
{
public:
	StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~StealthDetectorUpdate();
};

// ??0StealthDetectorUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
StealthDetectorUpdate::StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	StealthDetectorOwner *owner = m_owner;
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	unsigned int wake;
	if (owner->m_flag10 == 0)
		wake = GetGameLogicRandomValue(1, owner->m_maxRange, const_cast<char *>(s_file), 79);
	else
		wake = UPDATE_SLEEP_FOREVER;
	setWakeFrame(*(Object **)((char *)this + 8), wake);
}
