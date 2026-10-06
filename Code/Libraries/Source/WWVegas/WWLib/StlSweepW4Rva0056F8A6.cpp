// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva0056F8A6Element {
 Rva0056F8A6Element(); Rva0056F8A6Element(const Rva0056F8A6Element&);
 ~Rva0056F8A6Element(); Rva0056F8A6Element&operator=(const Rva0056F8A6Element&);
 char bytes[8];
};
bool operator<(const Rva0056F8A6Element&,const Rva0056F8A6Element&);

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<Rva0056F8A6Element, _STL::_Nonconst_traits<Rva0056F8A6Element> > _STL::_Rb_tree<Rva0056F8A6Element, Rva0056F8A6Element, _STL::_Identity<Rva0056F8A6Element>, _STL::less<Rva0056F8A6Element>, _STL::allocator<Rva0056F8A6Element> >::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, Rva0056F8A6Element const &, _STL::_Rb_tree_node_base *);
