// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4BfmeStringRecord00111ACF@@QAEAAU0@ABU0@@Z @0x00101EF5 60B unlock via rowed set 0x000366F0 plus caller 0x00101FA6 prev 0x00101ECF next 0x00101F5C layout from StringRecordInlineCopyBFME2
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
struct BfmeStringRecord00111ACF {
    AsciiString first;
    unsigned int word4;
    struct FloatStorage { float values[4]; } middle;
    AsciiString second;
    BfmeStringRecord00111ACF &operator=(const BfmeStringRecord00111ACF &o);
    ~BfmeStringRecord00111ACF();
};
BfmeStringRecord00111ACF &BfmeStringRecord00111ACF::operator=(const BfmeStringRecord00111ACF &o)
{
    first = o.first;
    word4 = o.word4;
    for (int i = 0; i < 4; ++i)
        middle.values[i] = o.middle.values[i];
    second = o.second;
    return *this;
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> BfmeStringRecord00111ACF * __copy_backward<BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, int>(BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> BfmeStringRecord00111ACF * __uninitialized_copy<BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *>(BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, __false_type const &); }
namespace _STL { template <> void fill<BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF>(BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF const &); }
namespace _STL { template <> BfmeStringRecord00111ACF * vector<BfmeStringRecord00111ACF, allocator<BfmeStringRecord00111ACF> >::erase(BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *); }
namespace _STL { template <> void vector<BfmeStringRecord00111ACF, allocator<BfmeStringRecord00111ACF> >::push_back(BfmeStringRecord00111ACF const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__copy@PAUBfmeStringRecord00111ACF@@PAU1@H@_STL@@YAPAUBfmeStringRecord00111ACF@@PAU1@00:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmeStringRecord00111ACF * __copy<BfmeStringRecord00111ACF *,BfmeStringRecord00111ACF *,int>(BfmeStringRecord00111ACF *,BfmeStringRecord00111ACF *,BfmeStringRecord00111ACF *,random_access_iterator_tag const &,int *); }
// The growth helper is emitted by stlport_vector_stringrecord_111acf_allocate_copy.cpp.
namespace _STL { template <> void vector<BfmeStringRecord00111ACF>::_M_insert_overflow(BfmeStringRecord00111ACF *, const BfmeStringRecord00111ACF &, const __false_type &, unsigned int, bool); }
template class _STL::vector<BfmeStringRecord00111ACF, _STL::allocator<BfmeStringRecord00111ACF> >;
