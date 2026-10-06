// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00600A40Element {
 Rva00600A40Element(); Rva00600A40Element(const Rva00600A40Element&);
 ~Rva00600A40Element(); Rva00600A40Element&operator=(const Rva00600A40Element&);
 char bytes[8];
};
bool operator<(const Rva00600A40Element&,const Rva00600A40Element&);
template class _STL::set<Rva00600A40Element>;
