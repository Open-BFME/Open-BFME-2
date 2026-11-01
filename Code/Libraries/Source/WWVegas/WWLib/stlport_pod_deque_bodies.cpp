// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 deque members for placeholder POD elements, each
// placed by a single masked whole-.text hit whose own bytes carry the element
// stride or buffer size. BfmePodN stands for the real N-byte element; where
// retail's copy construct for it is non-trivial it is pinned by call-site
// address, not compiled here. Only bodies whose callees agree with the size
// are kept: deque bodies that resolve into the pointer-deque rows are
// size-independent and deliberately not claimed. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod16;
struct BfmeNarrowRecord0041A617;
namespace _STL {
template <> void _Construct<BfmeNarrowRecord0041A617, BfmeNarrowRecord0041A617>(BfmeNarrowRecord0041A617 *, const BfmeNarrowRecord0041A617 &);
// 0x0041A727
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod16, BfmePod16>(BfmePod16 *p, const BfmePod16 &v)
{ _Construct((BfmeNarrowRecord0041A617 *)p, (const BfmeNarrowRecord0041A617 &)v); }
}
// Suppress this TU's non-retail copy of ??$__destroy_aux@U?$_Deque_iterator@UBfmePod16@@U?$_Nonconst_traits@UBfmePod16@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod16;
namespace _STL { template <> void __destroy_aux<_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> > >(_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,_Deque_iterator<BfmePod16,_Nonconst_traits<BfmePod16> >,__false_type const &); }
struct BfmePod16 { int a[4]; };
struct BfmePod28 { int a[7]; };
struct BfmePod40 { int a[10]; };
struct BfmePod56 { int a[14]; };
struct BfmePod108 { int a[27]; };
// The 16-byte deque's slow path is the recovered narrow-record body at
// 0x0041A9E8. Bind the POD view to that owner rather than emitting a trivial
// copy of the element where retail copy-constructs its string.
struct Rva0041A9E8 {
    void rva0041A9E8(const BfmeNarrowRecord0041A617 &);
};
namespace _STL {
template <> __declspec(dllimport) __forceinline
void deque<BfmePod16>::_M_push_back_aux_v(const BfmePod16 &x)
{
    ((Rva0041A9E8 *)this)->rva0041A9E8((const BfmeNarrowRecord0041A617 &)x);
}
}
// Instantiate the recovered operations and their native callees only.
template void _STL::deque<BfmePod16>::push_back(const BfmePod16 &);
template void _STL::_Deque_iterator_base<BfmePod28>::_M_increment();
template void _STL::_Deque_iterator_base<BfmePod40>::_M_increment();
template void _STL::_Deque_iterator_base<BfmePod40>::_M_decrement();
template BfmePod108 *_STL::allocator<BfmePod108>::allocate(unsigned int, const void *) const;
template BfmePod56 *_STL::allocator<BfmePod56>::allocate(unsigned int, const void *) const;
template void _STL::deque<BfmePod28>::_M_reserve_map_at_back(unsigned int);
