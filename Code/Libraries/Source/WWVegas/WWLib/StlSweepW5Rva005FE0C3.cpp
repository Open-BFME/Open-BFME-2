// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE0C3Element {Rva005FE0C3Element();Rva005FE0C3Element(const Rva005FE0C3Element&);Rva005FE0C3Element&operator=(const Rva005FE0C3Element&);~Rva005FE0C3Element(){}char bytes[12]; bool operator==(const Rva005FE0C3Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE0C3Element * _STL::__copy<Rva005FE0C3Element *, Rva005FE0C3Element *, int>(Rva005FE0C3Element *, Rva005FE0C3Element *, Rva005FE0C3Element *, _STL::random_access_iterator_tag const &, int *);
