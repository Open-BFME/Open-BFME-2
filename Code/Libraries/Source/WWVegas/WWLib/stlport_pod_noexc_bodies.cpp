// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector/deque members for placeholder POD elements
// in the _STLP_NO_EXCEPTIONS configuration (no try/catch around the
// reallocation paths), each placed by a single masked whole-.text hit whose
// own bytes carry the element size. BfmePodN stands for the real N-byte
// element; a non-trivial copy construct is pinned by call-site address, not
// compiled here. No retail caller is claimed.
#include <vector>
#include <deque>
struct BfmePod8 { int a[2]; };
struct BfmePod16 { int a[4]; };
struct BfmePod20 { int a[5]; };
struct BfmePod28 { int a[7]; };
struct BfmePod32 { int a[8]; };
struct BfmePod40 { int a[10]; };
struct BfmePod44 { int a[11]; };
struct BfmePod52 { int a[13]; };
struct BfmePod68 { int a[17]; };
struct BfmePod76 { int a[19]; };
struct BfmePod492 { int a[123]; };
struct BfmePod840 { int a[210]; };
struct BfmePod24 { int a[6]; };
// 696 = 0x2B8 is BuddyRequest, as in stlport_pod_large_bodies.cpp.
class BuddyRequest
{
	char m_bfmeBody[0x2B8];
};
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::vector<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod52, _STL::allocator<BfmePod52 > >;
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod76, _STL::allocator<BfmePod76 > >;
template class _STL::deque<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::deque<BfmePod16, _STL::allocator<BfmePod16 > >;
template class _STL::deque<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::deque<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::deque<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::deque<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::deque<BfmePod840, _STL::allocator<BfmePod840 > >;
