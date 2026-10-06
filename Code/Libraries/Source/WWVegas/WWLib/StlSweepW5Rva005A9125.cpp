// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva005A9125Element { char bytes[8]; bool operator<(const Rva005A9125Element&)const; bool operator==(const Rva005A9125Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::swap<Rva005A9125Element>(Rva005A9125Element &, Rva005A9125Element &);
