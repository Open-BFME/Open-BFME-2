// cl: /EHsc /MD
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
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@UBfmePod8@@@_STL@@@_STL@@QBEXPAU?$_List_node@UBfmePo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> void allocator<_List_node<BfmePod8> >::deallocate(_List_node<BfmePod8> *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> void _List_base<BfmePod8,allocator<BfmePod8> >::clear(); }

#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) Rva0022C987Base
{
public:
	Rva0022C987Base() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva0022C987Base();
private:
	char m_pad[8];
};

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags();
public:
	unsigned int m_word;
};

struct BfmePod8 { int a[2]; };

class AerialPathfinder : public Rva0022C987Base
{
public:
	AerialPathfinder();
	virtual ~AerialPathfinder();
private:
	BitFlags<11> m_flags0C;
	_STL::_List_base<BfmePod8, _STL::allocator<BfmePod8> > m_list10;
};

AerialPathfinder::AerialPathfinder()
	: m_flags0C()
	, m_list10(_STL::allocator<BfmePod8>())
{
	unsigned int *w = &m_flags0C.m_word;
	*(int *)&m_flags0C |= 0x28;
	*w |= 0x28;
}