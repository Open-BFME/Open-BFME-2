// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2 20-byte BfmeStringRecord00204A30 vector helpers (word AsciiString word AsciiString word = 0x14).
// ??$_Destroy@PAUBfmeStringRecord00204A30@@@_STL@@YAXPAUBfmeStringRecord00204A30@@0@Z retail 0x00206CBA 25B via dtor 0x00204848.
// ??$__copy@PAUBfmeStringRecord00204A30@@PAU1@H@_STL@@YAPAUBfmeStringRecord00204A30@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z retail 0x00204170 50B via assign 0x00203DDA.
// ??$__copy_ptrs@PAUBfmeStringRecord00204A30@@PAU1@@_STL@@YAPAUBfmeStringRecord00204A30@@PAU1@00U__false_type@0@@Z retail 0x00204A13 29B via __copy 0x00204170.
// Layout matches the 0x00204A30 copy ctor; callers are vector erase paths 0x00207F40 and 0x00357CA2.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>
#include "../../../../GameEngine/Include/Common/BfmeStringRecord00204A30.h"
namespace _STL {
template <> void _Construct<BfmeStringRecord00204A30, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, const BfmeStringRecord00204A30 &);
}
// Only the rowed members. A whole-class instantiation also emitted this TU's
// two erase overloads, which differ from retail and, first in link order, were
// kept over the retail copies; clear() calls the range erase that is defined
// elsewhere.
typedef _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> > BfmeStringRecord00204A30Vector;
template <> BfmeStringRecord00204A30 *BfmeStringRecord00204A30Vector::erase(BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *);
template BfmeStringRecord00204A30Vector::~vector();
template void BfmeStringRecord00204A30Vector::push_back(const BfmeStringRecord00204A30 &);
template void BfmeStringRecord00204A30Vector::clear();
template BfmeStringRecord00204A30 *_STL::__copy_ptrs<BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *>(BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *, _STL::__false_type);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00207E65Vector@@QAE@XZ=??1?$vector@UBfmeStringRecord00204A30@@V?$allocator@UBfmeStringRecord00204A30@@@_STL@@@_STL@@QAE@XZ")
