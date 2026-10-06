// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva00501A5FElement { Rva00501A5FElement();Rva00501A5FElement(const Rva00501A5FElement&);~Rva00501A5FElement();Rva00501A5FElement&operator=(const Rva00501A5FElement&);char bytes[1]; bool operator<(const Rva00501A5FElement&)const; bool operator==(const Rva00501A5FElement&)const; };
namespace _STL {template<> struct hash<Rva00501A5FElement> { unsigned operator()(const Rva00501A5FElement&) const; };}
template class _STL::hash_map<int,Rva00501A5FElement>;
