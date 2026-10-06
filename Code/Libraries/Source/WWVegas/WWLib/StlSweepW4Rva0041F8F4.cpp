// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0041F8F4Element { char bytes[1]; bool operator<(const Rva0041F8F4Element&)const; bool operator==(const Rva0041F8F4Element&)const; };
namespace _STL {template<> struct hash<Rva0041F8F4Element> { unsigned operator()(const Rva0041F8F4Element&) const; };}
template class _STL::hash_map<int,Rva0041F8F4Element>;
