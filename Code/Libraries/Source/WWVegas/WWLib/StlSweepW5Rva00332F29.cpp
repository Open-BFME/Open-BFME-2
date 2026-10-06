// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00332F29Element { char bytes[36]; bool operator<(const Rva00332F29Element&)const; bool operator==(const Rva00332F29Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00332F29Element * _STL::__copy<Rva00332F29Element *, Rva00332F29Element *, int>(Rva00332F29Element *, Rva00332F29Element *, Rva00332F29Element *, _STL::random_access_iterator_tag const &, int *);
