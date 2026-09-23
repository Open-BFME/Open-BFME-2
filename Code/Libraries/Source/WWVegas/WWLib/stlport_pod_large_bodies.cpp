// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector/deque members for large placeholder POD
// elements (132..900 bytes), each placed by a single masked whole-.text hit
// whose own bytes carry the element size (allocate multiplies by it,
// push_back/__uninitialized_fill_n step by it). BfmePodN stands for the real
// N-byte element; no retail caller is claimed and no container kind is
// asserted for the allocate rows.
#include <vector>
#include <deque>
struct BfmePod132 { int a[33]; };
struct BfmePod156 { int a[39]; };
struct BfmePod184 { int a[46]; };
struct BfmePod204 { int a[51]; };
struct BfmePod272 { int a[68]; };
struct BfmePod276 { int a[69]; };
struct BfmePod476 { int a[119]; };
struct BfmePod480 { int a[120]; };
struct BfmePod492 { int a[123]; };
struct BfmePod544 { int a[136]; };
// 696 = 0x2B8 is BuddyRequest (see BuddyRequestDequePushBackAux.cpp): the
// placed deque's _Construct callee is the matched _Construct<BuddyRequest>
// at 0x00550798, so these rows carry the real element type.
class BuddyRequest
{
	char m_bfmeBody[0x2B8];
};
struct BfmePod840 { int a[210]; };
struct BfmePod872 { int a[218]; };
struct BfmePod900 { int a[225]; };
// Only allocation is established for this 132-byte element.
template class _STL::allocator<BfmePod132>;
template class _STL::allocator<BfmePod156>;
template class _STL::allocator<BfmePod184>;
template class _STL::deque<BfmePod204, _STL::allocator<BfmePod204 > >;
template class _STL::deque<BfmePod272, _STL::allocator<BfmePod272 > >;
template class _STL::deque<BfmePod276, _STL::allocator<BfmePod276 > >;
template class _STL::vector<BfmePod476, _STL::allocator<BfmePod476 > >;
template class _STL::vector<BfmePod480, _STL::allocator<BfmePod480 > >;
template class _STL::vector<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::vector<BfmePod544, _STL::allocator<BfmePod544 > >;
template class _STL::vector<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::vector<BfmePod840, _STL::allocator<BfmePod840 > >;
template class _STL::vector<BfmePod872, _STL::allocator<BfmePod872 > >;
template class _STL::vector<BfmePod900, _STL::allocator<BfmePod900 > >;
template class _STL::deque<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::deque<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::deque<BfmePod840, _STL::allocator<BfmePod840 > >;
