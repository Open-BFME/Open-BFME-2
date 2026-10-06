// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00387568Element {
 Rva00387568Element(); Rva00387568Element(const Rva00387568Element&);
 ~Rva00387568Element(); Rva00387568Element&operator=(const Rva00387568Element&);
 char bytes[8];
};
bool operator<(const Rva00387568Element&,const Rva00387568Element&);

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> > & _STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> >::operator=(_STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> > const &);
