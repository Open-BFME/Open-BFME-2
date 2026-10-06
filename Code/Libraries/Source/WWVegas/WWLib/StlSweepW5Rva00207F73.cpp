// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00207F73Element { char bytes[9];Rva00207F73Element();Rva00207F73Element(const Rva00207F73Element&);~Rva00207F73Element();Rva00207F73Element&operator=(const Rva00207F73Element&); bool operator<(const Rva00207F73Element&)const; bool operator==(const Rva00207F73Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00207F73Element, _STL::allocator<Rva00207F73Element> >::_M_clear(void);
