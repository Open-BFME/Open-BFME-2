// Reference: pristine STLport4.5.3. Address-derived opaque ABI view.
// Target boundary and stride independently establish storage width; no game class identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>



struct Rva005C84F1Record { Rva005C84F1Record(); Rva005C84F1Record(const Rva005C84F1Record&); ~Rva005C84F1Record(); Rva005C84F1Record&operator=(const Rva005C84F1Record&); private: char bytes[72]; };

// reserve calls 5C8445 -> uninitialized_copy 5C83FA -> _Construct 5C83CD;
// its old storage cleanup calls 5C84D3 -> destroy range 5C847B -> 5C8FBD.
// Both loops step by 0x48, matching this view. Forward both helpers to the
// rowed Rva005C8624Element copy and the two-pointer _Destroy spelling at
// 5C847B (declared only); these are the owners, not new identities for the
// application record. The tag is a plain local: a value-initialized
// __false_type() would add a store retail lacks.
struct Rva005C8624Element;
struct Rva005C84D3Element;
namespace _STL {
template <> Rva005C8624Element *__uninitialized_copy<Rva005C8624Element *, Rva005C8624Element *>(
    Rva005C8624Element *, Rva005C8624Element *, Rva005C8624Element *, const __false_type &);
template <> void _Destroy<Rva005C84D3Element *>(Rva005C84D3Element *, Rva005C84D3Element *);
template <> __declspec(dllimport) __forceinline Rva005C84F1Record *__uninitialized_copy<Rva005C84F1Record *, Rva005C84F1Record *>(
    Rva005C84F1Record *__first, Rva005C84F1Record *__last, Rva005C84F1Record *__result, const __false_type &)
{
    __false_type __tag;
    return reinterpret_cast<Rva005C84F1Record *>(__uninitialized_copy(
        reinterpret_cast<Rva005C8624Element *>(__first), reinterpret_cast<Rva005C8624Element *>(__last),
        reinterpret_cast<Rva005C8624Element *>(__result), __tag));
}
template <> __declspec(dllimport) __forceinline void _Destroy<Rva005C84F1Record *>(Rva005C84F1Record *__first, Rva005C84F1Record *__last)
{
    _Destroy(reinterpret_cast<Rva005C84D3Element *>(__first), reinterpret_cast<Rva005C84D3Element *>(__last));
}
}

template void _STL::vector<Rva005C84F1Record>::reserve(unsigned int);
