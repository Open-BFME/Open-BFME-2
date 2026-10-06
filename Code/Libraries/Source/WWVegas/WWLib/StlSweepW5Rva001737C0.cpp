// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001737C0Element {Rva001737C0Element();Rva001737C0Element(const Rva001737C0Element&);Rva001737C0Element&operator=(const Rva001737C0Element&);~Rva001737C0Element(){}char bytes[32]; bool operator==(const Rva001737C0Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva001737C0Element * _STL::__copy<Rva001737C0Element *, Rva001737C0Element *, int>(Rva001737C0Element *, Rva001737C0Element *, Rva001737C0Element *, _STL::random_access_iterator_tag const &, int *);
