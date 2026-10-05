// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_fill_n<Rva002BAE2AElement*> (37 bytes) @0x002BB785:
// stride-12 masked twin of the rowed fill_n at 0x005F949D
// (stlport_uninitialized_fill_n12.cpp). The body null-guards the count and
// constructs each element through the rowed EH _Construct at 0x002BAE2A
// (StlportConstructFamilyW3G15.cpp), declared-only here. The element is the
// same address-named placeholder; only its 12-byte stride is claimed.

#include <memory>
#include <vector>

struct Rva002BAE2AElement
{
	Rva002BAE2AElement(const Rva002BAE2AElement &that);
	unsigned int m_body[3];
};

namespace _STL {
template<> void _Construct<Rva002BAE2AElement, Rva002BAE2AElement>(Rva002BAE2AElement *, const Rva002BAE2AElement &);
}

template _STL::vector<Rva002BAE2AElement, _STL::allocator<Rva002BAE2AElement> >::vector(unsigned int, const Rva002BAE2AElement &, const _STL::allocator<Rva002BAE2AElement> &);
