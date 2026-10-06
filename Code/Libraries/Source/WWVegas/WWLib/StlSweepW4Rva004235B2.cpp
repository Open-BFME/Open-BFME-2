// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva004235B2Element { char bytes[1]; bool operator<(const Rva004235B2Element&)const; bool operator==(const Rva004235B2Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva004235B2Element * _STL::lower_bound<Rva004235B2Element *, Rva004235B2Element, _STL::less<Rva004235B2Element> >(Rva004235B2Element *, Rva004235B2Element *, Rva004235B2Element const &, _STL::less<Rva004235B2Element>);
