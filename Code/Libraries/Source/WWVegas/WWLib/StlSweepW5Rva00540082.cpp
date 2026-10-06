// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00540082Element {Rva00540082Element();Rva00540082Element(const Rva00540082Element&);Rva00540082Element&operator=(const Rva00540082Element&);~Rva00540082Element(){}char bytes[40]; bool operator==(const Rva00540082Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00540082Element * _STL::__copy<Rva00540082Element *, Rva00540082Element *, int>(Rva00540082Element *, Rva00540082Element *, Rva00540082Element *, _STL::random_access_iterator_tag const &, int *);
