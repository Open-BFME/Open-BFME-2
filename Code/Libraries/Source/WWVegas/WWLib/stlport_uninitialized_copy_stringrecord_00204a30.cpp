// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_copy for 20-byte BfmeStringRecord00204A30 (38B),
// same-shape sibling of the rowed copy at 0x000BBAA1. Walks the source range
// constructing each element out-of-line through the rowed _Construct at
// 0x002056DC, striding 0x14. Minimal struct at retail stride with the
// struct-ness of the rowed copy ctor; no member is touched.
// Evidence: unlock lane unblocks 0x00209952, callers 0x00209993 0x002099DE.

#include <memory>
#include <vector>

struct BfmeStringRecord00204A30
{
public:
	BfmeStringRecord00204A30();
	BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &other);
	char m_body[0x14];
};

namespace _STL {
template<> void _Construct<BfmeStringRecord00204A30, BfmeStringRecord00204A30>(BfmeStringRecord00204A30 *, const BfmeStringRecord00204A30 &);
}

template _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::vector(const _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> > &);
