// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva004186F2Element {
 Rva004186F2Element(); Rva004186F2Element(const Rva004186F2Element&);
 ~Rva004186F2Element(); Rva004186F2Element&operator=(const Rva004186F2Element&);
 char bytes[8];
};
bool operator<(const Rva004186F2Element&,const Rva004186F2Element&);
template class _STL::set<Rva004186F2Element>;
