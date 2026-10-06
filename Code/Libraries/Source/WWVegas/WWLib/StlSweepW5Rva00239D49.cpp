// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva00239D49Element { Rva00239D49Element();Rva00239D49Element(const Rva00239D49Element&);~Rva00239D49Element();Rva00239D49Element&operator=(const Rva00239D49Element&);char bytes[1]; bool operator<(const Rva00239D49Element&)const; bool operator==(const Rva00239D49Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_List_base<Rva00239D49Element, _STL::allocator<Rva00239D49Element> >::clear(void);
