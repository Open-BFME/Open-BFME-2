// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE485Element { char bytes[9];Rva005FE485Element();Rva005FE485Element(const Rva005FE485Element&);~Rva005FE485Element();Rva005FE485Element&operator=(const Rva005FE485Element&); bool operator<(const Rva005FE485Element&)const; bool operator==(const Rva005FE485Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva005FE485Element, _STL::allocator<Rva005FE485Element> >::_M_clear(void);
