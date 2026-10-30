// cl: /MD /D_CRTIMP= /GX /DNDEBUG /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva004B0EBC@EmotionTrackerUpdate@@QAE_NXZ, retail 0x004B0EBC, 41 bytes.
// Honest-address method of EmotionTrackerUpdate proven by vector offsets:
// +0x90/+0x94 are m_emotions begin/end (EmotionTrackerUpdateDtor.cpp has
// EmotionTrackerVecHolder at +0x90). Iterates 4-byte pointer array,
// double-derefs +4 then tests byte at +0x18C, returns bool.
extern class GameLogic *TheGameLogic;

#include "../../../Common/GameLogicObjectLookupView.h"

#include <vector>
#include <set>
struct EmotionEntry;
struct Rva004DD018Arg;
class EmotionNugget
{
public:
	bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
	void OnDeactivation();
	char m_pad00[0x4];
	EmotionEntry *entry; // +0x04
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
class Thing;
class ModuleData;
class Xfer;
enum NameKeyType;
#include "Code/GameEngine/Include/Common/ObjectModule.h"

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

struct Rva004B0EBCInner
{
    char m_pad[4];
    void *m_ptr;
};

struct Rva004B0EBCOuter
{
    char m_pad[0x18C];
    bool m_flag;
};

bool EmotionTrackerUpdate::rva004B0EBC()
{
    void **it = (void **)nuggets.begin();
    void **end = (void **)nuggets.end();
    goto cond;
loop:
    {
        Rva004B0EBCInner *inner = *(Rva004B0EBCInner **)it;
        Rva004B0EBCOuter *outer = *(Rva004B0EBCOuter **)((char *)inner + 4);
        if (*(bool *)((char *)outer + 0x18C)) {
            return true;
        }
        ++it;
    }
cond:
    if (it != end) {
        goto loop;
    }
    return false;
}

// ?rva004B0D4C@EmotionTrackerUpdate@@QAEXHPAX@Z, retail 0x004B0D4C (36B):
// the undelayed sibling directly before PulseEmotion - same active flag and
// +0x74 source ID, frame slot cleared to 0. Object+0x24C forwards to it
// through its outermost container (0x0028EC48).
void EmotionTrackerUpdate::rva004B0D4C(int index, void *p)
{
    flags[index] = true;
    expiry[index] = 0;
    int v = (p != 0) ? *(int *)((char *)p + 0x74) : 0;
    targetID[index] = (ObjectID)v;
}

void EmotionTrackerUpdate::PulseEmotion(int index, void *p, int delay)
{
    flags[index] = true;
    expiry[index] = TheGameLogic->getFrame() + delay;
    int v = (p != 0) ? *(int *)((char *)p + 0x74) : 0;
    targetID[index] = (ObjectID)v;
}
