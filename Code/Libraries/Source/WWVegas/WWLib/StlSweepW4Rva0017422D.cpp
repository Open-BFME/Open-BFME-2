// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0017422DElement { Rva0017422DElement();Rva0017422DElement(const Rva0017422DElement&);~Rva0017422DElement();Rva0017422DElement&operator=(const Rva0017422DElement&);char bytes[32]; bool operator<(const Rva0017422DElement&)const; bool operator==(const Rva0017422DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0017422DElement, _STL::allocator<Rva0017422DElement> >::_M_fill_insert(Rva0017422DElement *, unsigned int, Rva0017422DElement const &);
