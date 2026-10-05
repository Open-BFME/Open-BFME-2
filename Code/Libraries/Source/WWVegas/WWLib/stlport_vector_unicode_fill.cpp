// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAVUnicodeString@@IV1@@_STL@@YAPAVUnicodeString@@PAV1@IABV1@ABU__false_type@0@@Z retail 0x00054E66 37B
// Evidence: same 37B count-loop plus _Construct shape as other vector fill_n rows; here fills UnicodeString via rowed _Construct 0x00054DF6;
// element and flags match stlport_vector_unicode_reserve.cpp; caller 0x0005B5A3.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "unicode_string.h"

namespace _STL {
template <> void _Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
}

template class _STL::vector<UnicodeString, _STL::allocator<UnicodeString> >;
