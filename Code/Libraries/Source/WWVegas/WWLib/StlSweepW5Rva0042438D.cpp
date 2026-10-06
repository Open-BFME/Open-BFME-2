// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva0042438DElement { Rva0042438DElement();Rva0042438DElement(const Rva0042438DElement&);~Rva0042438DElement();Rva0042438DElement&operator=(const Rva0042438DElement&);char bytes[1]; bool operator<(const Rva0042438DElement&)const; bool operator==(const Rva0042438DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_List_base<Rva0042438DElement, _STL::allocator<Rva0042438DElement> >::clear(void);
