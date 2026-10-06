// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva005EA9E1Element { char bytes[36]; bool operator<(const Rva005EA9E1Element&)const; bool operator==(const Rva005EA9E1Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva005EA9E1Element * _STL::__uninitialized_fill_n<Rva005EA9E1Element *, unsigned int, Rva005EA9E1Element>(Rva005EA9E1Element *, unsigned int, Rva005EA9E1Element const &, _STL::__false_type const &);
