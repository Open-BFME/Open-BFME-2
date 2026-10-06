// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <list>

struct Rva0005548FElement { _STL::deque<char> values[1]; bool operator<(const Rva0005548FElement&) const; bool operator==(const Rva0005548FElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0005548FElement, _STL::allocator<Rva0005548FElement> >::push_back(Rva0005548FElement const &);
