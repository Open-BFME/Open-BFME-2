// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>

struct Rva0056DDF5Element { char bytes[1]; Rva0056DDF5Element();Rva0056DDF5Element(const Rva0056DDF5Element&);~Rva0056DDF5Element();Rva0056DDF5Element&operator=(const Rva0056DDF5Element&); struct Hash { unsigned state[2]; unsigned operator()(const Rva0056DDF5Element&) const; }; struct Equal { unsigned state[2]; bool operator()(const Rva0056DDF5Element&,const Rva0056DDF5Element&)const; }; struct Compare {unsigned state[2]; bool operator()(const Rva0056DDF5Element&,const Rva0056DDF5Element&)const; }; bool operator==(const Rva0056DDF5Element&) const; };
template class _STL::hash_map<Rva0056DDF5Element,int,Rva0056DDF5Element::Hash,Rva0056DDF5Element::Equal>;
