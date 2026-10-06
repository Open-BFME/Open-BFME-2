// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F53DAElement { Rva003F53DAElement();Rva003F53DAElement(const Rva003F53DAElement&);~Rva003F53DAElement();Rva003F53DAElement&operator=(const Rva003F53DAElement&);char bytes[104]; bool operator<(const Rva003F53DAElement&)const; bool operator==(const Rva003F53DAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> >::_M_fill_insert(Rva003F53DAElement *, unsigned int, Rva003F53DAElement const &);
