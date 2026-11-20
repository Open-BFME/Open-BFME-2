// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022C9F6@@QAE@XZ @0x0022C987 75B: ctor for the class whose
// virtual dtor lives rowed at 0x0022C9F6. Calls rowed baseConstruct
// 0x001B4E63 via the novtable base, stores vtable 0xBE74F0, constructs
// BitFlags<11> at +0xC via rowed 0x003B31AD then _List_base at +0x10
// via rowed 0x0035C9A6, then or 0x28 into the flag word. Evidence: leaf
// packet calls rowed baseConstruct plus rowed BitFlags and List_base;
// vtable matches the rowed dtor; caller at 0x0022F405.
//
// Register-allocation note (established from the byte match): retail binds
// this to edi and keeps esi as the +0xC scratch, so the bitword address is
// materialised into a callee-save before the base ctor and re-dereferenced
// after it. Reproducing that live range needs the address local to survive
// past the flag write, hence the two |0x28 stores rather than one.
#include <list>
#include "../../../../Include/GameLogic/AerialPathfinderListEntry.h"

#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../../../Include/Common/BitFlags11.h"

// Both native lifetime edges use SubsystemInterface: constructor 0x001B4E63
// and the constructor's unwind cleanup 0x001B4E74. Use the same base as the
// rowed AerialPathfinder destructor, rather than a second private base name.
class AerialPathfinder : public SubsystemInterface
{
public:
	AerialPathfinder();
	virtual ~AerialPathfinder();
private:
	BitFlags<11> m_flags0C;
	_STL::_List_base<Rva00375AF7Entry, _STL::allocator<Rva00375AF7Entry> > m_list10;
};

AerialPathfinder::AerialPathfinder()
	: m_flags0C()
	, m_list10(_STL::allocator<Rva00375AF7Entry>())
{
	unsigned int *w = reinterpret_cast<unsigned int *>(&m_flags0C);
	*(int *)&m_flags0C |= 0x28;
	*w |= 0x28;
}


namespace _STL
{
template _List_base<Rva00375AF7Entry, allocator<Rva00375AF7Entry> >::_List_base(
    const allocator<Rva00375AF7Entry> &);
template _List_base<Rva00375AF7Entry, allocator<Rva00375AF7Entry> >::~_List_base();
template void _List_base<Rva00375AF7Entry, allocator<Rva00375AF7Entry> >::clear();
}
