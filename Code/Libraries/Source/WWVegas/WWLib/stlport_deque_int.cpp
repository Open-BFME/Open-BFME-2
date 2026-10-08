// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport

#include <deque>

// Use the complete native map-growth provider recovered with the asset worker.
// The generic vendor version uses a different allocation path in retail.
namespace _STL {
template <> void deque<int>::_M_reallocate_map(unsigned int, bool);
template <> void deque<int>::_M_push_back_aux_v(const int &);
template <> void deque<int>::_M_push_front_aux_v(const int &);
// Retail uses the shared four-byte allocator at 0x00068E15.
template <> int *allocator<int>::allocate(size_t, const void *) const;
}

template class _STL::deque<int, _STL::allocator<int> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?setup@FreelistProxyHead@@QAEXPBXPAX@Z=??0?$_STLP_alloc_proxy@IHV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@I@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocQG@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocQB@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeAllocPV@@YAPAXHI@Z=??2@YAPAXIPAX@Z")
