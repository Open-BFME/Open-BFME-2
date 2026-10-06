// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

struct Rva00423BD8Element { int word0; bool operator<(const Rva00423BD8Element&)const; bool operator==(const Rva00423BD8Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::deque<Rva00423BD8Element, _STL::allocator<Rva00423BD8Element> >::push_back(Rva00423BD8Element const &);
