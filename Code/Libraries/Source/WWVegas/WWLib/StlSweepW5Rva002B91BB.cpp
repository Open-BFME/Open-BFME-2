// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002B91BBElement {Rva002B91BBElement();Rva002B91BBElement(const Rva002B91BBElement&);Rva002B91BBElement&operator=(const Rva002B91BBElement&);~Rva002B91BBElement(){}char bytes[52]; bool operator==(const Rva002B91BBElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva002B91BBElement * _STL::__copy<Rva002B91BBElement *, Rva002B91BBElement *, int>(Rva002B91BBElement *, Rva002B91BBElement *, Rva002B91BBElement *, _STL::random_access_iterator_tag const &, int *);
