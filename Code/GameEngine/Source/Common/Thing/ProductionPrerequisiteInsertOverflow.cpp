// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// STLport vector<ProductionPrerequisite>::_M_insert_overflow (fill form),
// retail 0x0033E927, 183 bytes, called from push_back at 0x0033EA10.
// Same recipe as ProductionPrerequisiteVectorPushBack.cpp, plus /G7: without
// it MSVC homes `this` in esi (push edi sinks below the size computation);
// /G7 keeps the retail edi homing (push edi first, `this` in edi throughout).
// The tail calls _M_clear (retail 0x002D02DF, landed from this TU), which
// destroys the old range through the rowed _Destroy at 0x002CFBAE and frees
// it through 0x0030830. The allocator call resolves through the
// allocator<ProductionPrerequisite> pin at the shared 36-byte fold 0x005DFB2C.

#include <vector>

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	ProductionPrerequisite(const ProductionPrerequisite &other);
	~ProductionPrerequisite();
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);

private:
	void *m_unreconstructed[9];
};

typedef char ProductionPrerequisiteSizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

template void _STL::vector<ProductionPrerequisite>::_M_clear();

template void _STL::vector<ProductionPrerequisite>::_M_insert_overflow(
	ProductionPrerequisite *, const ProductionPrerequisite &, const _STL::__false_type &,
	unsigned int, bool);
