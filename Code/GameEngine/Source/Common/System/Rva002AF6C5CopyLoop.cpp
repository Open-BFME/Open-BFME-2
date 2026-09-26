// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Random-access __copy loop over the 0x24-byte element copied at retail
// 0x002AF6C5 (50 bytes; count via idiv 0x24, per-element copy through the
// pinned operator= at 0x002AF505). The rowed 0x002B0B71 forwarder reaches
// this body. The element is modelled as an opaque 0x24-byte struct: its
// retail operator= (AsciiString at +0, vector members at +8/+0x14) does not
// match the sibling GeometryShape layout, so no application type is claimed.
#include <algorithm>

struct Rva002AF6C5Element
{
	~Rva002AF6C5Element();
	Rva002AF6C5Element &operator=(const Rva002AF6C5Element &other);

	unsigned char m_pad[0x24];
};

template Rva002AF6C5Element *_STL::__copy<Rva002AF6C5Element *,
	Rva002AF6C5Element *, int>(Rva002AF6C5Element *, Rva002AF6C5Element *,
	Rva002AF6C5Element *, const _STL::random_access_iterator_tag &, int *);
