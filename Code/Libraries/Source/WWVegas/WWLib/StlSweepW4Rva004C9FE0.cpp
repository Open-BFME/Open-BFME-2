// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>

struct Rva004C9FE0Element { char bytes[1]; Rva004C9FE0Element();Rva004C9FE0Element(const Rva004C9FE0Element&);~Rva004C9FE0Element();Rva004C9FE0Element&operator=(const Rva004C9FE0Element&); struct Hash { unsigned state[1]; unsigned operator()(const Rva004C9FE0Element&) const; }; struct Equal { unsigned state[1]; bool operator()(const Rva004C9FE0Element&,const Rva004C9FE0Element&)const; }; struct Compare {unsigned state[1]; bool operator()(const Rva004C9FE0Element&,const Rva004C9FE0Element&)const; }; bool operator==(const Rva004C9FE0Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_node<Rva004C9FE0Element> * _STL::_Rb_tree<Rva004C9FE0Element, Rva004C9FE0Element, _STL::_Identity<Rva004C9FE0Element>, Rva004C9FE0Element::Compare, _STL::allocator<Rva004C9FE0Element> >::_M_lower_bound(Rva004C9FE0Element const &) const;
