// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva00501776 { Rva00501776();Rva00501776(const Rva00501776&);~Rva00501776();Rva00501776&operator=(const Rva00501776&);char bytes[1]; bool operator<(const Rva00501776&)const; bool operator==(const Rva00501776&)const; };
namespace _STL {template<> struct hash<Rva00501776> { unsigned operator()(const Rva00501776&) const; };}
template class _STL::hash_map<int,Rva00501776>;
