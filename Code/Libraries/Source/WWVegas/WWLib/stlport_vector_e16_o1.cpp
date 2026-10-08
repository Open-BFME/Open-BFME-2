// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
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
struct BfmeE16 { float x, y, z, w; };
template class _STL::vector<BfmeE16, _STL::allocator<BfmeE16 > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva004BA1C8@@V?$allocator@VRva004BA1C8@@@_STL@@@_STL@@QAE@ABV?$allocator@VRva004BA1C8@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@QAE@ABV?$allocator@VRva00297360Element@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAE@ABV?$allocator@UQuantityModifier@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@PAUBfmeExpLevelDraw@@V?$allocator@PAUBfmeExpLevelDraw@@@_STL@@@_STL@@QAE@ABV?$allocator@PAUBfmeExpLevelDraw@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_Vector_base@PAUBfmeMorphCondition@@V?$allocator@PAUBfmeMorphCondition@@@_STL@@@_STL@@QAE@ABV?$allocator@PAUBfmeMorphCondition@@@1@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
#pragma comment(linker, "/alternatename:??0AICommandCoordVector@@QAE@ABUAICommandCoordAlloc@@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
