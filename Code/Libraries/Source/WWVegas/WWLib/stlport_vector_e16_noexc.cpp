// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<BfmeE16>::_M_insert_overflow, retail 0x005B3970, 186 bytes. The same
// size-optimised instantiation as stlport_vector_e16_o1.cpp, built with
// STLport exceptions off: retail's body has a plain ebp frame with no
// _STLP_TRY/_STLP_UNWIND region around the element copies, where the
// exception-enabled unit wraps them in an __EH_prolog frame (235 bytes).
// That unit's other rows depend on its exception setting, so this is a
// second unit claiming only the body the no-exceptions build reproduces.
//
// BfmeE16 is the same element-size stand-in the sibling unit documents.
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
struct BfmeE16 { float x, y, z, w; };
template class _STL::vector<BfmeE16, _STL::allocator<BfmeE16 > >;
