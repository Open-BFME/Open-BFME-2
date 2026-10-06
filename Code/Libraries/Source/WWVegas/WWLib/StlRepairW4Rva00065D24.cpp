// STLport/compiled destructor reference. Native boundary, operation and call destinations verified.
// Element application identity and unaccessed layout remain address-derived inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00065D24Element {char bytes[8];Rva00065D24Element();Rva00065D24Element(const Rva00065D24Element&);~Rva00065D24Element();Rva00065D24Element&operator=(const Rva00065D24Element&);static void operator delete(void*);};
bool operator<(const Rva00065D24Element&,const Rva00065D24Element&);
template class _STL::set<Rva00065D24Element>;
