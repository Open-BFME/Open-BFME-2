// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00385CBAElement {
 Rva00385CBAElement(); Rva00385CBAElement(const Rva00385CBAElement&);
 ~Rva00385CBAElement(); Rva00385CBAElement&operator=(const Rva00385CBAElement&);
 char bytes[8];
};
bool operator<(const Rva00385CBAElement&,const Rva00385CBAElement&);

// Instantiate the recovered operation and its required template dependencies.
template unsigned int _STL::_Rb_tree<Rva00385CBAElement, Rva00385CBAElement, _STL::_Identity<Rva00385CBAElement>, _STL::less<Rva00385CBAElement>, _STL::allocator<Rva00385CBAElement> >::erase(Rva00385CBAElement const &);
