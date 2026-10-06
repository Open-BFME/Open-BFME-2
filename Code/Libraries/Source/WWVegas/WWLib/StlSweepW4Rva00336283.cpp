// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva00336283Element { char bytes[1]; bool operator<(const Rva00336283Element&)const; bool operator==(const Rva00336283Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00336283Element * _STL::lower_bound<Rva00336283Element *, Rva00336283Element, _STL::less<Rva00336283Element> >(Rva00336283Element *, Rva00336283Element *, Rva00336283Element const &, _STL::less<Rva00336283Element>);
