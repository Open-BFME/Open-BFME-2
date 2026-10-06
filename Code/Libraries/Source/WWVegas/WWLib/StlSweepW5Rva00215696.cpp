// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00215696Element {Rva00215696Element();Rva00215696Element(const Rva00215696Element&);Rva00215696Element&operator=(const Rva00215696Element&);~Rva00215696Element(){}char bytes[16]; bool operator==(const Rva00215696Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00215696Element * _STL::__copy<Rva00215696Element *, Rva00215696Element *, int>(Rva00215696Element *, Rva00215696Element *, Rva00215696Element *, _STL::random_access_iterator_tag const &, int *);
