// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva000ADE67Element { char bytes[16]; bool operator<(const Rva000ADE67Element&)const; bool operator==(const Rva000ADE67Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000ADE67Element * _STL::__uninitialized_copy<Rva000ADE67Element const *, Rva000ADE67Element *>(Rva000ADE67Element const *, Rva000ADE67Element const *, Rva000ADE67Element *, _STL::__false_type const &);
