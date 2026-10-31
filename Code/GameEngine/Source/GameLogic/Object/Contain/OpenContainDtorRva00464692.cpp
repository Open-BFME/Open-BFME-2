// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??1OpenContain@@UAE@XZ @0x00464692 (227B). Identity from its audited
// deleting-dtor caller 0x00464B7A and OpenContain vtable/string evidence.
// The 0x54 list loop, Object+0x274 store, and GameLogic call are target-proven.
// Member offsets follow the byte-matched constructor at 0x004649F8; destructor
// callees at +0x3C, +0x5C, and +0xF0 refine the donor's generic map labels.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>

class Thing;
class ModuleData;
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };
template <int NUMBITS> class BitFlags;
// Slot shapes from OpenContain.cpp, whose ??_7OpenContain@@6BUpdateModule@@@ this unit must reproduce.
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual BitFlags<13> getDisabledTypesToProcess() const = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual BitFlags<13> getDisabledTypesToProcess() const;
protected:
	void setWakeFrame(Object *obj, unsigned int frame);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

struct ContainIface20 { virtual void containIface20() = 0; };
struct ContainIface24 { virtual void containIface24() = 0; };
struct ContainIface28 { virtual void containIface28() = 0; };
struct ContainIface2C { virtual void containIface2C() = 0; };
struct ContainIface30 { virtual void containIface30() = 0; };
struct ContainIface34 { virtual void containIface34() = 0; };

struct Rva00462D08Mapped { unsigned int m_bits; };
struct Rva00462D35Mapped { unsigned int m_bits; };
typedef _STL::map<int, Rva00462D08Mapped> Rva00462D08Map;
typedef _STL::map<int, Rva00462D35Mapped> Rva00462D35Map;

// The existing row at 0x00464391 names this destructor. The 12-byte view keeps
// the constructor-measured member extent; its map-like identity remains unknown.
class Rva00463782
{
public:
	unsigned int m_header;
	int m_flag;
	int m_extent;
	~Rva00463782();
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

#include "../object.h"

#include "../../../Common/GameLogicObjectLookupView.h"

// map<ObjectID, int>: the tree family dtor 0x00286852 -> clear 0x00286656 ->
// erase 0x00286183 (one instantiation: the self-recursive erase is not ICF-folded;
// AITargetHeuristicEnemyStructure::findBestTarget 0x005735C6 keys it by object ID).
typedef _STL::map<ObjectID, int> ObjectIDIntMap;
class OpenContain
	: public UpdateModule
	, public ContainIface20
	, public ContainIface24
	, public ContainIface28
	, public ContainIface2C
	, public ContainIface30
	, public ContainIface34
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
	virtual UpdateSleepTime update();
private:
	int m_bfme38;
	Rva00463782 m_riderMapA;
	ObjectIDIntMap m_riderMapB;
	_STL::list<int> m_riderIdListA;
	int m_bfme58;
	Rva00462D08Map m_riderMapC;
	int m_bfme68;
	int m_bfme6C;
	int m_bfme70;
	_STL::list<int> m_riderIdListB;
	int m_bfme78;
	int m_bfme7C;
	int m_bfme80;
	Rva0042526Member m_store84;
	float m_bfmeD0;
	float m_bfmeD4;
	float m_bfmeD8;
	unsigned char m_bfmeDC;
	unsigned char m_bfmeDD;
	unsigned char m_bfmeDE;
	unsigned char m_bfmeDF;
	unsigned char m_bfmeE0;
	unsigned char m_bfmeE1;
	unsigned char m_padE2[2];
	int m_bfmeE4;
	int m_bfmeE8;
	int m_bfmeEC;
	Rva00462D35Map m_riderMapDraw;
};

OpenContain::~OpenContain()
{
	for (_STL::list<int>::iterator it = m_riderIdListA.begin(); it != m_riderIdListA.end(); ) {
		Object *rider = (Object *)(*it);
		++it;
		rider->m_containedBy = 0;
		TheGameLogic->destroyObject(rider);
	}

}
