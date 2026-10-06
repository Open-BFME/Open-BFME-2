// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003B02D1Element { unsigned opaque;bool operator<(const Rva003B02D1Element&)const;bool operator==(const Rva003B02D1Element&)const; };


// Instantiate the recovered operation and its required template dependencies.
template void _STL::__pop_heap_aux<Rva003B02D1Element **, Rva003B02D1Element *, _STL::less<Rva003B02D1Element *> >(Rva003B02D1Element **, Rva003B02D1Element **, Rva003B02D1Element **, _STL::less<Rva003B02D1Element *>);
