// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, in the
// _STLP_USE_MALLOC allocator configuration. Each body was placed by a single
// masked whole-.text hit and its own bytes carry the element stride.
// BfmePodN stands for the real N-byte element at each site; where retail's
// copy construct for it is non-trivial, _Construct<BfmePodN> is pinned by
// call-site address, not compiled here. No retail caller is claimed. The
// 8/12/16-byte callees resolve to the existing BfmeE8/E12/E16 rows, the same
// placeholder sizes under their older names.
#include <vector>
struct BfmePod8 { int a[2]; };
struct BfmePod12 { int a[3]; };
struct BfmePod16 { int a[4]; };
struct BfmePod40 { int a[10]; };
struct BfmePod44 { int a[11]; };
struct BfmePod60 { int a[15]; };
struct BfmePod68 { int a[17]; };
struct BfmePod260 { int a[65]; };
template class _STL::vector<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::vector<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::vector<BfmePod16, _STL::allocator<BfmePod16 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod60, _STL::allocator<BfmePod60 > >;
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod260, _STL::allocator<BfmePod260 > >;
