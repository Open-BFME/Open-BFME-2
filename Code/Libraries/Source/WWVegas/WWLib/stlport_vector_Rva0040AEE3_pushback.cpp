// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@VRva0040AEE3@@V?$allocator@VRva0040AEE3@@@_STL@@@_STL@@QAEXABVRva0040AEE3@@@Z @ 0x0040BA33 (55B). Vector push_back fast path via pinned _Construct 0x0040B14E else rowed _M_insert_overflow 0x0040B834.
// Evidence: chain lane calls 0x0040B834 just landed; retail cmp je Construct add 0x10 vs overflow with n=1; caller 0x0040BAC1; same 55B shape as sibling pushbacks; vector start finish end at +0/+4/+8 stride 0x10.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
// Preserve the visible STL loops and call the existing native placement-copy
// provider for this same record view. The application identity remains unknown.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
class Rva0040AEE3;
void Rva0040B14EConstruct(Rva0040AEE3 *, const Rva0040AEE3 &);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0040AEE3 *destination,
                                    const Rva0040AEE3 &source)
{
    Rva0040B14EConstruct(destination, source);
}
}

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


class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

namespace _STL
{

}

template void _STL::vector<Rva0040AEE3>::push_back(const Rva0040AEE3 &);
