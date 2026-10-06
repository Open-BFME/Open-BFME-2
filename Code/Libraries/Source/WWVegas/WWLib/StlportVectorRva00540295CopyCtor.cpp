// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector copy constructor for a 40-byte codegen view. Target
// evidence: the 71-byte body at 0x00540295 ends with RET4 at 0x005402DC and
// its copy loop call resolves to the rowed 40-byte worker at 0x005400B4.
// The call distinguishes this body from the other 40-byte vector copy view;
// the element's C++ identity remains unresolved.
#include <vector>

struct Rva00540295Element { unsigned char bytes[40]; };

template class _STL::vector<Rva00540295Element, _STL::allocator<Rva00540295Element> >;
