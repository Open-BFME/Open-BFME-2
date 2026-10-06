// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003B01C3Element { char bytes[4]; bool operator<(const Rva003B01C3Element&)const; bool operator==(const Rva003B01C3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__pop_heap<Rva003B01C3Element *, Rva003B01C3Element, _STL::less<Rva003B01C3Element>, int>(Rva003B01C3Element *, Rva003B01C3Element *, Rva003B01C3Element *, Rva003B01C3Element, _STL::less<Rva003B01C3Element>, int *);
