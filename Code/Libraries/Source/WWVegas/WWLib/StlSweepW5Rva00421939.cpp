// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00421939Element { char bytes[16]; bool operator<(const Rva00421939Element&)const; bool operator==(const Rva00421939Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00421939Element * _STL::__uninitialized_fill_n<Rva00421939Element *, unsigned int, Rva00421939Element>(Rva00421939Element *, unsigned int, Rva00421939Element const &, _STL::__false_type const &);
