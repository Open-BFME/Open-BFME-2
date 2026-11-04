// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector copy constructor for a 40-byte codegen view. Target
// evidence: the 71-byte body at 0x00540295 ends with RET4 at 0x005402DC and
// its copy loop call resolves to the rowed 40-byte worker at 0x005400B4.
// The call distinguishes this body from the other 40-byte vector copy view;
// the element's C++ identity remains unresolved.
// Keep this inlined unsigned max overload local; retail has one external owner.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Rva00540295Element { unsigned char bytes[40]; };

class Rva0054000B;
namespace _STL {
template <> void _Construct<Rva0054000B, Rva0054000B>(
    Rva0054000B *, const Rva0054000B &) throw();

// Retail constructs each camera-track key through the rowed 0x00540070
// worker; copying the size-only element view would skip its nontrivial copy.
template <> inline Rva00540295Element *__uninitialized_copy<
    const Rva00540295Element *, Rva00540295Element *>(
    const Rva00540295Element *first, const Rva00540295Element *last,
    Rva00540295Element *result, const __false_type &)
{
    Rva00540295Element *current = result;
    for (; first != last; ++first, ++current)
        _Construct(reinterpret_cast<Rva0054000B *>(current),
            *reinterpret_cast<const Rva0054000B *>(first));
    return current;
}
}

template class _STL::vector<Rva00540295Element, _STL::allocator<Rva00540295Element> >;
