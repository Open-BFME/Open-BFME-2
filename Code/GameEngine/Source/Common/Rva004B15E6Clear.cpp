// cl: /MD /D_CRTIMP= /GX /DNDEBUG /D_STLP_USE_STATIC_LIB /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?rva004B15E6@EmotionTrackerUpdate@@UAEXXZ @0x004B15E6 77B.
// EmotionTrackerUpdate's override of slot 0 of its +0x20 interface (the
// derived table's slot, ctor 0x004B21B9 / dtor 0x004B1322), so its this is
// that subobject: +0x70/+0x7C here are the object's +0x90 emotion vector
// and +0x9C current emotion. When the current one is live, call 0x004DD2C0
// on it and clear it. Then destroy each non-null element of the vector
// through the rowed destructor 0x004DCE8E and operator delete 0x0002FD60,
// and erase the whole range through the rowed vector erase 0x0031BD55.

#include <vector>
#include <set>
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

class Rva004DCE8E
{
public:
	~Rva004DCE8E();
};

// The UpdateModule part (primary vftable, 0x20 bytes) and the one-slot
// interface at +0x20.


#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
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

void EmotionTrackerUpdate::rva004B15E6()
{
	EmotionNugget *slot = active;
	if (slot != 0)
	{
		slot->OnDeactivation();
		active = 0;
	}
	std::vector<EmotionNugget *> *vec = &nuggets;
	for (EmotionNugget **it = vec->begin(); it != nuggets.end(); ++it)
	{
		Rva004DCE8E *elem = (Rva004DCE8E *)*it;
		if (elem != 0)
		{
			elem->~Rva004DCE8E();
			::operator delete(elem);
		}
	}
	reinterpret_cast<std::vector<void *> *>(vec)->erase(
		reinterpret_cast<void **>(vec->begin()), reinterpret_cast<void **>(vec->end()));
}
