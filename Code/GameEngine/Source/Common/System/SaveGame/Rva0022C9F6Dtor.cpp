// cl: /EHsc /MD
// stlport
//
// ??1Rva0022C9F6@@UAE@XZ @0x0022C9F6 59B: opaque virtual dtor.
// Vtable 0xBE74F0 store, then typed list-base dtor at +0x10 via rowed
// 0x004EC395, then SubsystemInterface dtor via rowed 0x001B4E74.
// Scalar at +0x0C untouched. The 28B ??_G at 0x0022C9DA calls this,
// proving the ??1 identity and virtualness. Owner identity unproven,
// honest Rva name with public-virtual UAE like opaque siblings
// (Rva00221027). Prev 0x0022C55B and next 0x0022CD65 share no TU,
// new file beside them. EH frame with states 0/-1 matches /EHsc.
#include <list>
#include "../../../../Include/GameLogic/AerialPathfinderListEntry.h"

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
extern template void _List_base<Rva00375AF7Entry, allocator<Rva00375AF7Entry> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
extern template _List_base<Rva00375AF7Entry, allocator<Rva00375AF7Entry> >::~_List_base();
}

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Include/Common/BitFlags11.h"

class AerialPathfinder : public SubsystemInterface
{
public:
	AerialPathfinder();
	virtual ~AerialPathfinder();

private:
	BitFlags<11> m_flags0C;
	_STL::_List_base<Rva00375AF7Entry, _STL::allocator<Rva00375AF7Entry> > m_list10;
};

AerialPathfinder::~AerialPathfinder()
{
}
