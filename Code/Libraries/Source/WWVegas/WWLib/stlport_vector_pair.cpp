// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <vector>

// Preserve retail's inlined buffer release while using the canonical public allocator.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<pair<int, int> >::deallocate(pair<int, int> *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

template class _STL::vector<_STL::pair<int, int>, _STL::allocator<_STL::pair<int, int> > >;
