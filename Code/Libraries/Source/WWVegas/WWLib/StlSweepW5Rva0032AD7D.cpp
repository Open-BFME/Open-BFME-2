// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva0032AD7DElement { char bytes[8]; bool operator<(const Rva0032AD7DElement&)const; bool operator==(const Rva0032AD7DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0032AD7DElement * _STL::__uninitialized_copy<Rva0032AD7DElement const *, Rva0032AD7DElement *>(Rva0032AD7DElement const *, Rva0032AD7DElement const *, Rva0032AD7DElement *, _STL::__false_type const &);
