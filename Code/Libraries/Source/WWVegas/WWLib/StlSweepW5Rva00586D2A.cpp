// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00586D2AElement { Rva00586D2AElement();Rva00586D2AElement(const Rva00586D2AElement&);~Rva00586D2AElement();Rva00586D2AElement&operator=(const Rva00586D2AElement&);char bytes[84]; bool operator<(const Rva00586D2AElement&)const; bool operator==(const Rva00586D2AElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00586D2AElement * _STL::__copy<Rva00586D2AElement *, Rva00586D2AElement *, int>(Rva00586D2AElement *, Rva00586D2AElement *, Rva00586D2AElement *, _STL::random_access_iterator_tag const &, int *);
