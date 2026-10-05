// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__copy@PBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@PAV12@H at
// retail 0x00079F8A (50B): stride-12 copy loop over narrow basic_string.
// Retail calls the rowed copy-assign at 0x000120C0, i.e. STLport 4.6-style
// operator= returning assign(__s); the vendored 4.5.3 header instead emits a
// self-check plus range-assign. The 4.6-style specialization below reconciles
// the version gap; it inlines into the loop. Caller 0x0007A414 in 0x0007A401.
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

#include <algorithm>
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > NarrowStr12;

template NarrowStr12 &NarrowStr12::assign(const NarrowStr12 &);

template <> inline NarrowStr12 &NarrowStr12::operator=(const NarrowStr12 &__s) { return assign(__s); }

template NarrowStr12 *_STL::copy<const NarrowStr12 *, NarrowStr12 *>(const NarrowStr12 *, const NarrowStr12 *, NarrowStr12 *);
