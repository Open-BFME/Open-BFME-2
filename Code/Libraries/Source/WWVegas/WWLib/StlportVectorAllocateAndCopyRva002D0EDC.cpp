// Target boundary 0x002D0EDC/45 is STLport vector::_M_allocate_and_copy.
// The caller at 0x002D0F65 supplies element count and source-range pointers;
// this helper allocates through the vector allocator and returns the copied
// buffer. Retail advances the source/destination by the witnessed 0x5C stride.
//
// Rva002D0EDCElement is an address-derived 92-byte non-trivial emitter view.
// Its target Construct chain reaches the matched GeometryInfo copy constructor
// at 0x000929E8, but no complete element layout is claimed by this TU.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002D0EDCElement {
	char opaque[92];
	Rva002D0EDCElement(const Rva002D0EDCElement &);
	~Rva002D0EDCElement();
};

template Rva002D0EDCElement *
_STL::vector<Rva002D0EDCElement>::_M_allocate_and_copy(
	unsigned int, const Rva002D0EDCElement *, const Rva002D0EDCElement *);
