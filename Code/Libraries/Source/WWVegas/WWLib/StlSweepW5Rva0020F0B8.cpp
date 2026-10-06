// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0020F0B8Element { char bytes[1]; Rva0020F0B8Element();Rva0020F0B8Element(const Rva0020F0B8Element&);~Rva0020F0B8Element();Rva0020F0B8Element&operator=(const Rva0020F0B8Element&); struct Hash { unsigned state[1]; unsigned operator()(const Rva0020F0B8Element&) const; }; struct Equal { unsigned state[1]; bool operator()(const Rva0020F0B8Element&,const Rva0020F0B8Element&)const; }; struct Compare {unsigned state[1]; bool operator()(const Rva0020F0B8Element&,const Rva0020F0B8Element&)const; }; bool operator==(const Rva0020F0B8Element&) const; };
template class _STL::hash_map<Rva0020F0B8Element,int,Rva0020F0B8Element::Hash,Rva0020F0B8Element::Equal>;
