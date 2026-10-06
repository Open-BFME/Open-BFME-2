// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <list>

struct Rva00392076Element { _STL::deque<char> values[1]; bool operator<(const Rva00392076Element&) const; bool operator==(const Rva00392076Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva00392076Element, _STL::allocator<Rva00392076Element> >::push_front(Rva00392076Element const &);
