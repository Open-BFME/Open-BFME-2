// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00311602Element { char bytes[184];Rva00311602Element();Rva00311602Element(const Rva00311602Element&);~Rva00311602Element();Rva00311602Element&operator=(const Rva00311602Element&); bool operator<(const Rva00311602Element&)const; bool operator==(const Rva00311602Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00311602Element * _STL::__copy<Rva00311602Element *, Rva00311602Element *, int>(Rva00311602Element *, Rva00311602Element *, Rva00311602Element *, _STL::random_access_iterator_tag const &, int *);
