// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 instantiation used as a target-local structural view.
// Retail helper calls establish an 8-byte deque element with trivial destruction;
// the original element name and fields are not identified. This neutral view
// preserves only those supported facts.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <deque>
struct BfmeTrivialDequeElement8
{
    unsigned char opaque[8];
};
typedef char BfmeTrivialDequeElement8_is_8_bytes[
    sizeof(BfmeTrivialDequeElement8) == 8 ? 1 : -1];
template class _STL::deque<BfmeTrivialDequeElement8,
                           _STL::allocator<BfmeTrivialDequeElement8> >;
