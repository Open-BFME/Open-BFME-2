// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva0033E0B7Element { char bytes[36]; bool operator<(const Rva0033E0B7Element&)const; bool operator==(const Rva0033E0B7Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0033E0B7Element * _STL::__uninitialized_copy<Rva0033E0B7Element const *, Rva0033E0B7Element *>(Rva0033E0B7Element const *, Rva0033E0B7Element const *, Rva0033E0B7Element *, _STL::__false_type const &);
