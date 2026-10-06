// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0002CD53Element { char bytes[9];Rva0002CD53Element();Rva0002CD53Element(const Rva0002CD53Element&);~Rva0002CD53Element();Rva0002CD53Element&operator=(const Rva0002CD53Element&); bool operator<(const Rva0002CD53Element&)const; bool operator==(const Rva0002CD53Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0002CD53Element, _STL::allocator<Rva0002CD53Element> >::_M_clear(void);
