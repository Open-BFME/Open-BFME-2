// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00539A2EElement {Rva00539A2EElement();Rva00539A2EElement(const Rva00539A2EElement&);Rva00539A2EElement&operator=(const Rva00539A2EElement&);~Rva00539A2EElement(){}char bytes[8]; bool operator==(const Rva00539A2EElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00539A2EElement, _STL::allocator<Rva00539A2EElement> >::push_back(Rva00539A2EElement const &);
