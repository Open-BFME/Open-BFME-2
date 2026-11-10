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



struct Rva002E26E1Record { Rva002E26E1Record(); Rva002E26E1Record(const Rva002E26E1Record&); ~Rva002E26E1Record(); Rva002E26E1Record&operator=(const Rva002E26E1Record&); private: char bytes[216]; };

// Native allocate/copy 2E1693 calls 2E163C -> cdecl placement copy 2E160F.
// Clear 2E26C3 calls range wrapper 2AF4ED -> 2AE5CF. The copy and destroy
// loops both advance 0xD8. Forward both helpers to the rowed
// __uninitialized_copy<Rva002E2BBARecord*> and _Destroy<Rva002E2690Element*>
// bodies (declared only) without naming the game record. The tag is a plain
// local: a value-initialized __false_type() would add a store retail lacks.
struct Rva002E2BBARecord;
struct Rva002E2690Element;
namespace _STL {
template <> Rva002E2BBARecord *__uninitialized_copy<Rva002E2BBARecord *, Rva002E2BBARecord *>(
    Rva002E2BBARecord *, Rva002E2BBARecord *, Rva002E2BBARecord *, const __false_type &);
template <> void _Destroy<Rva002E2690Element *>(Rva002E2690Element *, Rva002E2690Element *);
template <> __declspec(dllimport) __forceinline Rva002E26E1Record *__uninitialized_copy<Rva002E26E1Record *, Rva002E26E1Record *>(
    Rva002E26E1Record *__first, Rva002E26E1Record *__last, Rva002E26E1Record *__result, const __false_type &)
{
    __false_type __tag;
    return reinterpret_cast<Rva002E26E1Record *>(__uninitialized_copy(
        reinterpret_cast<Rva002E2BBARecord *>(__first), reinterpret_cast<Rva002E2BBARecord *>(__last),
        reinterpret_cast<Rva002E2BBARecord *>(__result), __tag));
}
template <> __declspec(dllimport) __forceinline void _Destroy<Rva002E26E1Record *>(Rva002E26E1Record *__first, Rva002E26E1Record *__last)
{
    _Destroy(reinterpret_cast<Rva002E2690Element *>(__first), reinterpret_cast<Rva002E2690Element *>(__last));
}
}

template void _STL::vector<Rva002E26E1Record>::reserve(unsigned int);
