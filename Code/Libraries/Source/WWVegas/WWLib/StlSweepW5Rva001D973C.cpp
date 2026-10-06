// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva001D973CElement { char bytes[8]; bool operator<(const Rva001D973CElement&)const; bool operator==(const Rva001D973CElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva001D973CElement * _STL::__copy<Rva001D973CElement *, Rva001D973CElement *, int>(Rva001D973CElement *, Rva001D973CElement *, Rva001D973CElement *, _STL::random_access_iterator_tag const &, int *);
