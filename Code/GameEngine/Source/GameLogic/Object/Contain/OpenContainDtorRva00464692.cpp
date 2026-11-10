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

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };
template <int NUMBITS> class BitFlags;
// Slot shapes from OpenContain.cpp, whose ??_7OpenContain@@6BUpdateModule@@@ this unit must reproduce.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


struct ContainIface20 { virtual void containIface20() = 0; };
struct ContainIface24 { virtual void containIface24() = 0; };
// The +0x28 base is the die interface: getDie (slot 7, 0x004523A9) returns it and retail
// table 0x00C46F78 holds one slot, OpenContain::onDie 0x004641B1.
#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"
// The +0x2C base is the damage interface: getDamage (slot 4, 0x004647C0) returns it, and
// retail table 0x00C58790 holds OpenContain's three empty overrides (0x0047A69C x2, 0x000D1407).
#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"
struct ContainIface30 { virtual void containIface30() = 0; };
// The +0x34 base is the create interface: getCreate (slot 3, 0x0046644A) returns it, the
// constructor stores its four-slot construction table 0x00C4EF80 there first, and retail
// table 0x00C48B28 holds OpenContain's four overrides (0x000B3FD0 x3, 0x0047A699).
#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

struct Rva00462D08Mapped { unsigned int m_bits; };
#include "../../../../Include/Common/Rva00462D35Mapped.h"
typedef _STL::map<int, Rva00462D08Mapped> Rva00462D08Map;
typedef _STL::map<int, Rva00462D35Mapped> Rva00462D35Map;

// The existing row at 0x00464391 names this destructor. The 12-byte view keeps
// the constructor-measured member extent; its map-like identity remains unknown.
class Rva00463782
{
public:
	~Rva00463782();
	_STL::_Rb_tree_node_base *m_header; // +0x00
	unsigned int m_count; // +0x04
	int m_extent; // +0x08
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
	, public DieModuleInterface
	, public DamageModuleInterface
	, public ContainIface30
	, public CreateModuleInterface
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
public:
	// retail slot 4: the rowed ?getModuleNameKey@OpenContain@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
public:
	// BehaviorModuleInterface table 0x00C43528 (+0x0C): the receiver converted to the
	// class's own interfaces, the null-preserving casts retail folds across the module family.
	virtual CollideModuleInterface *getCollide();	// slot 1: retail 0x003730FC, the +0x24 interface
	virtual ContainModuleInterface *getContain();	// slot 2: retail 0x004543A9, the +0x20 interface
	virtual CreateModuleInterface *getCreate();		// slot 3: retail 0x0046644A, the +0x34 interface
	virtual DamageModuleInterface *getDamage();		// slot 4: retail 0x004647C0, the +0x2C interface
	virtual DieModuleInterface *getDie();			// slot 7: retail 0x004523A9, the +0x28 interface
	// The +0x28 DieModuleInterface table 0x00C46F78, slot 0: rowed in OpenContainOnDie.cpp.
	virtual void onDie(const DamageInfo *damageInfo);
	// The +0x2C DamageModuleInterface table 0x00C58790: three empty bodies retail shares (ICF).
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);
	// The +0x34 CreateModuleInterface table 0x00C48B28: nothing to do on creation or build
	// completion (the shared empty body 0x000B3FD0 and false 0x0047A699, ICF).
	virtual void onCreate();
	virtual void onBuildComplete();
	virtual void slot02();
	virtual bool shouldDoOnBuildComplete() const;
	// Primary table 0x00C435E8: the OpenContain overrides already rowed under these names.
	virtual void onDelete();						// slot 8: retail 0x00464120 (OpenContainRva00464EE7.cpp)
protected:
	virtual void loadPostProcess();					// slot 1: retail 0x00463C6E (OpenContain.cpp)
	virtual void xfer(Xfer *xfer);					// slot 3: retail 0x00465EF1 (OpenContainXfer.cpp)
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
