// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva002D044BElement { char bytes[9];Rva002D044BElement();Rva002D044BElement(const Rva002D044BElement&);~Rva002D044BElement();Rva002D044BElement&operator=(const Rva002D044BElement&); bool operator<(const Rva002D044BElement&)const; bool operator==(const Rva002D044BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002D044BElement, _STL::allocator<Rva002D044BElement> >::_M_clear(void);
