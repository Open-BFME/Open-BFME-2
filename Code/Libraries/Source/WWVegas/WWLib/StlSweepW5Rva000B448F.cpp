// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva000B448FElement { char bytes[24]; bool operator<(const Rva000B448FElement&)const; bool operator==(const Rva000B448FElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000B448FElement * _STL::__copy<Rva000B448FElement *, Rva000B448FElement *, int>(Rva000B448FElement *, Rva000B448FElement *, Rva000B448FElement *, _STL::random_access_iterator_tag const &, int *);
