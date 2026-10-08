// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/vendor/stlport/stl
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
// Use the pristine algorithms while retaining BFME2's allocation shim.
// The shim's algorithm header forces the copy-backward aux layer inline,
// producing a competing 65-byte body instead of retail's 63-byte wrapper.
#include <_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeE12 { float x, y, z; };
template class _STL::deque<BfmeE12, _STL::allocator<BfmeE12 > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?allocate@?$allocator@W4ScienceType@@@_STL@@QAEPAW4ScienceType@@IPBX@Z=?allocate@?$allocator@PAUBfmeE12@@@_STL@@QBEPAPAUBfmeE12@@IPBX@Z")
