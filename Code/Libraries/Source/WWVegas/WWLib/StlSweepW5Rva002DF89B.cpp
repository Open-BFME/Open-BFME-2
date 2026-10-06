// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002DF89BElement { char bytes[12]; bool operator<(const Rva002DF89BElement&)const; bool operator==(const Rva002DF89BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002DF89BElement, _STL::allocator<Rva002DF89BElement> >::push_back(Rva002DF89BElement const &);
