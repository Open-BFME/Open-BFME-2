// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva004DFCB0Element { char bytes[4]; bool operator<(const Rva004DFCB0Element&)const; bool operator==(const Rva004DFCB0Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva004DFCB0Element, _STL::allocator<Rva004DFCB0Element> >::push_back(Rva004DFCB0Element const &);
