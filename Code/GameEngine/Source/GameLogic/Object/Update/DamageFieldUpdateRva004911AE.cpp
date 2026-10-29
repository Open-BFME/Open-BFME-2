// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
//
// DamageFieldUpdate::update: native 0x00491316..0x0049157D (615 bytes).
// Identity: WorldBuilder update at VA 0x011DF5A0 and the native module's
// upgrade/filter/query/weapon/update call chain. The native body independently
// establishes Object position +0x38, ObjectID +0x74, module data +0x04,
// owning Object +0x08, update interface +0x10 and retained victims +0x2C.
//
// Algorithm provenance: STLport 4.5.3 list and find, plus the WB control-flow
// lead. Retail proves a distinct fixed-node pool at 0x00DA60E8 and free list
// at 0x00DA60F0. BfmeObjectIdPoolAllocator is a structural allocator view;
// its original target type name is unknown. Its nine emitted helpers are
// independently verified whole-body/relocation folds onto existing providers.
// The allocator parameter preserves the established ObjectID iterator/find
// identity while distinguishing this pool from the normal allocator family.
//
// The existing 126-byte fire helper stays in its measured source unit.
// Native 0x004914AA proves thiscall void(Object*); weapon at +0x20, damage
// list at +0x24, entry weapon/frame/flag at +0/+4/+8 and GameLogic frame
// +0x40 are native facts. Original helper name remains unknown.
// Evidence: reverse/attempt_support/damagefield-pool-20261019/.
//
template <class T> class BfmeObjectIdPoolAllocator;
namespace _STL {
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> &__stl_alloc_rebind(BfmeObjectIdPoolAllocator<T> &sourceAllocator, const U *)
{ return (BfmeObjectIdPoolAllocator<U> &)sourceAllocator; }
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> __stl_alloc_create(const BfmeObjectIdPoolAllocator<T> &, const U *)
{ return BfmeObjectIdPoolAllocator<U>(); }
}
#include "ascii_string.h"

typedef float Real;
typedef int Int;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ObjectID { INVALID_ID = 0 };

#include "Coord3D.h"

class Player;
class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;	// has the upgrade
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;			// +0x74
};

// Partition filters: vptr, +0x04 chain link, then each filter's members.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *spec, Player *player, bool flag) : m_spec(spec), m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	const void *m_spec;
	Player *m_player;
	bool m_flag;
};
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	Object *m_obj;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(Object *obj, Int mode, bool flag) : m_obj(obj), m_mode(mode), m_flag(flag) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Object *m_obj;
	Int m_mode;
	bool m_flag;
};

#include "PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#include <list>
#include <algorithm>
// Use the established TU-local comparison adapter so inlined iterator tests
// do not emit a differently optimized copy of the rowed iterator-base member.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits> &a,
                              const _List_iterator<T, Traits> &b)
{ return a._M_node != b._M_node; }
}
// Target node allocation/return is a distinct fixed-size freelist family.
// This VC7.1 STLport configuration uses the pre-member-template allocator
// adapter: declare its rebind/create overloads before the first STL header.
// Iterator identity depends on ObjectID, not on this allocator parameter.
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool;
extern void *g_freeList;
template <class T> class BfmeObjectIdPoolAllocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef unsigned int size_type;
    typedef int difference_type;
    template <class U> struct rebind { typedef BfmeObjectIdPoolAllocator<U> other; };
    BfmeObjectIdPoolAllocator() {}
    template <class U> BfmeObjectIdPoolAllocator(const BfmeObjectIdPoolAllocator<U> &) {}
    pointer allocate(size_type, const void * = 0) { return (pointer)g_freelistPool.pop(); }
    void deallocate(pointer p, size_type)
    {
        if (p)
        {
            *(void **)p = g_freeList;
            g_freeList = p;
        }
    }
    void construct(pointer p, const_reference value) { new (p) T(value); }
    void destroy(pointer p) { p->~T(); }
    size_type max_size() const { return (size_type)(-1)/sizeof(T); }
};
namespace _STL {
template <class T, class U> struct _Alloc_traits<T, BfmeObjectIdPoolAllocator<U> > {
    typedef BfmeObjectIdPoolAllocator<U> _Orig;
    typedef BfmeObjectIdPoolAllocator<T> allocator_type;
    static allocator_type create_allocator(const _Orig &originalAllocator) { return allocator_type(originalAllocator); }
};
}
namespace _STL {
typedef _List_node<ObjectID> DamageFieldPoolNode;
template <> __declspec(noinline)
_STLP_alloc_proxy<DamageFieldPoolNode *, DamageFieldPoolNode, BfmeObjectIdPoolAllocator<DamageFieldPoolNode> >::_STLP_alloc_proxy(
    const BfmeObjectIdPoolAllocator<DamageFieldPoolNode> &a, DamageFieldPoolNode *p)
    : BfmeObjectIdPoolAllocator<DamageFieldPoolNode>(a), _M_data(p) {}
}
typedef std::list<ObjectID, BfmeObjectIdPoolAllocator<ObjectID> > ObjectIDList;
template <> ObjectIDList::iterator ObjectIDList::erase(iterator position)
{
    // Native pool erase loads prev before next; preserve its actual unlink
    // and free-list operation (the ObjectID payload has no destructor work).
    _STL::_List_node_base *node = position._M_node;
    _STL::_List_node_base *prev = node->_M_prev;
    _STL::_List_node_base *next = node->_M_next;
    prev->_M_next = next;
    next->_M_prev = prev;
    node->_M_next = (_STL::_List_node_base *)g_freeList;
    g_freeList = node;
    return iterator((_STL::_List_node<ObjectID> *)next);
}
struct DamageFieldUpdateModuleData
{
	unsigned char m_pad00[0x10];
	Int m_radius;			// +0x10
	unsigned char m_filterSpec[4];	// +0x14
	AsciiString m_requiredUpgrade;	// +0x18
};

