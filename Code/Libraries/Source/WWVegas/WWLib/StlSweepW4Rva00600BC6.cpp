// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00600BC6Element {
 Rva00600BC6Element(); Rva00600BC6Element(const Rva00600BC6Element&);
 ~Rva00600BC6Element(); Rva00600BC6Element&operator=(const Rva00600BC6Element&);
 char bytes[8];
};
bool operator<(const Rva00600BC6Element&,const Rva00600BC6Element&);

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<Rva00600BC6Element, _STL::_Const_traits<Rva00600BC6Element> >, bool> _STL::set<Rva00600BC6Element, _STL::less<Rva00600BC6Element>, _STL::allocator<Rva00600BC6Element> >::insert(Rva00600BC6Element const &);
