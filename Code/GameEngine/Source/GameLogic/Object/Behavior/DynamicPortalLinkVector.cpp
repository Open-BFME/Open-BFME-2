// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x4613EB destroys 12B Link elements through the clearer at
// 0x003F29F8 (stride 0xC, per-element destruction through 0x0007FAB3),
// then frees the vector storage. Target 0x003F29F8 is the element
// clearer loop; target 0x0007FAB3 is the element dtor itself (null-checked
// free of the owned pointer at +0). Link elements are therefore 12B owner
// records; interiors are positional (the dtor proves +0 is an owned
// pointer, the rest is unproven). StlportAsciiStringVectorDtor precedent
// (explicit instantiation emits the foldable family).
#include <vector>

extern "C" void _free(void *ptr);

struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink();
};

DynamicPortalLink::~DynamicPortalLink()
{
	if (m_owned != 0)
		_free(m_owned);
}

template _STL::vector<DynamicPortalLink>::~vector();
