// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00332EF3Element { char bytes[156]; bool operator<(const Rva00332EF3Element&)const; bool operator==(const Rva00332EF3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00332EF3Element * _STL::__copy<Rva00332EF3Element *, Rva00332EF3Element *, int>(Rva00332EF3Element *, Rva00332EF3Element *, Rva00332EF3Element *, _STL::random_access_iterator_tag const &, int *);
