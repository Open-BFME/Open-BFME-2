// cl: /O1 /DNDEBUG /MD /arch:SSE /Oy-
// stlport
// ?ForceEmotion@EmotionTrackerUpdate@@QAEXHMH@Z @0x004B0DAC 115B. Linkbody via
// caller 0x0028ECD3 (Object::forceEmotion forwards index value arg). Stores
// index at +0xB0 when value>0; ceil scaled duration at +0xB4 via IAT ceil;
// source id at +0xB8 from arg+0x74 or 0; clears +0x9C slot via rowed
// rva004DD2C0. Evidence: pin name LINK BONUS, rowed/pinned callees,
// g_parseDurationMsecScale 1000.0f literal (VA 0x00BBE358), neighbours.
#include <math.h>

extern float g_parseDurationMsecScale;

// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing.
// Local inline conversion; AIUpdate.cpp owns the retail external helper.
static __forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct Rva004DD018Arg;
struct EmotionEntry;
class EmotionNugget
{
public:
	bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
	void OnDeactivation();
	char m_pad00[0x4];
	EmotionEntry *entry; // +0x04
};

struct Rva004B0DACArg
{
	char m_pad[0x74];
	int m_74;
};

#include "GameLogicObjectLookupView.h"
#include <vector>
#include <set>
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
class Thing;
class ModuleData;
class Xfer;
enum NameKeyType;
#include "../../Include/Common/ObjectModule.h"

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
    virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpdateModule();
    void xfer(Xfer *xfer);
protected:
    virtual void loadPostProcess();
private:
    unsigned int m_nextCallFrameAndPhase; // +0x14
    int m_indexInLogic; // +0x18
    int m_reserved1C; // +0x1C
};

class EmotionTrackerUpdateSecondaryBase
{
public:
    virtual void rva004B15E6() = 0;
};

// The ObjectID set at +0xA4; its ctor is the 25-byte STLport set ctor
// 0x000D3A71, its dtor the one the rowed dtor runs.
class Rva002EE9B7
{
public:
    Rva002EE9B7();
    ~Rva002EE9B7();
private:
    void *m_header;
    int m_count;
    int m_compare;
};

class EmotionTrackerUpdate : public UpdateModule, public EmotionTrackerUpdateSecondaryBase
{
public:
    class TauntPointFilter;
    EmotionTrackerUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~EmotionTrackerUpdate();
    virtual UpdateSleepTime update();
    virtual NameKeyType getModuleNameKey() const;
    virtual void rva004B15E6();
    EmotionNugget *rva004B13D8();
    bool rva004B0EBC();
    void rva004B0D4C(int index, void *p);
    void PulseEmotion(int index, void *p, int delay);
    void ForceEmotion(int index, float value, int arg);
protected:
    virtual void loadPostProcess();
    virtual void xfer(Xfer *xfer);
private:
    enum { SLOT_COUNT = 12 };
    bool flags[SLOT_COUNT]; // +0x24
    unsigned int expiry[SLOT_COUNT]; // +0x30
    ObjectID targetID[SLOT_COUNT]; // +0x60
    std::vector<EmotionNugget *> nuggets; // +0x90
    EmotionNugget *active; // +0x9C
    int countdown; // +0xA0
    std::set<int> m_emotionTargets; // +0xA4
    int forcedKind, forcedFrames; // +0xB0, +0xB4
    ObjectID m_B8; // +0xB8
    unsigned int m_BC; // +0xBC
    bool m_enabled; // +0xC0
    int m_C4; // +0xC4
};

void EmotionTrackerUpdate::ForceEmotion(int index, float value, int arg)
{
	if (value <= 0.0f)
		return;
	forcedKind = index;
	float prod = g_parseDurationMsecScale * value;
	prod *= 1e+03f;
	float tmp = (float)ceil((double)prod);
	forcedFrames = fast_float2long_round(tmp);
	int v = (arg != 0) ? ((Rva004B0DACArg *)arg)->m_74 : 0;
	m_B8 = (ObjectID)v;
	EmotionNugget **slotp = &active;
	EmotionNugget *slot = *slotp;
	if (slot != 0) {
		slot->OnDeactivation();
		*slotp = 0;
	}
}
