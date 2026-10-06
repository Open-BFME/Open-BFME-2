// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva003876A4Element {
 Rva003876A4Element(); Rva003876A4Element(const Rva003876A4Element&);
 ~Rva003876A4Element(); Rva003876A4Element&operator=(const Rva003876A4Element&);
 char bytes[8];
};
bool operator<(const Rva003876A4Element&,const Rva003876A4Element&);

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> > & _STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> >::operator=(_STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> > const &);
