// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0051FC54Element {Rva0051FC54Element();Rva0051FC54Element(const Rva0051FC54Element&);Rva0051FC54Element&operator=(const Rva0051FC54Element&);~Rva0051FC54Element(){}char bytes[80]; bool operator==(const Rva0051FC54Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0051FC54Element * _STL::__copy<Rva0051FC54Element *, Rva0051FC54Element *, int>(Rva0051FC54Element *, Rva0051FC54Element *, Rva0051FC54Element *, _STL::random_access_iterator_tag const &, int *);
