// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
//
// ?shouldActivate@Rva005D791C@@UAE_NPAVObject@@@Z @0x005D796F 154B, slot 6
// (offset 0x18) of vtable 0x00875DFC (class of rowed dtor 0x005D791C).
// For each ObjectID in the array behind rowed rva002A8F24 (via global
// TheSkirmishAIManager) plus rowed LeaField get 0x005C4AD1: resolve it through rowed
// GameLogic::findObjectByID via TheGameLogic; skip nulls, skip IDs already
// keys of the map<int,int> at +0x28 (rowed _M_find 0x00388F63, HordeContain
// precedent), skip when pin-only 0x005EE8DD is false; else insert the key
// into the set<int> overlaid at the same +0x28 (rowed set insert 0x000BC15D,
// horde_rank_set precedent) and return true. False when nothing inserts.
// The map and set calls address the same member per retail; the insert goes
// through a set-typed view of it.
#include <map>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
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
#include <set>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}

#include "GameLogicObjectLookupView.h"

class Player;
class Object;
#include "../../../Libraries/Include/Lib/Coord3D.h"

class PlayerList;
extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x38];
	Coord3D m_coord38;
	unsigned char m_pad44[0x74 - 0x44];
	int m_74;
};

#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

#include "../../Include/Common/Rva005EE816.h"

class Rva005D791C
{
public:
	virtual ~Rva005D791C();
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool shouldActivate(Object *arg);
private:
	unsigned char m_pad04[0x28 - 0x04];
	_STL::map<int, int> m_map28;
};

bool Rva005D791C::shouldActivate(Object *object)
{
	Player *player = object->getControllingPlayer();
	void *arr = TheSkirmishAIManager->rva002A8F24(player);
	const Rva005C4AD1LeaField *fld = *(const Rva005C4AD1LeaField *const *)((const char *)arr + 0x0C);
	ObjectID **pp = (ObjectID **)fld->get();
	ObjectID *cur = pp[0];
	for (; cur != pp[1]; ++cur)
	{
		Object *o = TheGameLogic->findObjectByID(*cur);
		if (o == 0)
			continue;
		int key = o->m_74;
		if (m_map28.find(key) != m_map28.end())
			continue;
		if (!((Rva005EE816 *)this)->rva005EE8DD((const Coord3D *)((const char *)o + 0x38), object))
			continue;
		((_STL::set<int> *)&m_map28)->insert(key);
		return true;
	}
	return false;
}
