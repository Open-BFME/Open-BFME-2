// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??$_Destroy@PAURva0007BB16Record@@@_STL@@YAXPAURva0007BB16Record@@0@Z @0x0007C2D7 25B:
// ?_M_clear@?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@IAEXXZ @0x0007C614 30B:
// STLport 4.5.3 range destroy over the 0x24-byte two-string record whose dtor
// is rowed at 0x0007BB16 (strings at +0x00/+0x08, tail past +0x0C unrecovered,
// same definition as Code/GameEngine/Source/Common/StringRecordDtors.cpp).
// Retail steps esi by 0x24 and calls the rowed dtor; callers at 0x0007C5D5,
// 0x0007C614, 0x0015229C and 0x001522CF prove the 0x24 stride and the two
// vector lifetimes. Landing this unblocks those four callers.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0007BB16Record;
namespace _STL { template <> void vector<Rva0007BB16Record,allocator<Rva0007BB16Record> >::_M_fill_insert(Rva0007BB16Record *,unsigned int,Rva0007BB16Record const &); }

#include "Rva0007BB16Record.h"

namespace _STL
{

template <>
inline void _Destroy<Rva0007BB16Record *>(Rva0007BB16Record *__first, Rva0007BB16Record *__last)
{
	for (; __first != __last; ++__first)
		_Destroy(&*__first);
}

template<> vector<Rva0007BB16Record> &vector<Rva0007BB16Record>::operator=(const vector<Rva0007BB16Record> &);

}

template void _STL::vector<Rva0007BB16Record>::_M_clear();

// Only this unit's rowed members; the rest of vector<Rva0007BB16Record> has
// other retail owners (StlportVectorGrowthFootprints.cpp, Rva0015229CEraseRange.cpp, ...).
template Rva0007BB16Record *_STL::uninitialized_fill_n<Rva0007BB16Record *, unsigned int, Rva0007BB16Record>(Rva0007BB16Record *, unsigned int, const Rva0007BB16Record &);
template void _STL::_Construct<Rva0007BB16Record, Rva0007BB16Record>(Rva0007BB16Record *, const Rva0007BB16Record &);

template void _STL::_Destroy<Rva0007BB16Record *>(Rva0007BB16Record *, Rva0007BB16Record *);

class Rva0007C632Dtor
{
public:
	~Rva0007C632Dtor();
};

Rva0007C632Dtor::~Rva0007C632Dtor()
{
	((_STL::vector<Rva0007BB16Record> *)this)->~vector();
}

