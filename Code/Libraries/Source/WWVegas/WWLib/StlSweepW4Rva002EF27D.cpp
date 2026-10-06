// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva002EF27DElement { int word0; bool operator<(const Rva002EF27DElement&)const; bool operator==(const Rva002EF27DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__pop_heap<Rva002EF27DElement *, Rva002EF27DElement, _STL::less<Rva002EF27DElement>, int>(Rva002EF27DElement *, Rva002EF27DElement *, Rva002EF27DElement *, Rva002EF27DElement, _STL::less<Rva002EF27DElement>, int *);
