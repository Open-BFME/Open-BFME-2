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
#include <hash_map>

struct Rva0041553AElement {Rva0041553AElement();Rva0041553AElement(const Rva0041553AElement&);Rva0041553AElement&operator=(const Rva0041553AElement&);~Rva0041553AElement(){}char bytes[8]; bool operator==(const Rva0041553AElement&)const;};
template class _STL::hash_map<int,Rva0041553AElement>;
