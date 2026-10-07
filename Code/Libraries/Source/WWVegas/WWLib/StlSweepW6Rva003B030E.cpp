// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>
#include <utility>

struct Rva003B030EElement { unsigned char words[1];bool operator<(const Rva003B030EElement&)const;bool operator==(const Rva003B030EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::pop_heap<Rva003B030EElement *, _STL::less<Rva003B030EElement> >(Rva003B030EElement *, Rva003B030EElement *, _STL::less<Rva003B030EElement>);
