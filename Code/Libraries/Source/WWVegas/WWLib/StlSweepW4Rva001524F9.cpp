// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001524F9Element { Rva001524F9Element();Rva001524F9Element(const Rva001524F9Element&);~Rva001524F9Element();Rva001524F9Element&operator=(const Rva001524F9Element&);char bytes[36]; bool operator<(const Rva001524F9Element&)const; bool operator==(const Rva001524F9Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001524F9Element, _STL::allocator<Rva001524F9Element> >::_M_fill_insert(Rva001524F9Element *, unsigned int, Rva001524F9Element const &);
