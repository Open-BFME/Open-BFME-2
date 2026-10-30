// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?xfer@EmotionTrackerUpdate@@MAEXPAVXfer@@@Z, retail 0x004B1ECB, 444 bytes.
// Slot 3 of ??_7EmotionTrackerUpdate 0x00C5667C (slot-2 name getter returns
// "EmotionTrackerUpdate"; the rowed dtor 0x004B1322 installs it). The rowed
// UpdateModule::xfer 0x0044DF9F, Version(1,2), twelve (bool, uint, ObjectID)
// triples from the parallel arrays at +0x24/+0x30/+0x60, each element of the
// pointer vector at +0x90 by a direct call to its slot-3 xfer 0x004DD489
// (remembering the index of the one at +0x9C when saving into +0xC4), ints
// at +0xC4 and +0xA0, before version 2 the ObjectID set at +0xA4 (rowed set<int>::insert
// on load), four raw bytes at +0xB0, an int at +0xB4, an ObjectID at +0xB8
// and from version 2 a uint at +0xBC and a bool at +0xC0. Member names not
// recovered.

#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class Rva004DD489
{
public:
	virtual void xfer(Xfer *xfer);
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
class Thing;
class ModuleData;
class Xfer;
enum NameKeyType;
#include "../../../../Include/Common/ObjectModule.h"

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

// ?xfer@EmotionTrackerUpdate@@MAEXPAVXfer@@@Z @0x004B1ECB
void EmotionTrackerUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	Xfer::Version version(1, 2);
	*xfer == version;

	for (int i = 0; i < SLOT_COUNT; ++i)
	{
		*xfer == flags[i];
		*xfer == expiry[i];
		XferObjectID(xfer, &targetID[i]);
	}

	m_C4 = -1;
	int count = nuggets.size();
	for (int j = 0; j < count; ++j)
	{
		Rva004DD489 *entry = reinterpret_cast<Rva004DD489 *>(nuggets[j]);
		if (xfer->IsStoring() && entry == reinterpret_cast<Rva004DD489 *>(active))
			m_C4 = j;
		entry->Rva004DD489::xfer(xfer);
	}

	*xfer == m_C4;
	*xfer == countdown;

	if (version.m_minimum < 2)
	{
		int size = m_emotionTargets.size();
		*xfer == size;
		if (xfer->IsLoading())
		{
			ObjectID id = INVALID_OBJECT_ID;
			for (int k = 0; k < size; ++k)
			{
				XferObjectID(xfer, &id);
				m_emotionTargets.insert(reinterpret_cast<const int &>(id));
			}
		}
		else
		{
			for (_STL::set<int>::iterator it = m_emotionTargets.begin(); it != m_emotionTargets.end(); ++it)
			{
				ObjectID id = (ObjectID)*it;
				XferObjectID(xfer, &id);
			}
		}
	}

	xfer->XferRawBytes(&forcedKind, sizeof(forcedKind));
	*xfer == forcedFrames;
	XferObjectID(xfer, &m_B8);

	if (version.m_minimum >= 2)
	{
		*xfer == m_BC;
		*xfer == m_enabled;
	}
}
