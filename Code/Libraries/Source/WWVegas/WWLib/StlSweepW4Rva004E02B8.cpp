// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva004E02B8Element { char bytes[1]; bool operator<(const Rva004E02B8Element&)const; bool operator==(const Rva004E02B8Element&)const; };
namespace _STL {template<> struct hash<Rva004E02B8Element> { unsigned operator()(const Rva004E02B8Element&) const; };}
template class _STL::hash_map<int,Rva004E02B8Element>;
// AIStatCollector::Register increments the mapped four-byte count at node+8;
// its constructor's empty count-map call uses this same retail body. Keep
// the original opaque owner while proving the actual int-count instantiation
// against its whole body and all callee relocations through pin_admission.
template _STL::hash_map<int,int>::hash_map();
