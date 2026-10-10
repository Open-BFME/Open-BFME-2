// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>
#include <vector>






struct Rva00058BBDElement { _STL::list<short> values[1]; bool operator==(const Rva00058BBDElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00058BBDElement, _STL::allocator<Rva00058BBDElement> >::_M_insert_overflow(Rva00058BBDElement *, Rva00058BBDElement const &, _STL::__false_type const &, unsigned int, bool);
