// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0033A7DCElement { char bytes[1]; Rva0033A7DCElement();Rva0033A7DCElement(const Rva0033A7DCElement&);~Rva0033A7DCElement();Rva0033A7DCElement&operator=(const Rva0033A7DCElement&); struct Hash { unsigned state[2]; unsigned operator()(const Rva0033A7DCElement&) const; }; struct Equal { unsigned state[2]; bool operator()(const Rva0033A7DCElement&,const Rva0033A7DCElement&)const; }; struct Compare {unsigned state[2]; bool operator()(const Rva0033A7DCElement&,const Rva0033A7DCElement&)const; }; bool operator==(const Rva0033A7DCElement&) const; };
template class _STL::hash_map<Rva0033A7DCElement,int,Rva0033A7DCElement::Hash,Rva0033A7DCElement::Equal>;
