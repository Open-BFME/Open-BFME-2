// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002BC47DElement { Rva002BC47DElement();Rva002BC47DElement(const Rva002BC47DElement&);~Rva002BC47DElement();Rva002BC47DElement&operator=(const Rva002BC47DElement&);char bytes[52]; bool operator<(const Rva002BC47DElement&)const; bool operator==(const Rva002BC47DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002BC47DElement, _STL::allocator<Rva002BC47DElement> >::_M_fill_insert(Rva002BC47DElement *, unsigned int, Rva002BC47DElement const &);
