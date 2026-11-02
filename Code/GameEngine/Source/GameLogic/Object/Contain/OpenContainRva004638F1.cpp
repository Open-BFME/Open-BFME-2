// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
//
// ?addToContainList@OpenContain@@UAEXPAVObject@@@Z @0x004638F1 42B
// Name: ZH OpenContain::addToContainList; slot 40 of this +0x20 interface is
// addToContainList in rowed TunnelContain 0x0047DC75 and CaveContain 0x0046646E,
// and WorldBuilder names the SiegeEngineContain override (0x0047C07F) the same.
// OpenContain slot-40 add-rider: push rider as int into +0x34 list<int>,
// bump +0x38, and bump +0x48 when rider template kind bit1 set.
// Evidence: vslot 78 of 0x00848AA0 SlaughterHordeContain; pin OpenContain;
// callers 0x0047C155 and HordeSiege override 0x0047D17E; neighbours
// Rva004DD206TwoTreeConstructor and HordeTransportContainRva00463A4D.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
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

#include "../../../../Include/Common/ThingTemplate.h"

#include "../object.h"

class OpenContain
{
public:
	virtual void addToContainList(Object *rider);
	virtual Object *getClosestRider(const Coord3D *pos);
private:
	char m_pad[0x30];
	_STL::list<int> m_list;
	int m_38;
	char m_pad2[0x48 - 0x3C];
	int m_48;
};

// Select-any like the ZH-donor copy in OpenContain.cpp (that TU comes later in
// link order with a differing body, so this retail body is the one kept); the
// anchor keeps the body emitted.
inline void OpenContain::addToContainList(Object *rider)
{
	m_list.push_back((const int &)rider);
	++m_38;
	if (*(unsigned char *)((char *)rider->m_template + 0x10C) & 2)
		++m_48;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitOpenContainAddToContainList@@YAXPAVOpenContain@@@Z absent-from-retail
void bfmeEmitOpenContainAddToContainList(OpenContain *openContain)
{
	openContain->OpenContain::addToContainList((Object *)0);
}

// ?getClosestRider@OpenContain@@UAEPAVObject@@PBUCoord3D@@@Z @0x004632E0 91B (RET 4):
// the shared contain-interface slot every OpenContain-derived table holds
// (e.g. 0x008434A4, 0x00843B64): the contained object nearest, in the ground
// plane, to the given position, or null when nothing is inside.
Object *OpenContain::getClosestRider(const Coord3D *pos)
{
	Object *closest = 0;
	float closestDistSqr = 3.402823466e+38f;
	for (_STL::list<int>::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		Object *obj = (Object *)*it;
		if (obj)
		{
			float dx = pos->x - obj->getPosition()->x;
			float dy = pos->y - obj->getPosition()->y;
			float distSqr = dx * dx + dy * dy;
			if (closest == 0 || distSqr < closestDistSqr)
			{
				closest = obj;
				closestDistSqr = distSqr;
			}
		}
	}
	return closest;
}
