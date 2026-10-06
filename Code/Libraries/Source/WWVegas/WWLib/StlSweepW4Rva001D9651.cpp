// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva001D9651Element { char bytes[1]; bool operator<(const Rva001D9651Element&)const; bool operator==(const Rva001D9651Element&)const; };
namespace _STL {template<> struct hash<Rva001D9651Element> { unsigned operator()(const Rva001D9651Element&) const; };}
template class _STL::hash_map<int,Rva001D9651Element>;
