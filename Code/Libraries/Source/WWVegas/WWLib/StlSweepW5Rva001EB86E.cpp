// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001EB86EElement { char bytes[172];Rva001EB86EElement();Rva001EB86EElement(const Rva001EB86EElement&);~Rva001EB86EElement();Rva001EB86EElement&operator=(const Rva001EB86EElement&); bool operator<(const Rva001EB86EElement&)const; bool operator==(const Rva001EB86EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva001EB86EElement * _STL::__copy<Rva001EB86EElement *, Rva001EB86EElement *, int>(Rva001EB86EElement *, Rva001EB86EElement *, Rva001EB86EElement *, _STL::random_access_iterator_tag const &, int *);
