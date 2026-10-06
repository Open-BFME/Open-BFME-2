// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva004157BBElement { Rva004157BBElement();Rva004157BBElement(const Rva004157BBElement&);~Rva004157BBElement();Rva004157BBElement&operator=(const Rva004157BBElement&);char bytes[1]; bool operator<(const Rva004157BBElement&)const; bool operator==(const Rva004157BBElement&)const; };
namespace _STL {template<> struct hash<Rva004157BBElement> { unsigned operator()(const Rva004157BBElement&) const; };}
template class _STL::hash_map<int,Rva004157BBElement>;
