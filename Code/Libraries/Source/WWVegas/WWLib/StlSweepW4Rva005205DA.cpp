// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005205DAElement { Rva005205DAElement();Rva005205DAElement(const Rva005205DAElement&);~Rva005205DAElement();Rva005205DAElement&operator=(const Rva005205DAElement&);char bytes[80]; bool operator<(const Rva005205DAElement&)const; bool operator==(const Rva005205DAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva005205DAElement, _STL::allocator<Rva005205DAElement> >::_M_fill_insert(Rva005205DAElement *, unsigned int, Rva005205DAElement const &);
