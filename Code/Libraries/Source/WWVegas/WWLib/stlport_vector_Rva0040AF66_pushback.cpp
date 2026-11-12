// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@VRva0040AF66@@V?$allocator@VRva0040AF66@@@_STL@@@_STL@@QAEXABVRva0040AF66@@@Z @ 0x0040BA6A (55B). Vector push_back fast path via rowed _Construct 0x0040B17B else rowed _M_insert_overflow 0x0040B8E8.
// Evidence: chain lane calls 0x0040B8E8 just landed; retail cmp je Construct add 0x68 vs overflow with n=1; caller 0x0040BAE7; same 55B shape as sibling pushback 0x0040BA33.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}


#include "../../../../GameEngine/Include/Common/BfmeFixedStorage0004543D.h"

#include "../../../../GameEngine/Include/Common/Rva0040AF66.h"

namespace _STL
{
template <> void _Construct<Rva0040AF66, Rva0040AF66>(Rva0040AF66 *, const Rva0040AF66 &);
}

// _M_clear's range destroy is retail's rowed _Destroy<Rva0040AFF3*>
// (0x0040B547, stlport_destroy_range_0040B547.cpp); forward to it so the
// _M_clear copy calls its owner.
struct Rva0040AFF3;
namespace _STL {
template <> void _Destroy<Rva0040AFF3 *>(Rva0040AFF3 *, Rva0040AFF3 *);
template <> __declspec(dllimport) __forceinline void _Destroy<Rva0040AF66 *>(Rva0040AF66 *__first, Rva0040AF66 *__last)
{ _Destroy(reinterpret_cast<Rva0040AFF3 *>(__first), reinterpret_cast<Rva0040AFF3 *>(__last)); }
}

template void _STL::vector<Rva0040AF66>::push_back(const Rva0040AF66 &);
