#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
// cl: /MD /D_CRTIMP= /GX /DNDEBUG /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?loadPostProcess@EmotionTrackerUpdate@@MAEXXZ, retail 0x004B0FB9, 50 bytes:
// slot 1 of EmotionTrackerUpdate's primary vtable 0x00C5667C (ctors 0x004B1333,
// 0x004B21EF), the slot UpdateModule::loadPostProcess 0x0058B03E fills for
// modules that do not override it. Re-derives the pointer at +0x9C from the
// index at +0xC4 into the pointer vector at +0x90 (begin/end at +0x90/+0x94),
// null when the index is out of range.
class ModuleData;
class Object;



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

void EmotionTrackerUpdate::loadPostProcess()
{
	if (m_C4 >= 0 && m_C4 < nuggets.size())
		active = nuggets[m_C4];
	else
		active = 0;
}
