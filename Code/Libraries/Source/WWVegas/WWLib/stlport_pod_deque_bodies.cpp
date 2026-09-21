// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 deque members for placeholder POD elements, each
// placed by a single masked whole-.text hit whose own bytes carry the element
// stride or buffer size. BfmePodN stands for the real N-byte element; where
// retail's copy construct for it is non-trivial it is pinned by call-site
// address, not compiled here. Only bodies whose callees agree with the size
// are kept: deque bodies that resolve into the pointer-deque rows are
// size-independent and deliberately not claimed. No retail caller is claimed.
#include <deque>
struct BfmePod16 { int a[4]; };
struct BfmePod20 { int a[5]; };
struct BfmePod28 { int a[7]; };
struct BfmePod40 { int a[10]; };
struct BfmePod56 { int a[14]; };
struct BfmePod108 { int a[27]; };
template class _STL::deque<BfmePod16, _STL::allocator<BfmePod16 > >;
template class _STL::deque<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::deque<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::deque<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::deque<BfmePod56, _STL::allocator<BfmePod56 > >;
template class _STL::deque<BfmePod108, _STL::allocator<BfmePod108 > >;
