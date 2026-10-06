// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva004F4DC0Element {Rva004F4DC0Element();Rva004F4DC0Element(const Rva004F4DC0Element&);Rva004F4DC0Element&operator=(const Rva004F4DC0Element&);~Rva004F4DC0Element(){}char bytes[12]; bool operator==(const Rva004F4DC0Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva004F4DC0Element * _STL::__copy<Rva004F4DC0Element *, Rva004F4DC0Element *, int>(Rva004F4DC0Element *, Rva004F4DC0Element *, Rva004F4DC0Element *, _STL::random_access_iterator_tag const &, int *);