#include "../../../../Include/Common/ObjectModule.h"
class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	int m_14, m_18, m_1c;
};
enum WeaponStatus { READY_TO_FIRE, OUT_OF_AMMO, BETWEEN_FIRING_SHOTS, RELOADING_CLIP, PRE_ATTACK, WEAPON_STATUS_5 };
#include "../../../../Include/GameLogic/Weapon.h"
struct DamageEntry { Weapon *m_weapon; unsigned int m_frame04; unsigned char m_flag08; };
struct DamageNode { DamageNode *m_next00, *m_prev04; DamageEntry *m_entry08; };
class GameLogic;
extern GameLogic *TheGameLogic;
struct DamageFieldFrameView { char pad[0x40]; unsigned int frame; };
class FireWeaponUpdate : public UpdateModule
{
protected:
	UpdateSleepTime rva0048BA3E();
	Weapon *m_20; DamageNode *m_24; void *m_28;
};
class DamageFieldUpdate : public FireWeaponUpdate
{
public:
	virtual UpdateSleepTime update();
	__declspec(noinline) void rva004911AE(Object *other);
private:
	ObjectIDList m_victims;	// +0x2C
};

UpdateSleepTime DamageFieldUpdate::update()
{
	const DamageFieldUpdateModuleData *data = reinterpret_cast<const DamageFieldUpdateModuleData *>(getModuleData());
	Object *me = m_object;
	if (data && me)
	{
		if (data->m_requiredUpgrade != AsciiString::TheEmptyString)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_requiredUpgrade);
			if (upgrade && !me->hasUpgrade(upgrade))
				return UPDATE_SLEEP_NONE;
		}

		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(me->getPosition(), (Real)data->m_radius, 0,
			Rva00260EB1Filter(me, 1, false).link(Rva0026119DFilter().link(Rva002611BFFilter(me).link(&Rva002614ECFilter(data->m_filterSpec, me->getControllingPlayer(), true)))), 0);

		ObjectIDList inRange;
		ObjectIDList gone;
		Object *other = 0;
		while ((other = iter.next()) != 0)
		{
			inRange.push_back(other->getID());
			bool found = false;
			if (std::find(m_victims.begin(), m_victims.end(), other->getID()) != m_victims.end())
				found = true;
			if (!found)
			{
				rva004911AE(other);
				m_victims.push_back(other->getID());
			}
		}

		ObjectIDList::iterator it;
		for (it = m_victims.begin(); it != m_victims.end(); ++it)
		{
			ObjectID id = *it;
			bool found = false;
			if (std::find(inRange.begin(), inRange.end(), id) != inRange.end())
				found = true;
			if (!found)
				gone.push_back(id);
		}

		ObjectIDList::iterator git;
		for (git = gone.begin(); git != gone.end(); ++git)
		{
			ObjectID id = *git;
			m_victims.remove(id);
		}
	}
	return FireWeaponUpdate::rva0048BA3E();
}

void DamageFieldUpdate::rva004911AE(Object *other)
{
	if (other == 0)
		return;
	if (m_20 != 0)
	{
		if (m_20->getStatus() != READY_TO_FIRE)
			return;
		m_20->forceFireWeapon(m_object, other);
		return;
	}
	unsigned int frame = ((DamageFieldFrameView *)TheGameLogic)->frame;
	for (DamageNode *node = m_24->m_next00; node != m_24; node = node->m_next00)
	{
		DamageEntry *entry = node->m_entry08;
		if (frame <= entry->m_frame04)
			continue;
		if (entry->m_weapon->getStatus() != READY_TO_FIRE)
			continue;
		entry->m_weapon->forceFireWeapon(m_object, other);
		if (entry->m_flag08 == 0)
			continue;
		entry->m_frame04 = (unsigned int)-1;
	}
}
