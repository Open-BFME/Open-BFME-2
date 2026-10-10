// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva000C225DElement { Rva000C225DElement();Rva000C225DElement(const Rva000C225DElement&);~Rva000C225DElement();Rva000C225DElement&operator=(const Rva000C225DElement&);char bytes[8]; bool operator<(const Rva000C225DElement&)const; bool operator==(const Rva000C225DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva000C225DElement, _STL::allocator<Rva000C225DElement> >::_M_fill_insert(Rva000C225DElement *, unsigned int, Rva000C225DElement const &);
