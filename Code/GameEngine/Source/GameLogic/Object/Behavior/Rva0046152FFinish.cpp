// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector<DynamicPortalLink>::_M_insert_overflow, false_type
// growth path (12-byte Patch-owned portal Link records). Emitted by explicit
// instantiation of the real vendor template; retail 0x0046152F is exactly this
// body, the _M_insert_overflow reachable from the DynamicPortalBehaviour list.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class DynamicPortalLink
{
public:
	DynamicPortalLink();
	DynamicPortalLink(const DynamicPortalLink &other);
	DynamicPortalLink &operator=(const DynamicPortalLink &other);
	~DynamicPortalLink();
	void *m_owned;
	int m_second;
	int m_third;
};

template class _STL::vector<DynamicPortalLink, _STL::allocator<DynamicPortalLink> >;
