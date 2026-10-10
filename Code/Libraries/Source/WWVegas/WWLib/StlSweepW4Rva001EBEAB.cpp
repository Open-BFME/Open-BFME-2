// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

struct Rva001EBEABElement { char bytes[172];Rva001EBEABElement();Rva001EBEABElement(const Rva001EBEABElement&);~Rva001EBEABElement();Rva001EBEABElement&operator=(const Rva001EBEABElement&); bool operator<(const Rva001EBEABElement&)const; bool operator==(const Rva001EBEABElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001EBEABElement, _STL::allocator<Rva001EBEABElement> >::_M_fill_insert(Rva001EBEABElement *, unsigned int, Rva001EBEABElement const &);
