// cl: /EHsc /MD
// stlport
//
// ??1Rva0022C9F6@@UAE@XZ @0x0022C9F6 59B: opaque virtual dtor.
// Vtable 0xBE74F0 store, then _List_base<int> dtor at +0x10 via rowed
// 0x004EC395, then SubsystemInterface dtor via rowed 0x001B4E74.
// Scalar at +0x0C untouched. The 28B ??_G at 0x0022C9DA calls this,
// proving the ??1 identity and virtualness. Owner identity unproven,
// honest Rva name with public-virtual UAE like opaque siblings
// (Rva00221027). Prev 0x0022C55B and next 0x0022CD65 share no TU,
// new file beside them. EH frame with states 0/-1 matches /EHsc.
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

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Include/Common/BitFlags11.h"

class AerialPathfinder : public SubsystemInterface
{
public:
	virtual ~AerialPathfinder();

private:
	BitFlags<11> m_flags0C;
	_STL::_List_base<int, _STL::allocator<int> > m_list10;
};

AerialPathfinder::~AerialPathfinder()
{
}
