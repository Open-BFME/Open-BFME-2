// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00312C77Element { char bytes[9];Rva00312C77Element();Rva00312C77Element(const Rva00312C77Element&);~Rva00312C77Element();Rva00312C77Element&operator=(const Rva00312C77Element&); bool operator<(const Rva00312C77Element&)const; bool operator==(const Rva00312C77Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00312C77Element, _STL::allocator<Rva00312C77Element> >::_M_clear(void);
