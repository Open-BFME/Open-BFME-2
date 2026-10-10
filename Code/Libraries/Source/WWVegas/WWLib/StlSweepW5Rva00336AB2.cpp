// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

struct Rva00336AB2Element {Rva00336AB2Element();Rva00336AB2Element(const Rva00336AB2Element&);Rva00336AB2Element&operator=(const Rva00336AB2Element&);~Rva00336AB2Element(){}char bytes[156]; bool operator==(const Rva00336AB2Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00336AB2Element, _STL::allocator<Rva00336AB2Element> >::push_back(Rva00336AB2Element const &);
