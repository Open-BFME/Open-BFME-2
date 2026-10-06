// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00254D65Element {Rva00254D65Element();Rva00254D65Element(const Rva00254D65Element&);Rva00254D65Element&operator=(const Rva00254D65Element&);~Rva00254D65Element(){}char bytes[8]; bool operator==(const Rva00254D65Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00254D65Element * _STL::__copy<Rva00254D65Element *, Rva00254D65Element *, int>(Rva00254D65Element *, Rva00254D65Element *, Rva00254D65Element *, _STL::random_access_iterator_tag const &, int *);
