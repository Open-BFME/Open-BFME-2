// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::operator= for a 4-byte POD element, retail 0x0026F4F4
// (163 bytes), rowed as ?dup_0026f4f4. The body is folded across 4-byte-POD
// vectors: 27 image-wide callers and none with a proven element type, so no
// single T is claimed. int is the spelling compiled here; any 4-byte POD
// instantiation emits the same bytes.
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
template class _STL::vector<int, _STL::allocator<int > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeCopyTwoCDF@BfmePartCDF@@QAEXPAU1@@Z=??4?$vector@HV?$allocator@H@_STL@@@_STL@@QAEAAV01@ABV01@@Z")
