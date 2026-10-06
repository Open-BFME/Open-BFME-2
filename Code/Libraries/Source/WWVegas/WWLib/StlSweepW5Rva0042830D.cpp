// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0042830DElement {Rva0042830DElement();Rva0042830DElement(const Rva0042830DElement&);Rva0042830DElement&operator=(const Rva0042830DElement&);~Rva0042830DElement(){}char bytes[24]; bool operator==(const Rva0042830DElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0042830DElement * _STL::__copy<Rva0042830DElement *, Rva0042830DElement *, int>(Rva0042830DElement *, Rva0042830DElement *, Rva0042830DElement *, _STL::random_access_iterator_tag const &, int *);
