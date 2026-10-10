// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

struct Rva00598E66Element { char bytes[1]; bool operator<(const Rva00598E66Element&)const; bool operator==(const Rva00598E66Element&)const; };
namespace _STL {template<> struct hash<Rva00598E66Element> { unsigned operator()(const Rva00598E66Element&) const; };}
template class _STL::hash_map<int,Rva00598E66Element>;
