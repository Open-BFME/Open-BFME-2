// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <vector>

struct Rva00626EF0Element { int words[6]; bool operator<(const Rva00626EF0Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva00626EF0Element&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template Rva00626EF0Element * _STL::__copy<Rva00626EF0Element *, Rva00626EF0Element *, int>(Rva00626EF0Element *, Rva00626EF0Element *, Rva00626EF0Element *, _STL::random_access_iterator_tag const &, int *);
