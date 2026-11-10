// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
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



struct Rva0039C028Record { Rva0039C028Record(); Rva0039C028Record(const Rva0039C028Record&); ~Rva0039C028Record(); Rva0039C028Record&operator=(const Rva0039C028Record&); private: char bytes[20]; };

// Retail reserve calls allocate-and-copy 51ED51 -> uninitialized_copy 39BA22,
// whose 0x14-stride loop invokes copy constructor 39B893; cleanup is
// 565A42 -> destroy range 22C8E3. Forward both helpers to those rows' names
// (declared only). The tag is a plain local: a value-initialized
// __false_type() would add a store retail lacks.
class Rva0039B893;
struct Rva0052BF9BElem;
Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *, Rva0039B893 *, Rva0039B893 *, const _STL::__false_type &);
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *, Rva0052BF9BElem *);
namespace _STL {
template <> __declspec(dllimport) __forceinline Rva0039C028Record *__uninitialized_copy<Rva0039C028Record *, Rva0039C028Record *>(
    Rva0039C028Record *__first, Rva0039C028Record *__last, Rva0039C028Record *__result, const __false_type &)
{
    __false_type __tag;
    return reinterpret_cast<Rva0039C028Record *>(Rva0039BA22UninitCopy(
        reinterpret_cast<Rva0039B893 *>(__first), reinterpret_cast<Rva0039B893 *>(__last),
        reinterpret_cast<Rva0039B893 *>(__result), __tag));
}
template <> __declspec(dllimport) __forceinline void _Destroy<Rva0039C028Record *>(Rva0039C028Record *__first, Rva0039C028Record *__last)
{
    Rva0022C8E3DestroyRange(reinterpret_cast<Rva0052BF9BElem *>(__first), reinterpret_cast<Rva0052BF9BElem *>(__last));
}
}

template void _STL::vector<Rva0039C028Record>::reserve(unsigned int);
