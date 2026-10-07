// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>
#include <utility>

struct Rva00053D4FElement { unsigned char words[1];bool operator<(const Rva00053D4FElement&)const;bool operator==(const Rva00053D4FElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva00053D4FElement, _STL::allocator<Rva00053D4FElement> >::pop_back(void);
