// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport46

#include <deque>

// Use the complete native map-growth provider recovered with the asset worker.
// The generic vendor version uses a different allocation path in retail.
namespace _STL {
template <> void deque<int>::_M_reallocate_map(unsigned int, bool);
template <> void deque<int>::_M_push_back_aux_v(const int &);
template <> void deque<int>::_M_push_front_aux_v(const int &);
// Retail has one copy of the map initializer (rowed in stlport_deque_sighting_initmap.cpp).
template <> void _Deque_base<int, allocator<int> >::_M_initialize_map(size_t);
// Retail uses the shared four-byte allocator at 0x00068E15.
template <> int *allocator<int>::allocate(size_t, const void *);
// Retail has no copy of allocator<int>::deallocate (every use is inline). This /O2
// unit's 18B copy is first in link order and differs from the /O1 units' 20B one.
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int *__p, size_t) { if (__p != 0) ::free((void *)__p); }
}

template class _STL::deque<int, _STL::allocator<int> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeAllocQG@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocQB@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocPV@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
